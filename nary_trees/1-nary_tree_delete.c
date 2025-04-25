#include <stdlib.h>
#include "nary_trees.h"

/**
 * nary_tree_delete - Deallocates an entire N-ary tree
 *
 * @tree: Pointer to the root node of the tree
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *child, *next;

	if (!tree)
		return;

	child = tree->children;
	while (child)
	{
		next = child->next;
		nary_tree_delete(child);
		child = next;
	}

	free(tree->content);
	free(tree);
}
