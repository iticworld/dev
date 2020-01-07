#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#ifdef    __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__

typedef __INT64_TYPE__      integer64;

#define success             (0)
#define fail                (-1)

void random_init()
{
    srand((unsigned int) time(NULL));
}

int random_get(int bound)
{
    if(bound > 0)
    {
        return rand() % bound;
    }
    else
    {
        printf("bound <= 0\n");
    }
    return 0;
}

struct timestamp
{
    integer64 second;
    integer64 nanosecond;
};

int timestamp_get(struct timestamp * p)
{
    if(p != NULL)
    {
        struct timespec v;
        if(clock_gettime(CLOCK_REALTIME, &v) == 0)
        {
            p->second = v.tv_sec;
            p->nanosecond = v.tv_nsec;
            return success;
        }
        else
        {
            printf("fail to clock_gettime(CLOCK_REALTIME, &v) caused by %d\n", errno);
        }
    }
    else
    {
        printf("p == null\n");
    }
    return fail;
}

void timestamp_out(struct timestamp * p)
{
    if(p != NULL)
    {
#ifdef    __EMSCRIPTEN__
        printf("%lld.%09lld\n", p->second, p->nanosecond);
#else  // __EMSCRIPTEN__
        printf("%ld.%09ld\n", p->second, p->nanosecond);
#endif // __EMSCRIPTEN__
    }
    else
    {
        printf("p == null\n");
    }
}

int timestamp_gap(struct timestamp * p, struct timestamp * previous)
{
    if(p != NULL && previous != NULL)
    {
        struct timestamp current = {};
        if(timestamp_get(&current) == success)
        {
            p->second = current.second - previous->second;
            p->nanosecond = current.nanosecond - previous->nanosecond;
#ifdef    __EMSCRIPTEN__
            integer64 n = llabs(p->nanosecond);
#else  // __EMSCRIPTEN__
            integer64 n = labs(p->nanosecond);
#endif // __EMSCRIPTEN__
            if(p->nanosecond >= 0)
            {
                p->second += (n / 1000000000);
                p->nanosecond = (n % 1000000000);
            }
            else
            {
                p->second -= (n / 1000000000);
                p->nanosecond = (n % 1000000000);
                p->second -= 1;
                p->nanosecond = 1000000000 - p->nanosecond;
            }
            return success;
        }
        else
        {
            printf("fail to timestamp_get(&current)\n");
        }
    }
    else
    {
        printf("p == null || previous == NULL\n");
    }
    return fail;
}

struct node
{
    int value;
    struct node * parent;
    struct node * left;
    struct node * right;
};

struct tree
{
    struct node * root;
    int size;
};

struct tree * binary_search_tree_new();
void binary_search_tree_free(struct tree * p);
void binary_search_tree_clear(struct tree * p);

struct node * binary_search_tree_node_new(int value, struct node * parent, struct node * left, struct node * right);
void binary_search_tree_node_free(struct node * p);
void binary_search_tree_node_clear(struct node * p);
void binary_search_tree_add(struct tree * o, int v);
struct node * binary_search_tree_search(struct tree * o, int v);
void binary_search_tree_del(struct tree * o, int v);

void binary_search_tree_print(struct tree * o);
struct node * binary_search_tree_minimum_node(struct node * o);
struct node * binary_search_tree_maximum_node(struct node * o);

struct node * binary_search_tree_preorder_next(struct tree * o, struct node * n);

struct node * binary_search_tree_inorder_next(struct tree * o, struct node * n);
struct node * binary_search_tree_inorder_previous(struct tree * o, struct node * n);

int main()
{
#ifdef    __EMSCRIPTEN__
    EM_ASM({
        novemberizing.chart.init();
    });
#endif // __EMSCRIPTEN__
    random_init();
    struct timestamp previous = {};
    struct timestamp result = {};
    struct timestamp start = {};
    struct timestamp end = {};
    timestamp_get(&start);
    for(int k = 0; k < 1; k++)
    {
        struct tree * tree = binary_search_tree_new();
        printf("add:       ");
        for(int i = 0; i < 16; i++)
        {
            int v = random_get(100);
            timestamp_get(&previous);
            binary_search_tree_add(tree, v);
            timestamp_gap(&result, &previous);
            if(i == 0)
            {
#ifdef    __EMSCRIPTEN__
                printf("%02d (%lld.%09lld)\n", v, result.second, result.nanosecond);
#else  // __EMSCRIPTEN__
                printf("%02d (%ld.%09ld)\n", v, result.second, result.nanosecond);
#endif // __EMSCRIPTEN__
            }
            else
            {
#ifdef    __EMSCRIPTEN__
                printf("           %02d (%lld.%09lld)\n", v, result.second, result.nanosecond);
#else  // __EMSCRIPTEN__
                printf("           %02d (%ld.%09ld)\n", v, result.second, result.nanosecond);
#endif // __EMSCRIPTEN__
            }
            binary_search_tree_print(tree);
        }
        printf("size:      %d\n", tree->size);
        printf("preorder:  ");
        for(struct node * i = tree->root; i != NULL; i = binary_search_tree_preorder_next(tree, i))
        {
            printf("%d ", i->value);
        }
        printf("\n");
        printf("inorder:   ");
        for(struct node * i = binary_search_tree_minimum_node(tree->root); i != NULL; i = binary_search_tree_inorder_next(tree, i))
        {
            printf("%d ", i->value);
        }
        printf("\n");
        printf("inorder:   ");
        for(struct node * i = binary_search_tree_maximum_node(tree->root); i != NULL; i = binary_search_tree_inorder_previous(tree, i))
        {
            printf("%d ", i->value);
        }
        printf("\n");
        printf("del:       ");
        for(int i = 0; i < 8; i++)
        {
            int v = random_get(100);
            timestamp_get(&previous);
            binary_search_tree_del(tree, v);
            timestamp_gap(&result, &previous);
            if(i == 0)
            {
#ifdef    __EMSCRIPTEN__
                printf("%02d (%lld.%09lld)\n", v, result.second, result.nanosecond);
#else  // __EMSCRIPTEN__
                printf("%02d (%ld.%09ld)\n", v, result.second, result.nanosecond);
#endif // __EMSCRIPTEN__
            }
            else
            {
#ifdef    __EMSCRIPTEN__
                printf("           %02d (%lld.%09lld)\n", v, result.second, result.nanosecond);
#else  // __EMSCRIPTEN__
                printf("           %02d (%ld.%09ld)\n", v, result.second, result.nanosecond);
#endif // __EMSCRIPTEN__
            }
            binary_search_tree_print(tree);
        }
        binary_search_tree_free(tree);
    }
    timestamp_gap(&end, &start);
    timestamp_out(&end);
    return 0;
}

struct node * binary_search_tree_node_new(int value, struct node * parent, struct node * left, struct node * right)
{
    struct node * p = calloc(1, sizeof(struct node));
    if(p != NULL)
    {
        p->value = value;
        p->parent = parent;
        p->left = left;
        p->right = right;
    }
    else
    {
        printf("fail to calloc(...) caused by %d\n", errno);
    }
    return p;
}

void binary_search_tree_node_free(struct node * p)
{
    if(p != NULL)
    {
        if(p->parent)
        {
            if(p->parent->left == p)
            {
                p->parent->left = NULL;
            }
            else if(p->parent->right == p)
            {
                p->parent->right = NULL;
            }
            p->parent = NULL;
        }
        if(p->left)
        {
            if(p->left->parent == p)
            {
                p->left = NULL;
            }
            p->left = NULL;
        }
        if(p->right)
        {
            if(p->right->parent == p)
            {
                p->right = NULL;
            }
            p->right = NULL;
        }
        p->value = 0;
        free(p);
    }
}

void binary_search_tree_node_clear(struct node * p)
{
    if(p != NULL)
    {
        p->parent = NULL;
        p->left = NULL;
        p->right = NULL;
    }
}

struct tree * binary_search_tree_new()
{
    return calloc(1, sizeof(struct tree));
}

void binary_search_tree_free(struct tree * p)
{
    if(p != NULL)
    {
        binary_search_tree_clear(p);
        free(p);
    }
}

void binary_search_tree_clear(struct tree * p)
{
    if(p != NULL)
    {
        struct node * n = p->root;
        while(n)
        {
            if(n->left)
            {
                n = n->left;
            }
            else if(n->right)
            {
                n = n->right;
            }
            else
            {
                struct node * d = n;
                n = n->parent;
                binary_search_tree_node_free(d);
                p->size -= 1;
            }
        }
        p->root = NULL;
    }
}

void binary_search_tree_add(struct tree * o, int v)
{
    if(o != NULL)
    {
        struct node * current = o->root;
        if(current == NULL)
        {
            o->root = binary_search_tree_node_new(v, NULL, NULL, NULL);
            o->size += 1;
            return;
        }
        while(current)
        {
            if(current->value == v)
            {
                break;
            }
            else if(current->value > v)
            {
                if(current->left)
                {
                    current = current->left;
                }
                else
                {
                    struct node * n = binary_search_tree_node_new(v, current, NULL, NULL);
                    current->left = n;
                    o->size += 1;
                    break;
                }
            }
            else
            {
                if(current->right)
                {
                    current = current->right;
                }
                else
                {
                    struct node * n = binary_search_tree_node_new(v, current, NULL, NULL);
                    current->right = n;
                    o->size += 1;
                    break;
                }
            }
        }
    }
    else
    {
        printf("o == NULL\n");
    }
}

struct node * binary_search_tree_minimum_node(struct node * o)
{
    struct node * n = o;
    while(n!=NULL && n->left!=NULL)
    {
        n = n->left;
    }
    return n;
}

struct node * binary_search_tree_maximum_node(struct node * o)
{
    struct node * n = o;
    while(n!=NULL && n->right!=NULL)
    {
        n = n->right;
    }
    return n;
}

struct node * binary_search_tree_preorder_next(struct tree * o, struct node * n)
{
    if(o != NULL)
    {
        if(n != NULL)
        {
            if(n->left)
            {
                return n->left;
            }
            if(n->right)
            {
                return n->right;
            }
            if(n->parent)
            {
                while(n == n->parent->right || n == n->parent->left)
                {
                    if(n != n->parent->right)
                    {
                        if(n->parent->right)
                        {
                            return n->parent->right;
                        }
                    }
                    n = n->parent;
                    if(n->parent == NULL)
                    {
                        return NULL;
                    }
                }
            }
            else
            {
                return NULL;
            }
        }
        else
        {
            return o->root;
        }
    }
    else
    {
        printf("o == null\n");
    }
    return NULL;
}

struct node * binary_search_tree_inorder_previous(struct tree * o, struct node * n)
{
    if(o != NULL)
    {
        if(n != NULL)
        {
            if(n->left)
            {
                return binary_search_tree_maximum_node(n->left);
            }
            struct node * parent = n->parent;
            while(parent)
            {
                if(parent->right == n)
                {
                    return parent;
                }
                n = parent;
                parent = parent->parent;
            }
        }
        else
        {
            return binary_search_tree_maximum_node(o->root);
        }
    }
    return NULL;
}

struct node * binary_search_tree_inorder_next(struct tree * o, struct node * n)
{
    if(o != NULL)
    {
        if(n != NULL)
        {
            if(n->right)
            {
                return binary_search_tree_minimum_node(n->right);
            }
            struct node * parent = n->parent;
            while(parent)
            {
                if(parent->left == n)
                {
                    return parent;
                }
                n = parent;
                parent = parent->parent;
            }
        }
        else
        {
            return binary_search_tree_minimum_node(o->root);
        }
    }
    else
    {
        printf("o == NULL\n");
    }
    return NULL;
}

void binary_search_tree_print(struct tree * o)
{
    /** only using emscripten */
    if(o != NULL)
    {
        if(o->root != NULL)
        {
            int depth = 0;
            int count = 0;
            struct node ** container = malloc(sizeof(struct node *));
            container[0] = o->root;
            int start = 0;
            int end = 1;

            do
            {
                depth++;
                container = realloc(container, sizeof(struct node *) * ((end + 1) * 2 - 1));
                count = 0;
                for(int i = 0; i < (end - start); i++)
                {
                    container[end + i * 2] = NULL;
                    container[end + i * 2 + 1] = NULL;
                    if(container[start + i])
                    {
                        if(container[start + i]->left)
                        {
                            container[end + i * 2] = container[start + i]->left;
                            count++;
                        }
                        if(container[start + i]->right)
                        {
                            container[end + i * 2 + 1] = container[start + i]->right;
                            count++;
                        }
                    }
                }
                start = end;
                end = (end + 1) * 2 - 1;
            } while(count > 0);
            int total = ((end + 1) >> 2);
            int horizontal = total;
            printf("total: %d\n", total);
            printf("depth: %d\n", depth - 1);
            printf("horizontal: %d\n", horizontal);
            count = 0;
            start = 0;
            end = 1;
            char * json = malloc(sizeof(char) * 128);
            int len = 0;
            int capacity = 128;
            json[len++] = '[';
            json[len] = 0;

            for(int i = 0; i < depth; i++)
            {
                int x = 0;
                for(int j = 0; j < (end - start); j++)
                {
                    x += horizontal;
                    if(container[start + j])
                    {
                        char str[128];
                        int n = 0;
                        if(json[1] == 0)
                        {
                            n = snprintf(str, 128, "{\"x\":%d,\"y\":%d,\"v\":%d}", x + 1, depth - i, container[start + j]->value);
                        }
                        else
                        {
                            n = snprintf(str, 128, ",{\"x\":%d,\"y\":%d,\"v\":%d}", x + 1, depth - i, container[start + j]->value);
                        }
                        if(capacity <= len + n + 1)
                        {
                            json = realloc(json, (size_t) (capacity += 128));
                        }
                        memcpy(&json[len], str, n);
                        len += n;
                        json[len] = 0;
                    }
                    x += horizontal;
                }
                start = end;
                end = (end + 1) * 2 - 1;
                horizontal = (horizontal >> 1);
            }
            if(capacity <= len + 2)
            {
                json = realloc(json, (size_t) (capacity += 128));
            }
            json[len++] = ']';
            json[len] = 0;
            printf("%s\n", json);
#ifdef    __EMSCRIPTEN__
            EM_ASM_INT({
                novemberizing.tree.show(Pointer_stringify($0), 'binary search tree');
            }, json);
#endif // __EMSCRIPTEN__
            printf("implement print out\n");
            free(json);
            free(container);
        }
    }
}

struct node * binary_search_tree_search(struct tree * o, int v)
{
    if(o != NULL)
    {
        struct node * n = o->root;
        while(n)
        {
            if(n->value == v)
            {
                return n;
            }
            else if(n->value < v)
            {
                n = n->right;
            }
            else
            {
                n = n->left;
            }
        }
        return n;
    }
    return NULL;
}

void binary_search_tree_del(struct tree * o, int v)
{
    struct node * n = binary_search_tree_search(o, v);
    if(n != NULL)
    {
        if(n->left == NULL)
        {
            if(n->parent != NULL)
            {
                if(n->parent->left == n)
                {
                    n->parent->left = n->right;
                }
                else
                {
                    n->parent->right = n->right;
                }
            }
            else
            {
                o->root = n->right;
            }
            if(n->right)
            {
                n->right->parent = n->parent;
            }
        }
        else if(n->right == NULL)
        {
            if(n->parent != NULL)
            {
                if(n->parent->left == n)
                {
                    n->parent->left = n->left;
                }
                else
                {
                    n->parent->right = n->left;
                }
            }
            else
            {
                o->root = n->left;
            }
            n->left->parent = n->parent;
        }
        else
        {
            struct node * successor = binary_search_tree_minimum_node(n->right);
            struct node * right = successor->right;
            if(successor->parent->right == successor)
            {
                successor->parent->right = right;
            }
            else
            {
                successor->parent->left = right;
            }
            if(right)
            {
                right->parent = successor->parent;
            }
            if(n->parent != NULL)
            {
                if(n->parent->left == n)
                {
                    n->parent->left = successor;
                }
                else
                {
                    n->parent->right = successor;
                }
            }
            else
            {
                o->root = successor;
            }
            successor->parent = n->parent;
            successor->left = n->left;
            if(n->left)
            {
                n->left->parent = successor;
            }
            successor->right = n->right;
            if(n->right)
            {
                n->right->parent = successor;
            }
            binary_search_tree_node_clear(n);
        }
        binary_search_tree_node_free(n);
        o->size -= 1;
    }
}