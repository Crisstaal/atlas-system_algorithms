#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>
#include "graphs.h"
#include "queues.h"

/**
 * struct point_s - Structure storing coordinates
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);
queue_t *backtracking_graph(graph_t *graph,
			    vertex_t const *start, vertex_t const *target);
queue_t *dijkstra_graph(graph_t *graph,
			vertex_t const *start, vertex_t const *target);
int queue_is_empty(queue_t *queue);
point_t *queue_pop_front(queue_t *queue);

#endif /* PATHFINDING_H */
