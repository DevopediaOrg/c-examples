#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "io.h"
#include "solver.h"

#define DEBUG_SOLVER 0

/* Implementation as declared in solver.h */
bool is_on_path(int r, int c, Path *path) {
    if (path == NULL) return false;
    for (int i = 0; i < path->num_steps; i++) {
        if (path->cells[i].x == r && path->cells[i].y == c) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Core recursive function that explores the maze layout using Depth-First Search (DFS).
 *
 * Navigates from cell to cell by assessing valid moves (openings with no walls) while
 * updating the active path array and tracking the incoming entry direction to prevent backtracking.
 *
 * @param[in]     x        The current cell row coordinate.
 * @param[in]     y        The current cell column coordinate.
 * @param[in]     in       The direction from which the algorithm entered the current cell.
 * @param[in]     maze     Pointer to the encoded maze structure.
 * @param[in,out] path     Pointer to the active path tracking struct.
 * @param[in]     path_idx The current depth/step index within the execution path.
 * @return A pointer to the final Cell array containing the path sequence, or NULL if blocked.
 */
Cell* explore(int x, int y, Direction in, Maze *maze, Path *path, int path_idx) {
    Direction dirs[] = {North, East, South, West};
    int num_dirs = sizeof(dirs) / sizeof(dirs[0]);

    #if DEBUG_SOLVER
    printf("explore(%d, %d, %d, %d)\n", x, y, in, path_idx);
    #endif

    // Skip if indices are out of bounds
    if (x < 0 || x >= maze->num_rows || y < 0 || y >= maze->num_cols) return NULL;

    if (x == maze->num_rows-1 && y == maze->num_cols-1) {
        // We have reached the bottom-right cell: Success!
        path->found_path = 1;
        path->num_steps = path_idx + 1;
        path->cells[path_idx].x = x;
        path->cells[path_idx].y = y;
        return path->cells + path_idx;
    }

    Cell *next = NULL;
    for (int i = 0; i < num_dirs; i++) {
        // Don't explore the way we came in
        if (dirs[i] == in) continue;

        // Bit-wise operation non-zero implies a wall
        if ((maze->m[x*maze->num_cols + y] & dirs[i])) continue;

        switch (dirs[i]) {
            case North:
                next = explore(x-1, y, South, maze, path, path_idx+1);
                break;
            case East:
                next = explore(x, y+1, West, maze, path, path_idx+1);
                break;
            case South:
                next = explore(x+1, y, North, maze, path, path_idx+1);
                break;
            case West:
                next = explore(x, y-1, East, maze, path, path_idx+1);
                break;
        }

        // If found a path, don't search in other directions
        if (path->found_path) break;
    }

    if (next) {
        // Found a path
        path->cells[path_idx].x = x;
        path->cells[path_idx].y = y;
        return path->cells + path_idx;
    }

    return NULL;
}

/* Implementation as declared in solver.h */
void solve_maze(Maze *maze) {
    Path path;
    path.found_path = false;
    path.cells = malloc(maze->num_rows * maze->num_cols * sizeof(Cell));

    explore(0, 0, West, maze, &path, 0);
    printf("Found maze path of %d steps: ", path.num_steps);
    for (int i = 0; i < path.num_steps; i++) {
        printf("(%d, %d) ", path.cells[i].x, path.cells[i].y);
    }
    printf("\n\n");
    print_maze(maze, &path);

    free(path.cells);
}
