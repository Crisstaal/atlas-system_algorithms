#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * heap_insert - Inserts a new node into the heap
 * @heap: Pointer to the heap structure
 * @data: Pointer to the data to insert
 *
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
    binary_tree_node_t *new_node = NULL;

    if (heap == NULL || data == NULL)
        return (NULL);

    /* Create the new node */
    new_node = binary_tree_node(NULL, data);
    if (new_node == NULL)
        return (NULL);

    /* If the heap is empty, the new node becomes the root */
    if (heap->root == NULL)
    {
        heap->root = new_node;
        heap->size++;
        return (new_node);
    }

    /* Insert the new node in the leftmost available spot */
    insert_level_order(heap->root, new_node);

    /* Heapify-up to restore the heap property */
    heapify_up(new_node, heap->data_cmp);

    heap->size++;
    return (new_node);
}

/**
 * insert_level_order - Inserts a node into the heap in level-order
 * @root: The root of the heap
 * @new_node: The node to insert
 */
static void insert_level_order(binary_tree_node_t *root, binary_tree_node_t *new_node)
{
    binary_tree_node_t *queue[1024]; /* Queue for level-order traversal */
    int front = 0, rear = 0;
    binary_tree_node_t *current = NULL;

    /* Begin level-order traversal */
    queue[rear++] = root;

    while (front < rear)
    {
        current = queue[front++];

        /* Check if left child is available */
        if (current->left == NULL)
        {
            current->left = new_node;
            new_node->parent = current;
            return;
        }
        else
            queue[rear++] = current->left;

        /* Check if right child is available */
        if (current->right == NULL)
        {
            current->right = new_node;
            new_node->parent = current;
            return;
        }
        else
            queue[rear++] = current->right;
    }
}

/**
 * heapify_up - Restores the heap property by moving the node up the heap
 * @node: The newly inserted node
 * @data_cmp: The comparison function used to compare node data
 */
static void heapify_up(binary_tree_node_t *node, int (*data_cmp)(void *, void *))
{
    binary_tree_node_t *parent = NULL;

    while (node && node->parent)
    {
        parent = node->parent;

        /* Compare node's data with its parent's data */
        if (data_cmp(node->data, parent->data) < 0) /* Min-heap condition */
        {
            swap_data(node, parent);
            node = parent;
        }
        else
            break;
    }
}

/**
 * swap_data - Swaps the data of two nodes
 * @a: The first node
 * @b: The second node
 */
static void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
    void *tmp;

    tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}
