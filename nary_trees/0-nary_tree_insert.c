#include <stdlib.h>
#include <string.h>
#include "nary_trees.h"

/**
 * nary_tree_insert - Inserts a node into an N-ary tree
 *
 * @parent: Pointer to the parent node
 * @str: String to store in the new node (must be duplicated)
 *
 * Return: Pointer to the created node, or NULL on failure
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node;
	char *dup_str;

	if (!str)
		return (NULL);

	dup_str = strdup(str);
	if (!dup_str)
		return (NULL);

	new_node = malloc(sizeof(nary_tree_t));
	if (!new_node)
	{
		free(dup_str);
		return (NULL);
	}

	new_node->content = dup_str;
	new_node->parent = parent;
	new_node->nb_children = 0;
	new_node->children = NULL;

	if (parent)
	{
		new_node->next = parent->children;
		parent->children = new_node;
		parent->nb_children++;
	}
	else
	{
		new_node->next = NULL;
	}

	return (new_node);
}
