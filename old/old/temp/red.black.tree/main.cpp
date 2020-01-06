#include <iostream>

struct rb_node {
    unsigned long __rb_parent_color;
    struct rb_node * rb_right;
    struct rb_node * rb_left;
};

struct rb_root {
    struct rb_node * rb_node;
};

#define RB_RED          0
#define RB_BLACK        1

#define RB_EMPTY_NODE(node) ((node)->__rb_parent_color == (unsigned long)(node))

#define rb_parent(r)        ((struct rb_node *)((r)->__rb_parent_color & ~3))

#define __rb_parent(pc)     ((struct rb_node *)(pc & ~3))
#define __rb_color(pc)      ((pc) & 1)
#define __rb_is_black(pc)   __rb_color(pc)
#define __rb_is_red(pc)     (!__rb_color(pc))

#define rb_color(rb)       __rb_color((rb)->__rb_parent_color)
#define rb_is_red(rb)      __rb_is_red((rb)->__rb_parent_color)
#define rb_is_black(rb)    __rb_is_black((rb)->__rb_parent_color)

static inline void rb_set_parent(struct rb_node * rb, struct rb_node * p)
{
    rb->__rb_parent_color = rb_color(rb) | (unsigned long)p;
}

static inline void rb_set_parent_color(struct rb_node * rb, struct rb_node * p, int color)
{
    rb->__rb_parent_color = (unsigned long) p | color;
}

static void __rb_change_child(struct rb_node * old, struct rb_node * n, struct rb_node * p, struct rb_root * root)
{
    if(p)
    {
        if(p->rb_left == old)
        {
            p->rb_left = n;
        }
        else
        {
            p->rb_right = n;
        }
    }
    else
    {
        root->rb_node = n;
    }
}

struct rb_node * rb_next(const struct rb_node * node)
{
    struct rb_node * parent;

    if(RB_EMPTY_NODE(node))
    {
        return NULL;
    }

    /**
     * If we have a right-hand child, go down and then left as far as we can.
     */
    if(node->rb_right)
    {
        node = node->rb_right;
        while(node->rb_left){
            node = node->rb_left;
        }
        return (struct rb_node *) node;
    }

    /**
     * No right-hand children.
     * Everything down and left is smaller than use, so any 'next' node must be in the general direction of our parent.
     * Go up the tree; any time the ancestor is a right-hand child of tis parent, keep going up.
     * First time it's a left-hand child of tis parent, said parent is out 'next' node.
     */
    while((parent = rb_parent(node)) && node == parent->rb_right)
    {
        node = parent;
    }
    return parent;
}

static struct rb_node * __rb_erase_argumented(struct rb_node * node, struct rb_root * root, struct rb_node ** leftmost, const struct rb_argument_callbacks * argument)
{
    struct rb_node * child = node->rb_right;
    struct rb_node * tmp = node->rb_left;
    struct rb_node * parent;
    struct rb_node * rebalance;
    unsigned long pc;

    if(leftmost && node == *leftmost)
    {
        *leftmost = rb_next(node);
    }

    if(!tmp)
    {
        /**
         * Case 1: node to erase has no more than 1 child (easy!)
         *
         * Note that if there is one child it must be red due to 5)
         * and node must be black due to 4). We adjust colors locally so as to bypass __rb_erase_color later on.
         */
        pc = node->__rb_parent_color;
        parent = __rb_parent(pc);
        __rb_change_child(node, child, parent, root);
        if(child)
        {
            child->__rb_parent_color = pc;
            rebalance = NULL;
        }
        else
        {
            rebalance = __rb_is_black(pc) ? parent : NULL;
        }
        tmp = parent;
    }
    else
    {
        struct rb_node * successor = child;
        struct rb_node * child2;
        tmp = child->rb_left;
        if(!tmp)
        {
            /**
             * case 2: node's successor is its right child
             *
             *     (n)            (s)
             *     / \           /  \
             *   (x) (s)    -> (x)  (c)
             *        \
             *        (c)
             */
            parent = successor;
            child2 = successor->rb_right;
        }
        else
        {
            /**
             * case 3: node's successor is leftmost under
             * node's right child subtree
			 *    (n)          (s)
			 *    / \          / \
			 *  (x) (y)  ->  (x) (y)
			 *      /            /
			 *    (p)          (p)
			 *    /            /
			 *  (s)          (c)
			 *    \
			 *    (c)
             */
            do {
                parent = successor;
                successor = tmp;
                tmp = tmp->rb_left;
            } while(tmp);
            child2 = successor->rb_right;
            parent->rb_left = child2;
            successor->rb_right = child;
        }
        tmp = node->rb_left;
        successor->rb_left = tmp;
        rb_set_parent(tmp, successor);
        pc = node->__rb_parent_color;
        tmp = __rb_parent(pc);
        __rb_change_child(node, successor, tmp, root);
        if(child2)
        {
            successor->__rb_parent_color = pc;
            rb_set_parent_color(child2, parent, RB_BLACK);
            rebalance = NULL;
        }
        else
        {
            unsigned long pc2 = successor->__rb_parent_color;
            successor->__rb_parent_color = pc;
            rebalance = __rb_is_black(pc2) ? parent : NULL;
        }
        tmp = successor;
    }

    return rebalance;
}

static void __rb_erase_color(struct rb_node * parent, struct rb_root * root, void (*argument_rotate)(struct rb_node * o, struct rb_node * n));

static void rb_erase_augmented(struct rb_node * node, struct rb_root * root, const struct rb_argument_callbacks * augment)
{
    struct rb_node * rebalance = __rb_erase_argumented(node, root, NULL, augment);
    if(rebalance)
    {
        __rb_erase_color(rebalance, root, NULL);
    }
}

static void __rb_erase_color(struct rb_node * parent, struct rb_root * root, void (*argument_rotate)(struct rb_node * o, struct rb_node * n))
{

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}