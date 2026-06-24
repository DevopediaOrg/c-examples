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
#include <stdbool.h>

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
int get_num_cols(FILE *fp) {
    int num_corners = 0;

    int ch; // fgetc() returns int and EOF is int
    while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
        if (ch == '+') num_corners++;
    }

    // Reset fp to start
    fseek(fp, 0, SEEK_SET);

    return num_corners - 1;
}

char (*read_maze(char *filename, int *num_rows, int *num_cols))[] {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: unable to open maze file.\n");
        return NULL;
    }

    *num_cols = get_num_cols(fp);
    *num_rows = *num_cols; // assume square maze

    // Allocate maze memory and copy first row
    char (*maze)[*num_cols] = calloc(*num_rows, sizeof(*maze));

    // Read the entire maze
    int total_lines = 2 * (*num_rows) + 1;
    int max_line_len = 4 * (*num_cols) + 3; // 4 chars per cell + 1 for boundary + '\n' + '\0'

    char **lines = malloc(total_lines * sizeof(char *));
    for (int i = 0; i < total_lines; i++) {
        lines[i] = malloc((max_line_len) * sizeof(char));
        if (fgets(lines[i], max_line_len, fp) == NULL) {
            lines[i][0] = '\0';
        }
    }
    fclose(fp);

    for (int r = 0; r < *num_rows; r++) {
        for (int c = 0; c < *num_cols; c++) {
            char cell_val = 0;

            if (lines[2 * r][4 * c + 1] == '-') {
                cell_val |= North;
            }
            if (lines[2 * r + 1][4 * c + 4] == '|') {
                cell_val |= East;
            }
            if (lines[2 * r + 2][4 * c + 1] == '-') {
                cell_val |= South;
            }
            if (lines[2 * r + 1][4 * c] == '|') {
                cell_val |= West;
            }

            maze[r][c] = cell_val;
        }
    }

    for (int i = 0; i < total_lines; i++) {
        free(lines[i]);
    }
    free(lines);

    return maze;
}

void print_encoded_maze(int num_rows, int num_cols, char (*maze)[num_cols]) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            printf("0x%02X", (unsigned char)maze[i][j]);
            if (j == num_cols-1) printf("\n");
            else printf(" ");
        }
    }
}

bool is_on_path(int r, int c, Cell *path, int num_steps) {
    if (path == NULL) return false;
    for (int i = 0; i < num_steps; i++) {
        // Assuming x is column index and y is row index (or vice versa depending on your implementation)
        // Adjust if your struct defines x as row and y as column
        if (path[i].x == r && path[i].y == c) {
            return true;
        }
    }
    return false;
}

void print_maze(char (*maze)[num_cols], Cell *path, int num_steps) {
    for (int r = 0; r < num_rows; r++) {
        
        // --- 1. Print the North Walls Row ---
        for (int c = 0; c < num_cols; c++) {
            printf("+");
            if (maze[r][c] & North) {
                printf("---");
            } else {
                printf("   ");
            }
        }
        // Caps off the right side of the North boundary row
        printf("+\n");

        // --- 2. Print the Cell Middle Row (West wall, Space/*, East wall) ---
        for (int c = 0; c < num_cols; c++) {
            // Print the West wall of the cell
            if (maze[r][c] & West) {
                printf("|");
            } else {
                printf(" ");
            }

            // Print the cell interior center (Path marker '*' or empty space)
            if (is_on_path(r, c, path, num_steps)) {
                printf(" * ");
            } else {
                printf("   ");
            }
        }
        // Caps off the very last East wall of the current row
        if (maze[r][num_cols - 1] & East) {
            printf("|\n");
        } else {
            printf(" \n");
        }
    }

    // --- 3. Print the Final South Wall Row ---
    // The bottom-most outer border needs to be closed out cleanly
    for (int c = 0; c < num_cols; c++) {
        printf("+");
        if (maze[num_rows - 1][c] & South) {
            printf("---");
        } else {
            printf("   ");
        }
    }
    printf("+\n");
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
    printf("\n\n");
    print_maze(maze, path, num_steps);
}


/*--------------------------------------
Main processing
----------------------------------------*/
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: expecting exactly 1 program argument, the maze filename to process. Quitting...\n");
        return 1;
    }

    char (*maze)[];
    
    maze = read_maze(argv[1], &num_rows, &num_cols);
    
    solve_maze(num_rows, num_cols, maze);

    return 0;
}