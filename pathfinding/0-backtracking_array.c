#include "pathfinding.h"
#include "queues.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * backtrack - Recursively explores the map to find a path to the target
 * using backtracking
 *
 * @map: 2D array representing the map
 * @visited: 2D array to keep track of visited cells
 * @rows: number of rows in the map
 * @cols: number of columns in the map
 * @x: current x coordinate
 * @y: current y coordinate
 * @target: pointer to the target point
 * @path: queue to store the path
 *
 * Return: 1 if a path is found, 0 otherwise
 */
static int backtrack(char **map, int **visited, int rows, int cols,
		     int x, int y, const point_t *target, queue_t *path)
{
	point_t *pt = NULL;

	if (x < 0 || x >= rows || y < 0 || y >= cols ||
	    map[x][y] == '1' || visited[x][y])
		return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);
	visited[x][y] = 1;

	if (x == target->x && y == target->y)
	{
		pt = malloc(sizeof(point_t));
		if (!pt)
			return (0);
		pt->x = x;
		pt->y = y;
		queue_push_front(path, pt);
		return (1);
	}

	if (backtrack(map, visited, rows, cols, x, y + 1, target, path) ||
	    backtrack(map, visited, rows, cols, x + 1, y, target, path) ||
	    backtrack(map, visited, rows, cols, x, y - 1, target, path) ||
	    backtrack(map, visited, rows, cols, x - 1, y, target, path))
	{
		pt = malloc(sizeof(point_t));
		if (!pt)
			return (0);
		pt->x = x;
		pt->y = y;
		queue_push_front(path, pt);
		return (1);
	}

	return (0);
}

/**
 * backtracking_array - Uses backtracking to find a path in a 2D map
 * from start to target
 *
 * @map: 2D array representing the map
 * @rows: number of rows
 * @cols: number of columns
 * @start: pointer to start point
 * @target: pointer to target point
 *
 * Return: a queue of point_t* forming the path, or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    const point_t *start, const point_t *target)
{
	int **visited, i;
	queue_t *path = NULL;

	if (!map || !start || !target || rows <= 0 || cols <= 0)
		return (NULL);

	visited = malloc(sizeof(int *) * rows);
	if (!visited)
		return (NULL);

	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(int));
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
	}

	path = queue_create();
	if (!path)
	{
		for (i = 0; i < rows; i++)
			free(visited[i]);
		free(visited);
		return (NULL);
	}

	if (!backtrack(map, visited, rows, cols, start->x, start->y, target, path))
	{
		queue_delete(path);
		path = NULL;
	}

	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	return (path);
}
