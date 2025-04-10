#include "huffman.h"
#include "heap.h"
#include <stdlib.h>

/**
 * huffman_extract_and_insert - Extracts two nodes from the priority queue and inserts a new node
 * @priority_queue: Pointer to the priority queue (min heap)
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new_node;
	symbol_t *symbol1, *symbol2;
	symbol_t *new_symbol;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	/* Extract the two least frequent nodes */
	node1 = heap_extract(priority_queue);
	if (!node1)
		return (0);
	node2 = heap_extract(priority_queue);
	if (!node2)
	{
		heap_insert(priority_queue, node1); /* Reinsert the first node if second extraction fails */
		return (0);
	}

	/* Get the symbols from the extracted nodes */
	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;

	/* Create a new symbol with frequency being the sum of the two extracted nodes */
	new_symbol = symbol_create(-1, symbol1->freq + symbol2->freq);
	if (!new_symbol)
	{
		free(node1);
		free(node2);
		return (0);
	}

	/* Create a new binary tree node for the new symbol */
	new_node = binary_tree_node(NULL, new_symbol);
	if (!new_node)
	{
		free(new_symbol);
		free(node1);
		free(node2);
		return (0);
	}

	/* Set the two extracted nodes as the left and right children of the new node */
	new_node->left = node1;
	new_node->right = node2;

	/* Insert the new node back into the priority queue */
	if (!heap_insert(priority_queue, new_node))
	{
		free(new_symbol);
		free(node1);
		free(node2);
		free(new_node);
		return (0);
	}

	return (1);
}
