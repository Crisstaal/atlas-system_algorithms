#include "heap.h"
#include <stdlib.h>

/**
 * swap_data - Swaps the data between two nodes
 * @a: First node
 * @b: Second node
 */
void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

/**
 * sift_down - Moves the root node down to maintain min-heap property
 * @root: The root node to reorder
 * @data_cmp: Comparison function
 */
void sift_down(binary_tree_node_t *root, int (*data_cmp)(void *, void *))
{
	binary_tree_node_t *smallest, *left, *right;

	while (root)
	{
		smallest = root;
		left = root->left;
		right = root->right;

		if (left && data_cmp(left->data, smallest->data) < 0)
			smallest = left;

		if (right && data_cmp(right->data, smallest->data) < 0)
			smallest = right;

		if (smallest == root)
			break;

		swap_data(root, smallest);
		root = smallest;
	}
}

/**
 * get_last_node - Finds the last node in a heap using level-order
 * @root: Pointer to the root node
 * @size: Size of the heap
 *
 * Return: Pointer to the last node
 */
binary_tree_node_t *get_last_node(binary_tree_node_t *root, size_t size)
{
	binary_tree_node_t *queue[1024];
	size_t front = 0, back = 0;
	size_t i = 1;

	if (root == NULL)
		return (NULL);

	queue[back++] = root;

	while (i < size && front < back)
	{
		binary_tree_node_t *node = queue[front++];

		if (node->left)
		{
			queue[back++] = node->left;
			i++;
			if (i == size)
				return (node->left);
		}
		if (node->right)
		{
			queue[back++] = node->right;
			i++;
			if (i == size)
				return (node->right);
		}
	}

	return (NULL);
}

/**
 * heap_extract - Extracts the root value from a Min Binary Heap
 * @heap: Pointer to the heap
 *
 * Return: Pointer to extracted data, or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last, *parent;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last = get_last_node(heap->root, heap->size);
	if (!last)
		return (NULL);

	/* Swap last node's data into root */
	heap->root->data = last->data;

	parent = last->parent;
	if (parent->left == last)
		parent->left = NULL;
	else if (parent->right == last)
		parent->right = NULL;

	free(last);
	heap->size--;

	sift_down(heap->root, heap->data_cmp);

	return (data);
}
