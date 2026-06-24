#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

#define DEBUG 0

void create_maze(Maze *maze) {

}

void free_maze(Maze *maze) {
    int total_lines = 2 * (maze->num_rows) + 1;
    for (int i = 0; i < total_lines; i++) {
        free(maze->lines[i]);
    }
    free(maze->lines);

    free(maze->m);
}
