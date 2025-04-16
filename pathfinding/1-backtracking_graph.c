#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathfinding.h"
#include "queues.h"
#include "graphs.h"

/**
 * backtrack - Recursive helper to find a path from start to target.
 * @vertex: Current vertex.
 * @target: Target vertex.
 * @visited: Array of visited vertex names.
 * @path: Queue representing the current path.
 * Return: 1 if target is found, 0 otherwise.
 */
static int backtrack(vertex_t const *vertex, vertex_t const *target,
		     char **visited, size_t count, queue_t *path)
{
	size_t i;

	if (!vertex || !target || !visited || !path)
		return (0);

	for (i = 0; i < count; i++)
	{
		if (strcmp(visited[i], vertex->content) == 0)
			return (0);
	}

	printf("Checking %s\n", vertex->content);

	visited[count] = (char *)vertex->content;
	queue_push_back(path, strdup(vertex->content));

	if (vertex == target)
		return (1);

	edge_t *edge = vertex->edges;

	while (edge)
	{
		if (backtrack(edge->dest, target, visited, count + 1, path))
			return (1);
		edge = edge->next;
	}

	free(dequeue(path));
	return (0);
}

/**
 * backtracking_graph - Finds a path in a graph using backtracking.
 * @graph: Pointer to the graph.
 * @start: Pointer to the starting vertex.
 * @target: Pointer to the target vertex.
 * Return: Queue representing the path, or NULL on failure.
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start, vertex_t const *target)
{
	char **visited;
	queue_t *path;

	if (!graph || !start || !target)
		return (NULL);

	visited = calloc(graph->nb_vertices + 1, sizeof(char *));
	path = queue_create();

	if (!visited || !path)
	{
		free(visited);
		free(path);
		return (NULL);
	}

	if (!backtrack(start, target, visited, 0, path))
	{
		free(visited);
		while (path->front)
			free(dequeue(path));
		free(path);
		return (NULL);
	}

	free(visited);
	return (path);
}
