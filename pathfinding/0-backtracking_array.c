#include <stdio.h>
#include <stdlib.h>
#include "pathfinding.h"
#include "queues.h"

/**
 * backtrack - Recursive helper function to explore the map using backtracking
 *             to find the path from start to target.
 *
 * @map: Pointer to the 2D array representing the map.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @x: The current row coordinate.
 * @y: The current column coordinate.
 * @target: Coordinates of the target point.
 * @visited: The 2D array to track visited points.
 * @path: The queue to store the path.
 *
 * Return: 1 if the path is found, 0 if not.
 */
int backtrack(char **map, int rows, int cols, int x, int y, point_t const *target, int **visited, queue_t *path);

/**
 * backtracking_array - Searches for the first path from start to target
 *                      using recursive backtracking in a 2D map.
 *
 * @map: Pointer to the 2D array representing the map.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @start: Coordinates of the starting point.
 * @target: Coordinates of the target point.
 *
 * Return: A queue representing the path from start to target, or NULL if no
 *         path is found.
 */
queue_t *backtracking_array(char **map, int rows, int cols, point_t const *start, point_t const *target)
{
	queue_t *path = queue_create();		      /** Create a new queue to store the path */
	int **visited = malloc(sizeof(int *) * rows); /** Allocate memory for the visited array */
	int i, j;

	/** Initialize the visited array */
	for (i = 0; i < rows; i++)
	{
		visited[i] = malloc(sizeof(int) * cols); /** Allocate memory for each row */
		for (j = 0; j < cols; j++)
			visited[i][j] = 0; /** Mark all cells as unvisited */
	}

	/** Recursive function to perform the backtracking */
	if (backtrack(map, rows, cols, start->x, start->y, target, visited, path))
	{
		for (i = 0; i < rows; i++)
			free(visited[i]); /** Free each row of the visited array */
		free(visited);		  /** Free the visited array */
		return path;		  /** Return the found path */
	}

	/** If no path is found, free the visited array and return NULL */
	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);
	queue_delete(path); /** Deallocate the path queue */
	return NULL;	    /** Return NULL to indicate failure */
}

/**
 * backtrack - Recursive helper function to explore the map using backtracking
 *             to find the path from start to target.
 *
 * @map: Pointer to the 2D array representing the map.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @x: The current row coordinate.
 * @y: The current column coordinate.
 * @target: Coordinates of the target point.
 * @visited: The 2D array to track visited points.
 * @path: The queue to store the path.
 *
 * Return: 1 if the path is found, 0 if not.
 */
int backtrack(char **map, int rows, int cols, int x, int y, point_t const *target, int **visited, queue_t *path)
{
	/** Base case: If out of bounds or blocked or already visited */
	if (x < 0 || y < 0 || x >= rows || y >= cols || map[x][y] == '1' || visited[x][y])
		return 0;

	/** Mark the current cell as visited */
	visited[x][y] = 1;

	/** Print the current coordinates for debugging */
	printf("Checking coordinates [%d, %d]\n", x, y);

	/** If the target is reached, add the point to the path and return true */
	if (x == target->x && y == target->y)
	{
		point_t *point = malloc(sizeof(point_t)); /** Allocate memory for the point */
		point->x = x;
		point->y = y;
		queue_push_back(path, point); /** Push the point to the back of the queue */
		return 1;
	}

	/** Explore neighbors in the order: right, down, left, up */
	if (backtrack(map, rows, cols, x + 1, y, target, visited, path) || /** Right */
	    backtrack(map, rows, cols, x, y + 1, target, visited, path) || /** Down */
	    backtrack(map, rows, cols, x - 1, y, target, visited, path) || /** Left */
	    backtrack(map, rows, cols, x, y - 1, target, visited, path))   /** Up */
	{
		point_t *point = malloc(sizeof(point_t)); /** Allocate memory for the point */
		point->x = x;
		point->y = y;
		queue_push_back(path, point); /** Push the point to the back of the queue */
		return 1;
	}

	/** If no valid move is found, unmark the current cell and return false */
	visited[x][y] = 0;
	return 0;
}
