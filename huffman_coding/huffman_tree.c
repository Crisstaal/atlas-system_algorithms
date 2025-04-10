#include "huffman.h"
#include "heap.h"
#include <stdlib.h>

/**
 * huffman_tree - Builds the Huffman tree from a given set of symbols and frequencies
 * @data: Array of characters
 * @freq: Array of frequencies corresponding to the characters
 * @size: Size of the data and freq arrays
 *
 * Return: Pointer to the root of the Huffman tree, or NULL if it fails
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
    heap_t *priority_queue;
    binary_tree_node_t *root;

    /* Create the priority queue (min heap) from the given data and frequencies */
    priority_queue = huffman_priority_queue(data, freq, size);
    if (!priority_queue)
        return (NULL);

    /* Extract two nodes and insert a new one until there's only one node left */
    while (priority_queue->size > 1)
    {
        if (!huffman_extract_and_insert(priority_queue))
        {
            heap_delete(priority_queue, NULL);
            return (NULL);
        }
    }

    /* The last remaining node is the root of the Huffman tree */
    root = priority_queue->root;

    /* Clean up the priority queue since we no longer need it */
    heap_delete(priority_queue, NULL);

    return (root);
}
