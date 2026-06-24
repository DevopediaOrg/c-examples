#ifndef SOLVER_H
#define SOLVER_H

#include "maze.h"

/**
 * @brief Checks if a specific cell coordinate is currently part of the solved path.
 *
 * Iterates through the cells of `path` to see if the given row and column 
 * is on the path.
 *
 * @param[in] r    The row index of the cell.
 * @param[in] c    The column index of the cell.
 * @param[in] path Pointer to the Path tracker.
 * @return true if the cell is on the path, false otherwise.
 */
bool is_on_path(int r, int c, Path *path);

/**
 * @brief Initializes and runs the pathfinding algorithm on the given maze.
 *
 * Sets up the entry points and structures required by `explore`, initiates the search, 
 * and coordinates saving or displaying the result. Prints the maze and found path
 * within it.
 *
 * @param[in,out] maze Pointer to the Maze struct to solve.
 */
void solve_maze(Maze *maze);

#endif // SOLVER_H