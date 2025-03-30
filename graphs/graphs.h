#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

/**
 * struct vertex_s - Structure for a graph vertex (node)
 * @index: Index of the vertex in the adjacency list (unique)
 * @content: Name or data of the vertex (e.g., city name)
 * @nb_edges: Number of edges connected to the vertex
 * @edges: Pointer to the first edge (adjacency list)
 * @next: Pointer to the next vertex in the adjacency list
 */
typedef struct vertex_s
{
	size_t index;
	char *content;
	size_t nb_edges;
	struct edge_s *edges;
	struct vertex_s *next;
} vertex_t;

/**
 * struct edge_s - Structure for a graph edge (connection)
 * @dest: Pointer to the destination vertex
 * @next: Pointer to the next edge in the adjacency list
 */
typedef struct edge_s
{
	struct vertex_s *dest;
	struct edge_s *next;
} edge_t;

/**
 * struct graph_s - Graph structure
 * @nb_vertices: Number of vertices in the graph
 * @vertices: Pointer to the head of the adjacency list
 */
typedef struct graph_s
{
	size_t nb_vertices;
	struct vertex_s *vertices;
} graph_t;

/* Graph functions */
graph_t *graph_create(void);
void graph_delete(graph_t *graph);
vertex_t *graph_add_vertex(graph_t *graph, const char *content);
int graph_add_edge(graph_t *graph, const char *src, const char *dest, int type);
void graph_display(const graph_t *graph);

/* Traversal functions */
size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *, size_t));
size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *, size_t));

/* Edge type */
#define UNIDIRECTIONAL 0
#define BIDIRECTIONAL 1

#endif /* GRAPHS_H */
