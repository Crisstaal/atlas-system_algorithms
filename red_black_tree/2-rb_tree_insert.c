#include "rb_trees.h"
#include <stdlib.h>

/**
 * rb_rotate_left - Performs a left rotation on a Red-Black Tree
 * @tree: Double pointer to the root node
 * @node: Node to rotate
 */
void rb_rotate_left(rb_tree_t **tree, rb_tree_t *node)
{
    rb_tree_t *right_child = node->right;
    
    if (!right_child)
        return;
    
    node->right = right_child->left;
    if (right_child->left)
        right_child->left->parent = node;
    
    right_child->parent = node->parent;
    if (!node->parent)
        *tree = right_child;
    else if (node == node->parent->left)
        node->parent->left = right_child;
    else
        node->parent->right = right_child;
    
    right_child->left = node;
    node->parent = right_child;
}

/**
 * rb_rotate_right - Performs a right rotation on a Red-Black Tree
 * @tree: Double pointer to the root node
 * @node: Node to rotate
 */
void rb_rotate_right(rb_tree_t **tree, rb_tree_t *node)
{
    rb_tree_t *left_child = node->left;
    
    if (!left_child)
        return;
    
    node->left = left_child->right;
    if (left_child->right)
        left_child->right->parent = node;
    
    left_child->parent = node->parent;
    if (!node->parent)
        *tree = left_child;
    else if (node == node->parent->right)
        node->parent->right = left_child;
    else
        node->parent->left = left_child;
    
    left_child->right = node;
    node->parent = left_child;
}

/**
 * rb_insert_fixup - Fixes the Red-Black properties after insertion
 * @tree: Double pointer to the root node
 * @node: Newly inserted node
 */
void rb_insert_fixup(rb_tree_t **tree, rb_tree_t *node)
{
    rb_tree_t *parent, *grandparent, *uncle;
    
    while (node->parent && node->parent->color == RED)
    {
        parent = node->parent;
        grandparent = parent->parent;
        
        if (parent == grandparent->left)
        {
            uncle = grandparent->right;
            if (uncle && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else
            {
                if (node == parent->right)
                {
                    node = parent;
                    rb_rotate_left(tree, node);
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rb_rotate_right(tree, grandparent);
            }
        }
        else
        {
            uncle = grandparent->left;
            if (uncle && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else
            {
                if (node == parent->left)
                {
                    node = parent;
                    rb_rotate_right(tree, node);
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rb_rotate_left(tree, grandparent);
            }
        }
    }
    (*tree)->color = BLACK;
}

/**
 * rb_tree_insert - Inserts a value into a Red-Black Tree
 * @tree: Double pointer to the root node
 * @value: Value to insert
 *
 * Return: Pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
    rb_tree_t *new_node, *parent = NULL, *current;
    
    if (!tree)
        return (NULL);
    
    current = *tree;
    while (current)
    {
        parent = current;
        if (value < current->n)
            current = current->left;
        else if (value > current->n)
            current = current->right;
        else
            return (NULL);
    }
    
    new_node = rb_tree_node(parent, value, RED);
    if (!new_node)
        return (NULL);
    
    if (!parent)
        *tree = new_node;
    else if (value < parent->n)
        parent->left = new_node;
    else
        parent->right = new_node;
    
    rb_insert_fixup(tree, new_node);
    return (new_node);
}
