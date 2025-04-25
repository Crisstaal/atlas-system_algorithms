#include "nary_trees.h"
#include <stdlib.h>

/**
 * max - Returns the maximum of two numbers
 * @a: first number
 * @b: second number
 * Return: the larger number
 */
static size_t max(size_t a, size_t b)
{
	return (a > b ? a : b);
}

/**
 * dfs - Depth-first search to compute height and diameter
 * @node: current node
 * @diameter: pointer to store the maximum diameter
 * Return: height of the node
 */
static size_t dfs(nary_tree_t const *node, size_t *diameter)
{
	size_t first_max = 0, second_max = 0, height = 0;
	nary_tree_t *child = NULL;
	size_t h;

	if (!node)
		return (0);

	child = node->children;
	while (child)
	{
		h = dfs(child, diameter);
		if (h > first_max)
		{
			second_max = first_max;
			first_max = h;
		}
		else if (h > second_max)
		{
			second_max = h;
		}
		child = child->next;
	}

	/* The diameter is the largest path between any two nodes */
	*diameter = max(*diameter, first_max + second_max);
	height = 1 + first_max;
	return height;
}

/**
 * nary_tree_diameter - Computes the diameter of an N-ary tree
 * @root: pointer to the root node
 * Return: the diameter of the tree
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	if (!root)
		return (0);

	dfs(root, &diameter);
	return diameter;
}
