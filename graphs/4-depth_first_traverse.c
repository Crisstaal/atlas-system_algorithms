#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphs.h"

/**
 * dfs_helper - Helper function to perform DFS traversal recursively
 * @vertex: Current vertex being visited
 * @visited: Array tracking visited vertices
 * @depth: Current depth of traversal
 * @action: Function to execute on each vertex
 * @max_depth: Pointer to store the maximum depth reached
 */
void dfs_helper(const vertex_t *vertex, int *visited, size_t depth,
		void (*action)(const vertex_t *, size_t), size_t *max_depth)
{
	edge_t *edge;

	if (!vertex || visited[vertex->index])
		return;

	visited[vertex->index] = 1;
	action(vertex, depth);
	if (depth > *max_depth)
		*max_depth = depth;

	for (edge = vertex->edges; edge; edge = edge->next)
		dfs_helper(edge->dest, visited, depth + 1, action, max_depth);
}

/**
 * depth_first_traverse - Traverses a graph using depth-first search
 * @graph: Pointer to the graph to traverse
 * @action: Function to be called for each visited vertex
 * Return: The maximum depth reached, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *, size_t))
{
	int *visited;
	size_t max_depth = 0;

	if (!graph || !graph->vertices || !action)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(int));
	if (!visited)
		return (0);

	dfs_helper(graph->vertices, visited, 0, action, &max_depth);
	free(visited);

	return (max_depth);
}
