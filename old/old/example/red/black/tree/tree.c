/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 22.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#ifdef    __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__

#include "util.h"
#include "tree.h"

struct tree * red_black_tree_new()
{
    return calloc(sizeof(struct tree), 1);
}

struct tree * red_black_tree_clear(struct tree * t)
{
    assertion(t == NULL, "[%s:%d:%s] t == NULL", __FILE__, __LINE__, __func__);
    struct node * n = t->root;
    while(n != NULL)
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
            if(n->parent)
            {
                if(n->parent->left == n)
                {
                    n->parent->left = NULL;
                }
                else
                {
                    n->parent->right = NULL;
                }
            }
            struct node * d = n;
            n = n->parent;
            red_black_tree_node_free(d);
        }
    }
    t->size = 0;
    t->root = NULL;
    return t;
}

struct tree * red_black_tree_free(struct tree * t)
{
    assertion(t == NULL, "[%s:%d:%s] t == NULL", __FILE__, __LINE__, __func__);
    red_black_tree_clear(t);
    free(t);
    return NULL;
}

static void reb_black_tree_print_insertion_duplicate(int value)
{
    return;
#ifdef    __EMSCRIPTEN__
    EM_ASM_INT({
            let o = novemberizing.html.add('RED BLACK TREE INSERTION[DUP]: ' + $0, 'view');
            o.style.fontWeight = 'bolder';
            o.style.fontSize = '16pt';
            o.style.marginLeft = "5px";
            o.style.marginRight = "5px";
            o.style.marginTop = "5px";
            o.style.marginBottom = "5px";
        }, value);
#else  // __EMSCRIPTEN__
    (void)(value);
#endif // __EMSCRIPTEN__
}

static void reb_black_tree_print_insertion(int value, const char * format, ...)
{
    return;
    char s[1024];
    va_list ap;
    va_start(ap, format);
    vsnprintf(s, 1024, format, ap);
    va_end(ap);
#ifdef    __EMSCRIPTEN__
    EM_ASM_INT({
            let o = novemberizing.html.add('RED BLACK TREE INSERTION: ' + $0, 'view');
            o.style.fontWeight = 'bolder';
            o.style.fontSize = '16pt';
            o.style.marginLeft = "5px";
            o.style.marginRight = "5px";
            o.style.marginTop = "5px";
            o.style.marginBottom = "5px";
        }, value);
        EM_ASM_INT({
            let o = novemberizing.html.add(Pointer_stringify($0), 'view', 'p');
            o.style.fontWeight = 'normal';
            o.style.fontSize = '10pt';
            o.style.marginLeft = "15px";
            o.style.marginRight = "15px";
            o.style.marginTop = "2px";
            o.style.marginBottom = "2px";
        }, s);
#else  // __EMSCRIPTEN__
    (void)(value);
    (void)(s);
#endif // __EMSCRIPTEN__
}

static void reb_black_tree_print_insertion_fixup(const char * format, ...)
{
    return;
    char s[1024];
    va_list ap;
    va_start(ap, format);
    vsnprintf(s, 1024, format, ap);
    va_end(ap);
#ifdef    __EMSCRIPTEN__
    EM_ASM_INT({
        let o = novemberizing.html.add(Pointer_stringify($0), 'view', 'p');
        o.style.fontWeight = 'normal';
        o.style.fontSize = '10pt';
        o.style.marginLeft = "15px";
        o.style.marginRight = "15px";
        o.style.marginTop = "2px";
        o.style.marginBottom = "2px";
    }, s);
#else  // __EMSCRIPTEN__
    (void)(s);
#endif // __EMSCRIPTEN__
}

static void reb_black_tree_print_deletion(int value, const char * format, ...)
{
    char s[1024];
    va_list ap;
    va_start(ap, format);
    vsnprintf(s, 1024, format, ap);
    va_end(ap);
#ifdef    __EMSCRIPTEN__
    EM_ASM_INT({
            let o = novemberizing.html.add('RED BLACK TREE DELETION: ' + $0, 'view');
            o.style.fontWeight = 'bolder';
            o.style.fontSize = '16pt';
            o.style.marginLeft = "5px";
            o.style.marginRight = "5px";
            o.style.marginTop = "5px";
            o.style.marginBottom = "5px";
        }, value);
        EM_ASM_INT({
            let o = novemberizing.html.add(Pointer_stringify($0), 'view', 'p');
            o.style.fontWeight = 'normal';
            o.style.fontSize = '10pt';
            o.style.marginLeft = "15px";
            o.style.marginRight = "15px";
            o.style.marginTop = "2px";
            o.style.marginBottom = "2px";
        }, s);
#else  // __EMSCRIPTEN__
    (void)(value);
    (void)(s);
#endif // __EMSCRIPTEN__
}

struct node * red_black_tree_add(struct tree * t, int value)
{
    assertion(t == NULL, "[%s:%d:%s] t == NULL", __FILE__, __LINE__, __func__);
    if(t->root == NULL)
    {
        t->size += 1;
        reb_black_tree_print_insertion(value, "ROOT = NEW(%d, BLACK)", value);
        return t->root = red_black_tree_node_new(value, NULL, NULL, NULL, BLACK);
    }
    struct node * n = t->root;
    while(n != NULL)
    {
        if(n->value == value)
        {
            reb_black_tree_print_insertion_duplicate(value);
            return n;
        }
        else if(n->value < value)
        {
            if(n->right == NULL)
            {
                t->size += 1;
                reb_black_tree_print_insertion(value, "- %c(%d)'S RIGHT = NEW(%d, RED)", n->color == 1 ? 'R' : 'B' ,n->value, value);
                struct node * i = n->right = red_black_tree_node_new(value, n, NULL, NULL, RED);
                red_black_tree_fixup_add(t, n->right);
                return i;
            }
            n = n->right;
        }
        else
        {
            if(n->left == NULL)
            {
                t->size += 1;
                reb_black_tree_print_insertion(value, "- %c(%d)'S LEFT = NEW(%d, RED)", n->color == 1 ? 'R' : 'B' ,n->value, value);
                struct node * i = n->left = red_black_tree_node_new(value, n, NULL, NULL, RED);
                red_black_tree_fixup_add(t, n->left);
                return i;
            }
            n = n->left;
        }
    }
    return NULL;
}

extern void red_black_tree_fixup_add(struct tree * t, struct node * n)
{
    assertion(t == NULL || n == NULL, "[%s:%d:%s] t == NULL || n == NULL", __FILE__, __LINE__, __func__);
    while(n->parent != NULL && n->parent->color == RED)
    {
        struct node * parent = n->parent;
        struct node * grandparent = red_black_tree_node_grandparent(n);
        if(grandparent != NULL)
        {
            struct node * uncle = (grandparent->left == n->parent ? grandparent->right : grandparent->left);
            /** case 1: uncle's color is red */
            if(red_black_tree_node_color(uncle) == RED)
            {
                reb_black_tree_print_insertion_fixup("- FIXUP[RECOLOR]: %c(%d) AND UNCLE == RED", n->color == 1 ? 'R' : 'B' ,n->value);
                grandparent->color = RED;
                uncle->color = BLACK;
                parent->color = BLACK;
                n = grandparent;
                continue;
            }
            /** uncle's color is black */
            if(n == parent->left)
            {
                if(grandparent->right == parent)
                {
                    reb_black_tree_print_insertion_fixup("- FIXUP[TRIANGLE]: %c(%d) == BLACK AND UNCLE == RED", n->color == 1 ? 'R' : 'B' ,n->value);
                    n = parent;
                    red_black_tree_rotate_right(t, n);
                    parent = n->parent;
                    grandparent = parent->parent;
                }
            }
            else
            {
                if(grandparent->left == parent)
                {
                    reb_black_tree_print_insertion_fixup("- FIXUP[TRIANGLE]: %c(%d) == BLACK AND UNCLE == RED", n->color == 1 ? 'R' : 'B' ,n->value);
                    n = parent;
                    red_black_tree_rotate_left(t, n);
                    parent = n->parent;
                    grandparent = parent->parent;
                }
            }
            if(n == parent->left)
            {
                if(grandparent->left == parent)
                {
                    reb_black_tree_print_insertion_fixup("- FIXUP[LINE]: %c(%d) == BLACK AND UNCLE == RED", n->color == 1 ? 'R' : 'B' ,n->value);
                    grandparent->color = RED;
                    parent->color = BLACK;
                    red_black_tree_rotate_right(t, grandparent);
                    n = grandparent;
                    continue;
                }
            }
            else
            {
                if(grandparent->right == parent)
                {
                    reb_black_tree_print_insertion_fixup("- FIXUP[LINE]: %c(%d) == BLACK AND UNCLE == RED", n->color == 1 ? 'R' : 'B' ,n->value);
                    grandparent->color = RED;
                    parent->color = BLACK;
                    red_black_tree_rotate_left(t, grandparent);
                    continue;
                }
            }
        }
        break;
    }
    if(t->root->color == RED)
    {
        reb_black_tree_print_insertion_fixup("- FIXUP[ROOT]: %c(%d) == RED", t->root->color == 1 ? 'R' : 'B' , t->root->value);
    }
    t->root->color = BLACK;
}

void red_black_tree_rotate_left(struct tree * t, struct node * n)
{
    assertion(t == NULL || n == NULL, "[%s:%d:%s] t == NULL || n == NULL", __FILE__, __LINE__, __func__);
    struct node * right = n->right;
    /** right */
    if(n->parent != NULL)
    {
        if(n->parent->left == n)
        {
            n->parent->left = right;
        }
        else
        {
            n->parent->right = right;
        }
    }
    else
    {
        t->root = right;
    }
    right->parent = n->parent;
    /** right's left */
    n->right = right->left;
    if(right->left)
    {
        right->left->parent = n;
    }
    /** n */
    n->parent = right;
    right->left = n;
}

void red_black_tree_rotate_right(struct tree * t, struct node * n)
{
    assertion(t == NULL || n == NULL, "[%s:%d:%s] t == NULL || n == NULL", __FILE__, __LINE__, __func__);
    struct node * left = n->left;
    /** left */
    if(n->parent != NULL)
    {
        if(n->parent->left == n)
        {
            n->parent->left = left;
        }
        else
        {
            n->parent->right = left;
        }
    }
    else
    {
        t->root = n->left;
    }
    left->parent = n->parent;
    /** left's right */
    n->left = left->right;
    if(left->right)
    {
        left->right->parent = n;
    }
    /** n */
    left->right = n;
    n->parent = left;
}

void red_black_tree_print(struct tree * t)
{
    /** only using emscripten */
    if(t != NULL)
    {
        if(t->root != NULL)
        {
            int depth = 0;
            int count = 0;
            struct node ** container = malloc(sizeof(struct node *));
            container[0] = t->root;
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
//            printf("total: %d\n", total);
//            printf("depth: %d\n", depth - 1);
//            printf("horizontal: %d\n", horizontal);
            start = 0;
            end = 1;
            char * red = malloc(sizeof(char) * 128);
            char * black = malloc(sizeof(char) * 128);
            int redlen = 0;
            int blacklen = 0;
            int redcapacity = 128;
            int blackcapacity = 128;
            red[redlen++] = '[';
            red[redlen] = 0;
            black[blacklen++] = '[';
            black[blacklen] = 0;

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
                        if(container[start + j]->color==RED)
                        {
                            if(red[1] == 0)
                            {
                                // n = snprintf(str, 128, "{x:%d,y:%d,v:%d,c:%d}", x + 1, depth - i, container[start + j]->value, container[start + j]->color);
                                n = snprintf(str, 128, "{\"x\":%d,\"y\":%d,\"v\":%d,\"c\":%d}", x, depth - i, container[start + j]->value, container[start + j]->color);
                            }
                            else
                            {
                                // n = snprintf(str, 128, ",{x:%d,y:%d,v:%d,c:%d}", x + 1, depth - i, container[start + j]->value, container[start + j]->color);
                                n = snprintf(str, 128, ",{\"x\":%d,\"y\":%d,\"v\":%d,\"c\":%d}", x, depth - i, container[start + j]->value, container[start + j]->color);
                            }
                            if(redcapacity <= redlen + n + 1)
                            {
                                red = realloc(red, (size_t) (redcapacity += 128));
                            }
                            memcpy(&red[redlen], str, n);
                            redlen += n;
                            red[redlen] = 0;
                        }
                        else
                        {
                            if(black[1] == 0)
                            {
                                // n = snprintf(str, 128, "{x:%d,y:%d,v:%d,c:%d}", x + 1, depth - i, container[start + j]->value, container[start + j]->color);
                                n = snprintf(str, 128, "{\"x\":%d,\"y\":%d,\"v\":%d,\"c\":%d}", x, depth - i, container[start + j]->value, container[start + j]->color);
                            }
                            else
                            {
                                // n = snprintf(str, 128, ",{x:%d,y:%d,v:%d,c:%d}", x + 1, depth - i, container[start + j]->value, container[start + j]->color);
                                n = snprintf(str, 128, ",{\"x\":%d,\"y\":%d,\"v\":%d,\"c\":%d}", x, depth - i, container[start + j]->value, container[start + j]->color);
                            }
                            if(blackcapacity <= blacklen + n + 1)
                            {
                                black = realloc(black, (size_t) (blackcapacity += 128));
                            }
                            memcpy(&black[blacklen], str, n);
                            blacklen += n;
                            black[blacklen] = 0;
                        }
                    }
                    x += horizontal;
                }
                start = end;
                end = (end + 1) * 2 - 1;
                horizontal = (horizontal >> 1);
            }
            if(redcapacity <= redlen + 2)
            {
                red = realloc(red, (size_t) (redcapacity + 128));
            }
            red[redlen++] = ']';
            red[redlen] = 0;
            if(blackcapacity <= blacklen + 2)
            {
                black = realloc(black, (size_t) (blackcapacity + 128));
            }
            black[blacklen++] = ']';
            black[blacklen] = 0;
//            printf("depth: %d\n", depth);
//            printf("[\n%s\n,\n%s\n]\n", red, black);
#ifdef    __EMSCRIPTEN__
            EM_ASM_INT({
                novemberizing.tree.show("["+Pointer_stringify($0)+ "," +Pointer_stringify($1)+"]", 'red black tree', 'view', $2, $3);
            }, red, black, depth, total * 2);
#endif // __EMSCRIPTEN__
            //printf("implement print out\n");
            free(red);
            free(black);
            free(container);
        }
    }
}

struct node * red_black_tree_search(struct tree * t, int value)
{
    assertion(t == NULL, "[%s:%d:%s] t == NULL", __FILE__,__LINE__,__func__);
    struct node * n = t->root;
    while(n != NULL)
    {
        if(n->value == value)
        {
            return n;
        }
        else if(n->value < value)
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

struct node * red_black_tree_min(struct node * n)
{
    while(n && n->left){ n = n->left; }
    return n;
}

struct node * red_black_tree_max(struct node * n)
{
    while(n && n->right){ n = n->right; }
    return n;
}

struct node * red_black_tree_del(struct tree * t, int value)
{
    struct node * n = red_black_tree_search(t, value);
    if(n != NULL)
    {
        reb_black_tree_print_deletion(value, "- DELETE[BST] %c(%d)", n->color==1 ? 'R' : 'B', n->value);
        if(n->left == NULL)
        {
            if(n->parent)
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
                t->root = n->right;
            }
            if(n->right)
            {
                n->right->parent = n->parent;
            }

            if(n->color == BLACK)
            {
                red_black_tree_fixup_del(t, n->parent);
            }
        }
        else if(n->right == NULL)
        {
            if(n->parent)
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
                t->root = n->left;
            }
            n->left->parent = n->parent;

            if(n->color == BLACK)
            {
                red_black_tree_fixup_del(t, n->parent);
            }
        }
        else
        {
            struct node * min = red_black_tree_min(n->right);
            struct node * parent = min->parent;
            int color = min->color;
            if(min->parent->left == min)
            {
                min->parent->left = min->right;
            }
            else
            {
                min->parent->right = min->right;
            }
            if(min->right)
            {
                min->right->parent = min->parent;
            }
            if(n->parent)
            {
                if(n->parent->left == n)
                {
                    n->parent->left = min;
                }
                else
                {
                    n->parent->right = min;
                }
            }
            else
            {
                t->root = min;
            }
            min->parent = n->parent;
            min->left = n->left;
            min->left->parent = min;
            min->right = n->right;
            min->right->parent = min;
            min->color = n->color;
            if(color == BLACK)
            {
                red_black_tree_fixup_del(t, parent);
            }
        }
    }

    return n;
}

void red_black_tree_fixup_del(struct tree * t, struct node * parent)
{
#ifdef    __EMSCRIPTEN__
    EM_ASM({
        let o = novemberizing.html.add('- FIXUP', 'view', 'p');
        o.style.fontWeight = 'normal';
        o.style.fontSize = '10pt';
        o.style.marginLeft = "15px";
        o.style.marginRight = "15px";
        o.style.marginTop = "2px";
        o.style.marginBottom = "2px";
    });
#endif // __EMSCRIPTEN__
    struct node * n = NULL;
    struct node * sibling = NULL;
    while(red_black_tree_node_color(n)==BLACK && parent != NULL)
    {
        sibling = parent->right;
        if(n != sibling)
        {
            /** case 1: sibling's color is red */
            if(sibling->color == RED)
            {
                sibling->color = BLACK;
                sibling->parent->color = RED;
                red_black_tree_rotate_left(t, parent);
                red_black_tree_print(t);
                sibling = parent->right;
                n = parent->left;
            }

            if(red_black_tree_node_color(sibling->right)==BLACK)
            {
                if(red_black_tree_node_color(sibling->left)==BLACK)
                {
                    /** case 2: sibling's color is black and both of children are black */
                    sibling->color = RED;
                    n = parent;
                    parent = n->parent;
                    red_black_tree_print(t);
                }
                else
                {
                    /** case 3: sibling's color is black and sibling's left is red and sibling's right is black */
                    sibling->color = RED;
                    sibling->left->color = BLACK;
                    red_black_tree_rotate_right(t, sibling);
                    red_black_tree_print(t);
                    sibling = parent->right;
                }

            }
            if(red_black_tree_node_color(sibling->right)==RED)
            {
                sibling->color = parent->color;
                sibling->right->color = BLACK;
                parent->color = BLACK;
                red_black_tree_rotate_left(t, parent);
                break;
            }
        }
        else
        {
            sibling = parent->left;
            /** case 1: sibling's color is red */
            if(sibling->color == RED)
            {
                sibling->color = BLACK;
                sibling->parent->color = RED;
                red_black_tree_rotate_right(t, parent);
                red_black_tree_print(t);
            }
        }
    }
}
