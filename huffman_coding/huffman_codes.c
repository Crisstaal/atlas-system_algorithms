#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>

void huffman_codes_recursive(binary_tree_node_t *node, char *code);

/**
 * huffman_codes_recursive - Recursive function to traverse the Huffman tree
 * @node: The current node of the Huffman tree
 * @code: The current Huffman code being built
 */
void huffman_codes_recursive(binary_tree_node_t *node, char *code)
{
	symbol_t *symbol;
	char left_code[1024];
	char right_code[1024];

	if (!node)
		return;

	symbol = (symbol_t *)node->data;

	/* Check if it is a leaf node */
	if (symbol && symbol->data != -1) /* Leaf node */
	{
		printf("%c: %s\n", symbol->data, code);
		return;
	}

	/* If internal node, append '0' for left child and '1' for right child */
	snprintf(left_code, sizeof(left_code), "%s0", code);
	snprintf(right_code, sizeof(right_code), "%s1", code);

	/* Recursively go left and right */
	huffman_codes_recursive(node->left, left_code);
	huffman_codes_recursive(node->right, right_code);
}

/**
 * huffman_codes - Builds the Huffman tree and prints the Huffman codes for each symbol
 * @data: Array of characters
 * @freq: Array of frequencies corresponding to the characters
 * @size: Size of the data and freq arrays
 *
 * Return: 1 if successful, 0 if failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;

	/* Build the Huffman tree */
	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	/* Start the recursive process to print the codes */
	huffman_codes_recursive(root, "");

	return (1);
}
