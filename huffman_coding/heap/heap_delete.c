#include "heap.h"
#include <stdlib.h>

/**
 * delete_nodes - Recursively deletes all nodes in the heap
 * @node: Pointer to the current node
 * @free_data: Function pointer to free node data, or NULL
 */
void delete_nodes(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;

	delete_nodes(node->left, free_data);
	delete_nodes(node->right, free_data);

	if (free_data)
		free_data(node->data);

	free(node);
}

/**
 * heap_delete - Deletes a Min Binary Heap and its nodes
 * @heap: Pointer to the heap
 * @free_data: Function to free the node data, or NULL
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	delete_nodes(heap->root, free_data);
	free(heap);
}
