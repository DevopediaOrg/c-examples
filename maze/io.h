#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "maze.h"

// File Input
int get_num_cols(FILE *fp);
int get_num_rows(FILE *fp);
void read_maze_from_file(Maze *maze, char *filename);
void encode_maze(Maze *maze);

// Terminal Output
void print_encoded_maze(Maze *maze);
void print_maze(Maze *maze, Path *path);

#endif // IO_H