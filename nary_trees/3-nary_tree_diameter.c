#include "nary_trees.h"

/**
 * max - Returns the greater of two size_t values
 * @a: First value
 * @b: Second value
 *
 * Return: The maximum of a and b
 */
static size_t max(size_t a, size_t b)
{
	return (a > b ? a : b);
}

/**
 * depth_and_diameter - Recursively finds max depth and updates diameter
 * @node: Pointer to current node
 * @diameter: Pointer to current diameter
 *
 * Return: Max depth from this node downward
 */
static size_t depth_and_diameter(const nary_tree_t *node, size_t *diameter)
{
	size_t max1 = 0, max2 = 0, d, depth = 0;
	nary_tree_t *child;

	if (!node)
		return (0);

	child = node->children;
	while (child)
	{
		d = depth_and_diameter(child, diameter);
		if (d > max1)
		{
			max2 = max1;
			max1 = d;
		}
		else if (d > max2)
		{
			max2 = d;
		}
		child = child->next;
	}

	/* Update diameter if this path is longer */
	if (diameter && (max1 + max2) > *diameter)
		*diameter = max1 + max2;

	/* Return depth from this node */
	return (max1 + 1);
}

/**
 * nary_tree_diameter - Computes the diameter of an N-ary tree
 * @root: Pointer to the root node
 *
 * Return: Diameter of the tree
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	if (!root)
		return (0);

	depth_and_diameter(root, &diameter);
	return (diameter);
}
