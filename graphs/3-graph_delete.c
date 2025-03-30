#include <stdlib.h>
#include "graphs.h"

/**
 * free_edges - Frees all edges of a given vertex
 * @edges: Pointer to the head of the edges list
 */
void free_edges(edge_t *edges)
{
	edge_t *temp;

	while (edges)
	{
		temp = edges;
		edges = edges->next;
		free(temp);
	}
}

/**
 * graph_delete - Deletes an entire graph, freeing all memory
 * @graph: Pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
	vertex_t *temp_vertex;

	if (!graph)
		return;

	while (graph->vertices)
	{
		temp_vertex = graph->vertices;
		graph->vertices = graph->vertices->next;

		free_edges(temp_vertex->edges);
		free(temp_vertex->content);
		free(temp_vertex);
	}

	free(graph);
}
