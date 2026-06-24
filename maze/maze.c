#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

#define DEBUG 0

void create_maze(Maze *maze) {
    maze->num_lines = 2 * (maze->num_rows) + 1;
    maze->line_len = 4 * (maze->num_cols) + 3; // 4 chars per cell + 1 East boundary + '\n' + '\0'
    maze->lines = calloc(maze->num_lines * maze->line_len, sizeof(char));
    maze->m = calloc(maze->num_rows * maze->num_cols, sizeof(char));
}

void free_maze(Maze *maze) {
    free(maze->lines);
    free(maze->m);
}
