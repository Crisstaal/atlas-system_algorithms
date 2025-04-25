#include "nary_trees.h"

/**
 * traverse_helper - Helper to recursively traverse the N-ary tree
 *
 * @node: Current node
 * @action: Function to call on each node
 * @depth: Current depth level
 *
 * Return: Maximum depth reached
 */
static size_t traverse_helper(nary_tree_t const *node,
			      void (*action)(nary_tree_t const *node, size_t depth),
			      size_t depth)
{
	size_t max_depth = depth, child_depth;
	nary_tree_t *child;

	if (!node)
		return (0);

	if (action)
		action(node, depth);

	child = node->children;
	while (child)
	{
		child_depth = traverse_helper(child, action, depth + 1);
		if (child_depth > max_depth)
			max_depth = child_depth;
		child = child->next;
	}

	return (max_depth);
}

/**
 * nary_tree_traverse - Traverses an N-ary tree, node by node
 *
 * @root: Pointer to the root node
 * @action: Function to call for each node
 *
 * Return: Maximum depth of the tree
 */
size_t nary_tree_traverse(
    nary_tree_t const *root,
    void (*action)(nary_tree_t const *node, size_t depth))
{
	if (!root)
		return (0);

	return (traverse_helper(root, action, 0));
}
