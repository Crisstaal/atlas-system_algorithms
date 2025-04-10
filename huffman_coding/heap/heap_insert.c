#include "heap.h"
#include <stdlib.h>

/**
 * swap_data - Swaps the data pointers of two nodes
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
 * sift_up - Moves a node up to maintain min-heap property
 * @node: Node to sift up
 * @data_cmp: Comparison function
 */
void sift_up(binary_tree_node_t *node, int (*data_cmp)(void *, void *))
{
	while (node->parent && data_cmp(node->data, node->parent->data) < 0)
	{
		swap_data(node, node->parent);
		node = node->parent;
	}
}

/**
 * get_insertion_parent - Finds the parent where the new node should be inserted
 * @root: Pointer to the root node
 * @size: Current size of the heap
 *
 * Return: Pointer to the parent node where insertion should happen
 */
binary_tree_node_t *get_insertion_parent(binary_tree_node_t *root, size_t size)
{
	binary_tree_node_t *queue[1024];
	size_t front = 0, back = 0;

	if (root == NULL)
		return (NULL);

	queue[back++] = root;

	while (front < back)
	{
		binary_tree_node_t *node = queue[front++];

		if (node->left == NULL || node->right == NULL)
			return (node);

		queue[back++] = node->left;
		queue[back++] = node->right;
	}

	return (NULL);
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap
 * @data: Data to insert
 *
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node, *parent;

	if (heap == NULL || data == NULL)
		return (NULL);

	if (heap->root == NULL)
	{
		heap->root = binary_tree_node(NULL, data);
		if (heap->root == NULL)
			return (NULL);
		heap->size++;
		return (heap->root);
	}

	parent = get_insertion_parent(heap->root, heap->size + 1);
	if (parent == NULL)
		return (NULL);

	node = binary_tree_node(parent, data);
	if (node == NULL)
		return (NULL);

	if (parent->left == NULL)
		parent->left = node;
	else
		parent->right = node;

	sift_up(node, heap->data_cmp);
	heap->size++;

	return (node);
}
