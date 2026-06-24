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

// ------------------------------------------
// Lifecycle management
// ------------------------------------------
/**
 * @brief Dynamically allocates memory associated with the Maze structure.
 *
 * This function allocates 1-D array of chars for `lines` and `m`. However,
 * there's a dependency before calling this function. Maze members `num_rows`,
 * `num_cols`, `num_lines` and `line_len` have to be properly set.
 *
 * @param[in,out] maze Pointer to the Maze struct to be deallocated.
 */
void create_maze(Maze *maze);

/**
 * @brief Frees all dynamically allocated memory associated with the Maze structure.
 *
 * This function cleans up the row string buffers (`lines`) and the flattened 
 * encoded grid (`m`), resetting the maze pointer to prevent memory leaks.
 *
 * @param[in,out] maze Pointer to the Maze struct to be deallocated.
 */
void free_maze(Maze *maze);

#endif // MAZE_H