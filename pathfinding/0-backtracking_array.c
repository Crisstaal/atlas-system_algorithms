#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"
#include "queue.h"

/**
 * is_valid_move - Check if the current position is valid to move
 *
 * @map: Pointer to the 2D map
 * @rows: Number of rows in the map
 * @cols: Number of columns in the map
 * @x: Current x coordinate
 * @y: Current y coordinate
 *
 * Return: 1 if valid, 0 if not valid
 */
int is_valid_move(char **map, int rows, int cols, int x, int y)
{
	return (x >= 0 && x < rows && y >= 0 && y < cols && map[x][y] == '0');
}

/**
 * backtracking - Recursively find a path from start to target
 *
 * @map: Pointer to the 2D map
 * @rows: Number of rows in the map
 * @cols: Number of columns in the map
 * @start: Starting point
 * @target: Target point
 * @path: Queue to store the path
 * @visited: 2D array to keep track of visited positions
 *
 * Return: 1 if the path is found, 0 otherwise
 */
int backtracking(char **map, int rows, int cols, point_t const *start,
		 point_t const *target, queue_t *path, int **visited)
{
	int x = start->x;
	int y = start->y;

	/** Print current coordinates */
	printf("Checking coordinates [%d, %d]\n", x, y);

	/** Check if we've reached the target */
	if (x == target->x && y == target->y)
	{
		point_t *point = malloc(sizeof(point_t));
		if (!point)
			return 0;
		point->x = x;
		point->y = y;
		enqueue(path, point);
		return 1;
	}

	/** If the current position is not valid or already visited */
	if (!is_valid_move(map, rows, cols, x, y) || visited[x][y])
		return 0;

	/** Mark as visited */
	visited[x][y] = 1;

	/** Explore right, bottom, left, top */
	if (backtracking(map, rows, cols, &(point_t){x, y + 1}, target, path, visited) ||
	    backtracking(map, rows, cols, &(point_t){x + 1, y}, target, path, visited) ||
	    backtracking(map, rows, cols, &(point_t){x, y - 1}, target, path, visited) ||
	    backtracking(map, rows, cols, &(point_t){x - 1, y}, target, path, visited))
	{
		point_t *point = malloc(sizeof(point_t));
		if (!point)
			return 0;
		point->x = x;
		point->y = y;
		enqueue(path, point);
		return 1;
	}

	/** Backtrack if no path found */
	return 0;
}

/**
 * backtracking_array - Find the first path from start to target using backtracking
 *
 * @map: Pointer to the 2D map
 * @rows: Number of rows in the map
 * @cols: Number of columns in the map
 * @start: Starting point
 * @target: Target point
 *
 * Return: Queue containing the path, or NULL if no path is found
 */
queue_t *backtracking_array(char **map, int rows, int cols, point_t const *start, point_t const *target)
{
	queue_t *path = create_queue();
	if (!path)
		return NULL;

	/** Allocate memory for visited array */
	int **visited = malloc(rows * sizeof(int *));
	if (!visited)
	{
		free(path);
		return NULL;
	}

	for (int i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(int));
		if (!visited[i])
		{
			for (int j = 0; j < i; j++)
				free(visited[j]);
			free(visited);
			free(path);
			return NULL;
		}
	}

	/** Start backtracking from the start point */
	if (!backtracking(map, rows, cols, start, target, path, visited))
	{
		free(visited);
		free(path);
		return NULL;
	}

	/** Clean up visited array */
	for (int i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	return path;
}
