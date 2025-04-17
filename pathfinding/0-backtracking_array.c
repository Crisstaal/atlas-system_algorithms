#include <stdlib.h>
#include <stdio.h>

#include "pathfinding.h"
#include "queues.h"

/**
 * backtrack - Recursive backtracking function to find the path
 *
 * @map: The grid map
 * @rows: Number of rows
 * @cols: Number of columns
 * @x: Current x-coordinate
 * @y: Current y-coordinate
 * @target: The target point
 * @visited: 2D array to mark visited cells
 * @path: Queue to store the path
 *
 * Return: 1 if the target is found, 0 otherwise
 */
static int backtrack(char **map, int rows, int cols, int x, int y,
                     point_t *target, int **visited, queue_t *path)
{
    /** Check for out-of-bound or blocked cells */
    if (x < 0 || x >= rows || y < 0 || y >= cols || map[x][y] == '1' || visited[x][y])
        return 0;

    /** Mark the current cell as visited */
    visited[x][y] = 1;

    /** Print the current coordinates */
    printf("Checking coordinates [%d, %d]\n", x, y);

    /** If target is found, add the point to the queue and return success */
    if (x == target->x && y == target->y)
    {
        point_t *point = malloc(sizeof(point_t));
        if (!point)
            return 0;
        point->x = x;
        point->y = y;
        queue_push_back(path, point);
        return 1;
    }

    /** Try moving in the specified order: right, down, left, up */
    if (backtrack(map, rows, cols, y + 1, x, target, visited, path) ||   // Right
        backtrack(map, rows, cols, y, x + 1, target, visited, path) ||   // Bottom
        backtrack(map, rows, cols, y - 1, x, target, visited, path) ||   // Left
        backtrack(map, rows, cols, y, x - 1, target, visited, path))     // Top
    {
        point_t *point = malloc(sizeof(point_t));
        if (!point)
            return 0;
        point->x = x;
        point->y = y;
        queue_push_back(path, point);
        return 1;
    }

    return 0;
}

/**
 * backtracking_array - Finds the first path from start to target using backtracking
 *
 * @map: The grid map
 * @rows: Number of rows in the grid
 * @cols: Number of columns in the grid
 * @start: Starting point
 * @target: Target point
 *
 * Return: A queue containing the path from start to target, or NULL if no path
 */
queue_t *reverse_queue(queue_t *queue)
{
    queue_t *reversed = queue_create();
    if (!reversed)
        return NULL;

    // Pop elements from the original queue and push them to the reversed queue
    while (!queue_is_empty(queue))
    {
        point_t *point = queue_pop_front(queue);
        queue_push_back(reversed, point);
    }

    return reversed;
}
queue_t *backtracking_array(char **map, int rows, int cols,
                            point_t const *start, point_t const *target)
{
    queue_t *path = queue_create();
    if (!path)
        return NULL;

    int **visited = malloc(rows * sizeof(int *));
    if (!visited)
    {
        queue_delete(path);
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
            queue_delete(path);
            return NULL;
        }
    }

    if (backtrack(map, rows, cols, start->x, start->y, (point_t *)target, visited, path))
    {
        for (int i = 0; i < rows; i++)
            free(visited[i]);
        free(visited);
        return path;
    }

    for (int i = 0; i < rows; i++)
        free(visited[i]);
    free(visited);
    queue_delete(path);
    return NULL;
}
