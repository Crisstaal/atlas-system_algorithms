#include "rb_trees.h"
#include <stdlib.h>
void rb_rotate_left(rb_tree_t **tree, rb_tree_t *node);
void rb_rotate_right(rb_tree_t **tree, rb_tree_t *node);

/**
 * rb_tree_node - Creates a new node in a Red-Black Tree
 * @parent: Pointer to the parent node
 * @value: Value to insert into the node
 * @color: The color of the node (either RED or BLACK)
 *
 * Return: A pointer to the new node, or NULL on failure
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new_node = malloc(sizeof(rb_tree_t));

	/** Return NULL if memory allocation fails **/
	if (!new_node)
		return (NULL);

	new_node->n = value;
	new_node->color = color;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}

/**
 * rb_insert_fixup - Fixes the Red-Black properties after insertion
 * @tree: Double pointer to the root node
 * @node: Newly inserted node
 */
void rb_insert_fixup(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *parent, *grandparent, *uncle;

	/** Iterate while the parent of node is red **/
	while (node->parent && node->parent->color == RED)
	{
		parent = node->parent;
		grandparent = parent->parent;

		/** If the parent is the left child of the grandparent **/
		if (parent == grandparent->left)
		{
			uncle = grandparent->right;
			if (uncle && uncle->color == RED)
			{
				/** Case 1: Uncle is RED **/
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				node = grandparent;
			}
			else
			{
				/** Case 2: Uncle is BLACK or NULL **/
				if (node == parent->right)
				{
					node = parent;
					rb_rotate_left(tree, node); /** Left rotate at parent **/
				}
				parent->color = BLACK;
				grandparent->color = RED;
				rb_rotate_right(tree, grandparent); /** Right rotate at grandparent **/
			}
		}
		/** If the parent is the right child of the grandparent **/
		else
		{
			uncle = grandparent->left;
			if (uncle && uncle->color == RED)
			{
				/** Case 1: Uncle is RED **/
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				node = grandparent;
			}
			else
			{
				/** Case 2: Uncle is BLACK or NULL **/
				if (node == parent->left)
				{
					node = parent;
					rb_rotate_right(tree, node); /** Right rotate at parent **/
				}
				parent->color = BLACK;
				grandparent->color = RED;
				rb_rotate_left(tree, grandparent); /** Left rotate at grandparent **/
			}
		}
	}
	/** Ensure the root is always black **/
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

	/** Return NULL if tree is NULL **/
	if (!tree)
		return (NULL);

	current = *tree;
	/** Find the correct position for the new node **/
	while (current)
	{
		parent = current;
		if (value < current->n)
			current = current->left;
		else if (value > current->n)
			current = current->right;
		else
			return (NULL); /** Value already exists **/
	}

	/** Create a new node **/
	new_node = rb_tree_node(parent, value, RED);
	if (!new_node)
		return (NULL);

	/** Insert the new node into the tree **/
	if (!parent)
		*tree = new_node; /** Tree is empty, new node becomes root **/
	else if (value < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;

	/** Fix the Red-Black Tree properties **/
	rb_insert_fixup(tree, new_node);
	return (new_node);
}
