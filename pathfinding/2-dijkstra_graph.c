#include "pathfinding.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/**
 * struct dijkstra_node_s - Struct to store Dijkstra data
 * @vertex: Pointer to the graph vertex
 * @distance: Shortest known distance from the start
 * @prev: Pointer to previous vertex in the shortest path
 * @visited: Flag indicating if the vertex was visited
 */
typedef struct dijkstra_node_s
{
	vertex_t *vertex;
	size_t distance;
	vertex_t *prev;
	int visited;
} dijkstra_node_t;

/**
 * get_node_by_vertex - Finds the node data associated with a vertex
 * @nodes: Array of all dijkstra_node_t
 * @vertex: Target vertex
 * @size: Number of nodes
 * Return: Pointer to the found dijkstra_node_t, or NULL
 */
static dijkstra_node_t *get_node_by_vertex(dijkstra_node_t *nodes,
					   const vertex_t *vertex, size_t size)
{
	for (size_t i = 0; i < size; i++)
		if (nodes[i].vertex == vertex)
			return &nodes[i];
	return (NULL);
}

/**
 * get_closest_unvisited - Finds the closest unvisited node
 * @nodes: Array of dijkstra_node_t
 * @size: Number of nodes
 * Return: Pointer to the closest unvisited node
 */
static dijkstra_node_t *get_closest_unvisited(dijkstra_node_t *nodes, size_t size)
{
	dijkstra_node_t *min = NULL;

	for (size_t i = 0; i < size; i++)
	{
		if (!nodes[i].visited &&
		    (!min || nodes[i].distance < min->distance))
			min = &nodes[i];
	}
	return (min);
}

/**
 * build_path - Builds path queue from target to start
 * @nodes: Dijkstra nodes
 * @size: Total number of nodes
 * @start: Starting vertex
 * @target: Target vertex
 * Return: Queue with the path, or NULL on failure
 */
static queue_t *build_path(dijkstra_node_t *nodes, size_t size,
			   const vertex_t *start, const vertex_t *target)
{
	queue_t *path = queue_create();
	dijkstra_node_t *node = get_node_by_vertex(nodes, target, size);
	char *name;

	if (!path)
		return (NULL);

	while (node)
	{
		name = strdup(node->vertex->content);
		if (!name || !queue_push_front(path, name))
		{
			free(name);
			queue_delete(path);
			return (NULL);
		}
		if (node->vertex == start)
			break;
		node = get_node_by_vertex(nodes, node->prev, size);
	}
	return (path);
}

/**
 * dijkstra_graph - Finds the shortest path using Dijkstra’s algorithm
 * @graph: Pointer to the graph
 * @start: Starting vertex
 * @target: Target vertex
 * Return: Queue with shortest path or NULL
 */
queue_t *dijkstra_graph(graph_t *graph, const vertex_t *start,
			const vertex_t *target)
{
	vertex_t *v;
	dijkstra_node_t *nodes;
	dijkstra_node_t *current, *neighbor;
	edge_t *edge;
	size_t count = 0;

	if (!graph || !start || !target)
		return (NULL);

	for (v = graph->vertices; v; v = v->next)
		count++;

	nodes = calloc(count, sizeof(*nodes));
	if (!nodes)
		return (NULL);

	v = graph->vertices;
	for (size_t i = 0; i < count; i++, v = v->next)
	{
		nodes[i].vertex = v;
		nodes[i].distance = (v == start) ? 0 : SIZE_MAX;
		nodes[i].prev = NULL;
		nodes[i].visited = 0;
	}

	while ((current = get_closest_unvisited(nodes, count)))
	{
		current->visited = 1;
		printf("Checking %s, distance from %s is %lu\n",
		       current->vertex->content, start->content, current->distance);

		if (current->vertex == target)
			break;

		for (edge = current->vertex->edges; edge; edge = edge->next)
		{
			neighbor = get_node_by_vertex(nodes, edge->dest, count);
			if (!neighbor || neighbor->visited)
				continue;
			if (current->distance + edge->weight < neighbor->distance)
			{
				neighbor->distance = current->distance + edge->weight;
				neighbor->prev = current->vertex;
			}
		}
	}

	queue_t *path = build_path(nodes, count, start, target);
	free(nodes);
	return (path);
}
