#include "heap.h"
#include <stdlib.h>

/**
 * heap_create - Creates a new min binary heap
 * @data_cmp: Pointer to the comparison function
 *
 * Return: Pointer to the newly created heap_t structure, or NULL on failure
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap;

	if (data_cmp == NULL)
		return (NULL);

	heap = malloc(sizeof(heap_t));
	if (heap == NULL)
		return (NULL);

	heap->size = 0;
	heap->data_cmp = data_cmp;
	heap->root = NULL;

	return (heap);
}
