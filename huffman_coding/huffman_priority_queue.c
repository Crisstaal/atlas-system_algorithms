#include "huffman.h"
#include "heap.h"
#include <stdlib.h>

/**
 * node_cmp - Compares two binary tree nodes by symbol frequency
 * @p1: Pointer to the first binary tree node
 * @p2: Pointer to the second binary tree node
 *
 * Return: Difference in frequency (used by min-heap)
 */
int node_cmp(void *p1, void *p2)
{
	symbol_t *s1, *s2;

	s1 = ((binary_tree_node_t *)p1)->data;
	s2 = ((binary_tree_node_t *)p2)->data;

	return ((int)(s1->freq - s2->freq));
}

/**
 * huffman_priority_queue - Builds a priority queue for Huffman coding
 * @data: Array of characters
 * @freq: Array of frequencies
 * @size: Size of the arrays
 *
 * Return: Pointer to created min heap (priority queue), or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *symbol;
	binary_tree_node_t *node;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);

	heap = heap_create(node_cmp);
	if (!heap)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
		{
			heap_delete(heap, NULL);
			return (NULL);
		}

		node = binary_tree_node(NULL, symbol);
		if (!node || !heap_insert(heap, node))
		{
			free(symbol);
			free(node);
			heap_delete(heap, NULL);
			return (NULL);
		}
	}

	return (heap);
}
