#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * find_vertex - Finds a vertex in the graph by its content
 * @graph: Pointer to the graph
 * @str: String to search for
 * Return: Pointer to the vertex if found, NULL otherwise
 */
vertex_t *find_vertex(graph_t *graph, const char *str)
{
	vertex_t *temp;

	for (temp = graph->vertices; temp; temp = temp->next)
		if (strcmp(temp->content, str) == 0)
			return (temp);
	return (NULL);
}

/**
 * add_edge - Adds an edge to a vertex's adjacency list
 * @vertex: Pointer to the source vertex
 * @dest: Pointer to the destination vertex
 * Return: 1 on success, 0 on failure
 */
int add_edge(vertex_t *vertex, vertex_t *dest)
{
	edge_t *new_edge, *temp;

	new_edge = malloc(sizeof(edge_t));
	if (!new_edge)
		return (0);

	new_edge->dest = dest;
	new_edge->next = NULL;

	/* Append to the edge list */
	if (!vertex->edges)
		vertex->edges = new_edge;
	else
	{
		temp = vertex->edges;
		while (temp->next)
			temp = temp->next;
		temp->next = new_edge;
	}

	vertex->nb_edges++;
	return (1);
}

/**
 * graph_add_edge - Adds an edge between two vertices
 * @graph: Pointer to the graph
 * @src: String identifying the source vertex
 * @dest: String identifying the destination vertex
 * @type: Type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
	vertex_t *src_vertex, *dest_vertex;

	if (!graph || !src || !dest)
		return (0);

	src_vertex = find_vertex(graph, src);
	dest_vertex = find_vertex(graph, dest);
	if (!src_vertex || !dest_vertex)
		return (0);

	/* Add edge from src to dest */
	if (!add_edge(src_vertex, dest_vertex))
		return (0);

	/* If BIDIRECTIONAL, add edge from dest to src */
	if (type == BIDIRECTIONAL)
		if (!add_edge(dest_vertex, src_vertex))
			return (0);

	return (1);
}
