#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

typedef enum direction {
    North = 1,
    East = 2,
    South = 4,
    West = 8
} Direction;

typedef struct cell {
    int x;
    int y;
} Cell;

typedef struct maze {
    int num_rows;
    int num_cols;
    int num_lines;
    int line_len;
    char *lines; // as stored in file
    char *m; // as encoded in memory
} Maze;

typedef struct path {
    bool found_path;
    int num_steps; // indexes into cells
    Cell *cells;
} Path;

// Lifecycle management
void create_maze(Maze *maze);
void free_maze(Maze *maze);

#endif // MAZE_H