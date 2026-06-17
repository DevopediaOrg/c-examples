/*
This program is a maze solver. It reads a square maze
from an input text file. It figures out the maze size
from the input.

If maze is N x N, each cell is represented by a char.
The four LSB of this char indicate the North (bit 0),
East (bit 1), South (bit 2) and West (bit 3)
boundaries. Bit value 1 implies a wall. Bit 0 implies
an open path. For example, 0x0A (1010) implies walls
on the West and East boundaries of the cell. We give
five examples below:
+---+     +---+     +   +     +   +     +---+
          |         |   |         |     |   
+---+     +---+     +   +     +---+     +   +
0x05      0x0D      0x0A      0x06      0x09

The algorithm is a depth-first search. Maze is
entered at the top-left corner from the West. Maze
exit at the bottom-right corner to the East. If
there are multiple solution paths, only one is found
and not necessarily the shortest one.

The following are the objectives:
- Print the full found path
- Print the number steps in the found path
- Print the total number of steps taken TODO
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0


/*--------------------------------------
Type definitions
----------------------------------------*/
typedef enum {
    North = 1,
    East = 2,
    South = 4,
    West = 8
} Direction;

typedef struct {
    int x;
    int y;
} Cell;


/*--------------------------------------
Globals
----------------------------------------*/
int num_rows, num_cols;
int found_path = 0;
int num_steps; // indexes into path[]
Cell path[100] = {};


/*--------------------------------------
Functions
----------------------------------------*/
int read_row(FILE *fp, char *row, int num_cols) {
    int actual_num_cols = 0;
    for (int i = 0; i < num_cols; i++) {
        int cell;
        if (fscanf(fp, "0x%02x", &cell) == 1) {
            row[i] = (char)cell;
            int separator = fgetc(fp);
            if (separator == '\n') {
                // Last cell of each row is followed by \n and not space
                actual_num_cols = i + 1; // assume square maze
                break;
            }
            else if (separator != ' ') {
                printf("Warning: separator is not a space as expected.\n");
            }
        }
        else {
            printf("Warning: unable to read cell in expected fscanf format.\n");
        }
    }
    return actual_num_cols;
}

char (*read_maze(int *num_rows, int *num_cols))[] {
    FILE *fp = fopen("m1.txt", "r");
    if (fp == NULL) {
        printf("Error: unable to open maze file.\n");
        return NULL;
    }

    char row[100]; // assume a temporary limit on maze size
    *num_cols = read_row(fp, row, sizeof(row)/sizeof(char));
    *num_rows = *num_cols; // assume square maze

    // Allocate maze memory and copy first row
    char (*maze)[*num_cols] = calloc(*num_rows, sizeof(*maze));
    memcpy(maze, row, sizeof(*maze));

    // Read the remaining rows
    for (int i = 1; i < *num_rows; i++) {
        read_row(fp, maze[i], *num_cols);
    }

    return maze;
}

void print_maze(int num_rows, int num_cols, char (*maze)[num_cols]) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            printf("0x%02x", (unsigned char)maze[i][j]);
            if (j == num_cols-1) printf("\n");
            else printf(" ");
        }
    }
}

Cell* explore(int x, int y, Direction in, char (*maze)[num_cols], int path_idx) {
    Direction dirs[] = {North, East, South, West};
    int num_dirs = sizeof(dirs) / sizeof(dirs[0]);

    #if DEBUG
    printf("explore(%d, %d, %d, %d)\n", x, y, in, path_idx);
    #endif

    // Skip if indices are out of bounds
    if (x < 0 || x >= num_rows || y < 0 || y >= num_cols) return NULL;

    if (x == num_rows-1 && y == num_cols-1) {
        // We have reached the bottom-right cell: Success!
        found_path = 1;
        num_steps = path_idx + 1;
        path[path_idx].x = x;
        path[path_idx].y = y;
        return path + path_idx;
    }

    Cell *next = NULL;
    for (int i = 0; i < num_dirs; i++) {
        // Don't explore the way we came in
        if (dirs[i] == in) continue;

        // Bit-wise operation non-zero implies a wall
        if ((maze[x][y] & dirs[i])) continue;

        switch (dirs[i]) {
            case North:
                next = explore(x-1, y, South, maze, path_idx+1);
                break;
            case East:
                next = explore(x, y+1, West, maze, path_idx+1);
                break;
            case South:
                next = explore(x+1, y, North, maze, path_idx+1);
                break;
            case West:
                next = explore(x, y-1, East, maze, path_idx+1);
                break;
        }

        // If found a path, don't search in other directions
        if (found_path) break;
    }

    if (next) {
        // Found a path
        path[path_idx].x = x;
        path[path_idx].y = y;
        return path + path_idx;
    }

    return NULL;
}

void solve_maze(int num_rows, int num_cols, char (*maze)[num_cols]) {
    explore(0, 0, West, maze, 0);
    printf("Found maze path of %d steps: ", num_steps);
    for (int i = 0; i < num_steps; i++) {
        printf("(%d, %d) ", path[i].x, path[i].y);
    }
}


/*--------------------------------------
Main processing
----------------------------------------*/
int main() {
    char (*maze)[];

    maze = read_maze(&num_rows, &num_cols);
    
    solve_maze(num_rows, num_cols, maze);

    return 0;
}