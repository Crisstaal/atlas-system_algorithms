#include "graphs.h"

/**
 * graph_add_edge - Adds an edge between two vertices in the graph
 * @graph: A pointer to the graph to add the edge to
 * @src: The string identifying the source vertex
 * @dest: The string identifying the destination vertex
 * @type: The type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 * 
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
    vertex_t *src_vertex;
    vertex_t *dest_vertex;
    edge_t *new_edge;

    src_vertex = graph_find_vertex(graph, src);
    dest_vertex = graph_find_vertex(graph, dest);

    if (!src_vertex || !dest_vertex)
    {
        return (0);
    }

    new_edge = malloc(sizeof(edge_t));
    if (!new_edge)
    {
        return (0);
    }

    new_edge->dest = dest_vertex;
    new_edge->next = src_vertex->edges;
    src_vertex->edges = new_edge;

    if (type == BIDIRECTIONAL)
    {
        new_edge = malloc(sizeof(edge_t));
        if (!new_edge)
        {
            return (0);
        }

        new_edge->dest = src_vertex;
        new_edge->next = dest_vertex->edges;
        dest_vertex->edges = new_edge;
    }

    return (1);
}
