/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 22.
 */

#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "tree.h"

struct node * red_black_tree_node_new(int value, struct node * parent, struct node * left, struct node * right, int color)
{
    struct node * n = malloc(sizeof(struct node));
    n->value = value;
    n->parent = parent;
    n->left = left;
    n->right = right;
    n->color = color;
    return n;
}

struct node * red_black_tree_node_clear(struct node * n)
{
    assertion(n == NULL, "[%s:%d:%s] n == NULL", __FILE__, __LINE__,__func__);
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    n->color = BLACK;
    return n;
}

struct node * red_black_tree_node_free(struct node * n)
{
    assertion(n == NULL, "[%s:%d:%s] n == NULL", __FILE__, __LINE__,__func__);
    free(n);
    return NULL;
}

struct node * red_black_tree_node_uncle(struct node * n)
{
    assertion(n == NULL, "[%s:%d:%s] n == NULL", __FILE__, __LINE__, __func__);
    struct node * grandparent = red_black_tree_node_grandparent(n);
    return grandparent != NULL ? (n->parent == grandparent->left ? grandparent->right : grandparent->left) : NULL;
}

struct node * red_black_tree_node_sibling(struct node * n)
{
    assertion(n == NULL, "[%s:%d:%s] n == NULL", __FILE__, __LINE__, __func__);
    return n->parent != NULL ? (n->parent->left == n ? n->parent->right : n->parent->left) : NULL;
}

struct node * red_black_tree_node_grandparent(struct node * n)
{
    assertion(n == NULL, "[%s:%d:%s] n == NULL", __FILE__, __LINE__, __func__);
    return n->parent != NULL ? n->parent->parent : NULL;
}

int red_black_tree_node_color(struct node * n)
{
    return n != NULL ? n->color : BLACK;
}

