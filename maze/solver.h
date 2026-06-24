#ifndef SOLVER_H
#define SOLVER_H

#include "maze.h"

bool is_on_path(int r, int c, Path *path);
void solve_maze(Maze *maze);

#endif // SOLVER_H