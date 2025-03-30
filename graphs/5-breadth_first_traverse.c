#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphs.h"

/**
 * queue_node_s - Structure for a queue node
 * @vertex: Pointer to the graph vertex
 * @depth: Depth of the vertex in traversal
 * @next: Pointer to the next queue node
 */
typedef struct queue_node_s
{
	const vertex_t *vertex;
	size_t depth;
	struct queue_node_s *next;
} queue_node_t;

/**
 * enqueue - Adds a vertex to the queue
 * @head: Pointer to the queue head
 * @tail: Pointer to the queue tail
 * @vertex: Vertex to enqueue
 * @depth: Depth of the vertex
 * Return: 1 on success, 0 on failure
 */
int enqueue(queue_node_t **head, queue_node_t **tail, const vertex_t *vertex, size_t depth)
{
	queue_node_t *new_node = malloc(sizeof(queue_node_t));

	if (!new_node)
		return (0);
	new_node->vertex = vertex;
	new_node->depth = depth;
	new_node->next = NULL;

	if (*tail)
		(*tail)->next = new_node;
	else
		*head = new_node;
	*tail = new_node;

	return (1);
}

/**
 * dequeue - Removes a vertex from the queue
 * @head: Pointer
 * @tail: Pointer
 * Return: Pointer to the dequeued vertex, or NULL if empty
 */
queue_node_t *dequeue(queue_node_t **head, queue_node_t **tail)
{
	queue_node_t *node = *head;

	if (!node)
		return (NULL);

	*head = node->next;
	if (!*head)
		*tail = NULL;

	return (node);
}

/**
 * free_queue - Frees the entire queue
 * @head: Pointer to the queue head
 */
void free_queue(queue_node_t *head)
{
	queue_node_t *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

/**
 * breadth_first_traverse - Traverses a graph using BFS
 * @graph: Pointer to the graph
 * @action: Function to execute on each vertex
 * Return: Maximum depth reached, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *, size_t))
{
	int *visited;
	size_t max_depth = 0;
	queue_node_t *head = NULL, *tail = NULL, *node;
	edge_t *edge;

	if (!graph || !graph->vertices || !action)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(int));
	if (!visited)
		return (0);

	enqueue(&head, &tail, graph->vertices, 0);

	while ((node = dequeue(&head, &tail)))
	{
		if (visited[node->vertex->index])
		{
			free(node);
			continue;
		}

		visited[node->vertex->index] = 1;
		action(node->vertex, node->depth);
		if (node->depth > max_depth)
			max_depth = node->depth;

		for (edge = node->vertex->edges; edge; edge = edge->next)
			if (!visited[edge->dest->index])
				enqueue(&head, &tail, edge->dest, node->depth + 1);

		free(node);
	}

	free(visited);
	free_queue(head);

	return (max_depth);
}
