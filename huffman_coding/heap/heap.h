#ifndef _HEAP_H_
#define _HEAP_H_

#include <stddef.h>


/**
 * struct binary_tree_node_s - Binary tree node data structure
 *
 * @data: Data stored in a node
 * @left: Pointer to the left child
 * @right: Pointer to the right child
 * @parent: Pointer to the parent node
 */
typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} binary_tree_node_t;

/**
 * struct heap_s - Heap data structure
 *
 * @size: Size of the heap (number of nodes)
 * @data_cmp: Function to compare two nodes data
 * @root: Pointer to the root node of the heap
 */
typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	binary_tree_node_t *root;
} heap_t;
/**
 * swap_data - Swaps the data pointers of two nodes
 * @a: First node
 * @b: Second node
 */


void heap_delete(heap_t *heap, void (*free_data)(void *));
void *heap_extract(heap_t *heap);
static void insert_level_order(binary_tree_node_t *root, binary_tree_node_t *new_node);
static void heapify_up(binary_tree_node_t *node, int (*data_cmp)(void *, void *));
static void swap_data(binary_tree_node_t *a, binary_tree_node_t *b);
binary_tree_node_t *heap_insert(heap_t *heap, void *data);
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);
heap_t *heap_create(int (*data_cmp)(void *, void *));

#endif
