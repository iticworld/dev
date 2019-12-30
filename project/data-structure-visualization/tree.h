/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 22.
 */

#ifndef   __TREE__H__
#define   __TREE__H__

#define BLACK       0
#define RED         1

struct node
{
    int color;
    int value;
    struct node * parent;
    struct node * left;
    struct node * right;
};

extern struct node * red_black_tree_node_new(int value, struct node * parent, struct node * left, struct node * right, int color);
extern struct node * red_black_tree_node_clear(struct node * n);
extern struct node * red_black_tree_node_free(struct node * n);
extern int red_black_tree_node_color(struct node * n);

extern struct node * red_black_tree_node_uncle(struct node * n);
extern struct node * red_black_tree_node_sibling(struct node * n);
extern struct node * red_black_tree_node_grandparent(struct node * n);

struct tree
{
    struct node * root;
    int size;
};

extern struct tree * red_black_tree_new();
extern struct tree * red_black_tree_clear(struct tree * t);
extern struct tree * red_black_tree_free(struct tree * t);

extern void red_black_tree_print(struct tree * o);

extern struct node * red_black_tree_search(struct tree * t, int value);
extern struct node * red_black_tree_min(struct node * n);
extern struct node * red_black_tree_max(struct node * n);

extern struct node * red_black_tree_add(struct tree * t, int value);
extern void red_black_tree_fixup_add(struct tree * t, struct node * n);

extern struct node * red_black_tree_del(struct tree * t, int value);
extern void red_black_tree_fixup_del(struct tree * t, struct node * n);

extern void red_black_tree_rotate_left(struct tree * t, struct node * n);
extern void red_black_tree_rotate_right(struct tree * t, struct node * n);

#endif // __TREE__H__
