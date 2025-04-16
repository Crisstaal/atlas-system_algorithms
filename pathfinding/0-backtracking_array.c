#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathfinding.h"

/**
 * is_valid - Checks if a cell is within bounds and walkable
 * @map: 2D map array
 * @visited: 2D visited array
 * @x: x-coordinate
 * @y: y-coordinate
 * @rows: number of rows
 * @cols: number of columns
 * Return: 1 if valid, 0 otherwise
 */
static int is_valid(char **map, int **visited, int x, int y, int rows, int cols)
{
	if (x < 0 || x >= cols || y < 0 || y >= rows)
		return (0);
	if (map[y][x] == '1' || visited[y][x])
		return (0);
	return (1);
}

/**
 * backtrack - Recursive backtracking function
 * @map: 2D map array
 * @visited: 2D visited array
 * @path: Queue to store the path
 * @current: Current point
 * @target: Target point
 * @rows: number of rows
 * @cols: number of columns
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack(char **map, int **visited, queue_t *path,
		     point_t *current, point_t const *target,
		     int rows, int cols)
{
	point_t *pt;

	printf("Checking coordinates [%d, %d]\n", current->x, current->y);

	if (!is_valid(map, visited, current->x, current->y, rows, cols))
		return (0);

	visited[current->y][current->x] = 1;

	if (current->x == target->x && current->y == target->y)
	{
		pt = malloc(sizeof(*pt));
		if (!pt)
			return (0);
		pt->x = current->x;
		pt->y = current->y;
		enqueue(path, pt);
		return (1);
	}

	point_t dirs[] = {
		{current->x + 1, current->y}, /* Right */
		{current->x, current->y + 1}, /* Down */
		{current->x - 1, current->y}, /* Left */
		{current->x, current->y - 1}  /* Up */
	};
	int i;

	for (i = 0; i < 4; i++)
	{
		if (backtrack(map, visited, path, &dirs[i], target, rows, cols))
		{
			pt = malloc(sizeof(*pt));
			if (!pt)
				return (0);
			pt->x = current->x;
			pt->y = current->y;
			enqueue(path, pt);
			return (1);
		}
	}

	return (0);
}

/**
 * backtracking_array - Finds a path in a 2D array using backtracking
 * @map: 2D map array
 * @rows: Number of rows
 * @cols: Number of columns
 * @start: Starting point
 * @target: Target point
 * Return: Queue containing the path or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	int **visited, i;
	queue_t *path;
	point_t cur;

	visited = malloc(sizeof(*visited) * rows);
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

	cur.x = start->x;
	cur.y = start->y;

	if (!backtrack(map, visited, path, &cur, target, rows, cols))
	{
		queue_delete(path);
		path = NULL;
	}

	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	return (path);
}
