#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - Adds a new vertex to the graph
 *
 * @graph: Pointer to the graph to add the vertex to
 * @str: String to store in the new vertex
 *
 * Return: Pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex, *temp;
	size_t index = 0;

	if (!graph || !str)
		return (NULL);

	/* Check if vertex already exists */
	for (temp = graph->vertices; temp; temp = temp->next)
	{
		if (strcmp(temp->content, str) == 0)
			return (NULL);
		index++;
	}

	/* Allocate and initialize new vertex */
	new_vertex = malloc(sizeof(vertex_t));
	if (!new_vertex)
		return (NULL);

	new_vertex->content = strdup(str);
	if (!new_vertex->content)
	{
		free(new_vertex);
		return (NULL);
	}

	new_vertex->index = graph->nb_vertices;
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	/* Add to adjacency list */
	if (!graph->vertices)
		graph->vertices = new_vertex;
	else
	{
		temp = graph->vertices;
		while (temp->next)
			temp = temp->next;
		temp->next = new_vertex;
	}

	graph->nb_vertices++;

	return (new_vertex);
}
