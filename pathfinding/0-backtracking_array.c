#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"
#include "queues.h"

/**
 * backtrack - Recursive helper to explore the maze
 *
 * @map: 2D array of chars representing the maze
 * @visited: 2D array to track visited cells
 * @rows: number of rows in map
 * @cols: number of columns in map
 * @x: current x position
 * @y: current y position
 * @target: pointer to the target point
 * @path: pointer to the path queue
 *
 * Return: 1 if path to target is found, 0 otherwise
 */
static int backtrack(char **map, char **visited, int rows, int cols,
		     int x, int y, const point_t *target, queue_t *path)
{
	point_t *point;

	/* Check bounds */
	if (x < 0 || x >= cols || y < 0 || y >= rows)
		return (0);

	/* Check if cell is blocked or already visited */
	if (map[y][x] != '0' || visited[y][x])
		return (0);

	/* Print check */
	printf("Checking coordinates [%d, %d]\n", x, y);

	/* Mark current cell as visited */
	visited[y][x] = 1;

	/* Allocate and add point to path */
	point = malloc(sizeof(point_t));
	if (!point)
		return (0);
	point->x = x;
	point->y = y;
	queue_push_back(path, point);

	/* Check if target reached */
	if (x == target->x && y == target->y)
		return (1);

	/* Recurse in order: RIGHT, BOTTOM, LEFT, TOP */
	if (backtrack(map, visited, rows, cols, x + 1, y, target, path) ||
	    backtrack(map, visited, rows, cols, x, y + 1, target, path) ||
	    backtrack(map, visited, rows, cols, x - 1, y, target, path) ||
	    backtrack(map, visited, rows, cols, x, y - 1, target, path))
		return (1);

	/* Backtrack: remove current point from path */
	free(dequeue(path));
	return (0);
}

/**
 * backtracking_array - Finds a path from start to target using backtracking
 *
 * @map: 2D array of chars representing the maze
 * @rows: number of rows
 * @cols: number of columns
 * @start: pointer to the starting point
 * @target: pointer to the target point
 *
 * Return: queue_t containing path from start to target or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	char **visited;
	queue_t *path;
	int i;

	if (!map || !start || !target)
		return (NULL);

	/* Allocate visited matrix */
	visited = malloc(sizeof(char *) * rows);
	if (!visited)
		return (NULL);
	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(char));
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
	}

	/* Create path queue */
	path = queue_create();
	if (!path)
	{
		for (i = 0; i < rows; i++)
			free(visited[i]);
		free(visited);
		return (NULL);
	}

	/* Start recursive backtracking */
	if (!backtrack(map, visited, rows, cols, start->x, start->y, target, path))
	{
		/* No path found, cleanup */
		queue_delete(path);
		path = NULL;
	}

	/* Cleanup visited matrix */
	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	return (path);
}
