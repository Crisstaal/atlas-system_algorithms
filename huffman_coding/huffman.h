#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include <stddef.h>
/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

int huffman_codes(char *data, size_t *freq, size_t size);
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
symbol_t *symbol_create(char data, size_t freq);

#endif