#include "rb_trees.h"
#include <limits.h>

/**
 * is_bst - Checks if a tree is a valid Binary Search Tree
 * @tree: Pointer to the root node
 * @min: Minimum value
 * @max: Maximum value
 *
 * Return: 1 if valid BST, 0 otherwise
 */

int is_bst(const rb_tree_t *tree, int min, int max)
{
	if (!tree)
		return (1);
	if (tree->n <= min || tree->n >= max)
		return (0);
	return (is_bst(tree->left, min, tree->n) && is_bst(tree->right, tree->n, max));
}

/**
 * validate_rb_properties - Validates Red-Black properties
 * @tree: Pointer to the root node
 * @black_count: Black node
 * @path_black_count: Black count
 *
 * Return: 1 if valid, 0 otherwise
 */

int validate_rb_properties(const rb_tree_t *tree, int *black_count, int path_black_count)
{
	if (!tree)
	{
		if (*black_count == -1)
			*black_count = path_black_count;
		return (*black_count == path_black_count);
	}
	if (tree->color == RED)
	{
		if ((tree->left && tree->left->color == RED) ||
		    (tree->right && tree->right->color == RED))
			return (0);
	}
	else
		path_black_count++;
	return (validate_rb_properties(tree->left, black_count, path_black_count) &&
		validate_rb_properties(tree->right, black_count, path_black_count));
}

/**
 * rb_tree_is_valid - Checks if a binary tree is a valid Red-Black Tree
 * @tree: Pointer to the root node
 *
 * Return: 1 if tree is a valid Red-Black Tree, 0 otherwise
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int black_count = -1;

	if (!tree || tree->color != BLACK)
		return (0);
	if (!is_bst(tree, INT_MIN, INT_MAX))
		return (0);
	return (validate_rb_properties(tree, &black_count, 0));
}
