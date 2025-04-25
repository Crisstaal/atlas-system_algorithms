#include "nary_trees.h"
#include <string.h>

/**
 * path_exists - Checks if a path exists in an N-ary tree
 * @root: pointer to the root node of the tree
 * @path: NULL-terminated array of strings representing the path
 * Return: 1 if path exists, 0 otherwise
 */
int path_exists(nary_tree_t const *root, char const *const *path)
{
	size_t i;
	nary_tree_t *current;
	nary_tree_t *child;

	if (!root || !path || !path[0])
		return (0);

	if (strcmp(root->content, path[0]) != 0)
		return (0);

	current = (nary_tree_t *)root;

	for (i = 1; path[i]; i++)
	{
		child = current->children;
		current = NULL;
		while (child)
		{
			if (strcmp(child->content, path[i]) == 0)
			{
				current = child;
				break;
			}
			child = child->next;
		}

		if (!current)
			return (0);
	}

	return (1);
}
