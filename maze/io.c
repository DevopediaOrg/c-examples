#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "io.h"
#include "solver.h"

/**
 * @brief Calculates the number of columns in the maze from the input file.
 *
 * Scans the first line of the file to determine the width of the maze 
 * based on the character pattern.
 *
 * @param[in] fp Pointer to the opened file stream.
 * @return The total number of columns found.
 */
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

/**
 * @brief Calculates the number of rows in the maze from the input file.
 *
 * Counts the total lines in the file to determine the grid height.
 *
 * @param[in] fp Pointer to the opened file stream.
 * @return The total number of rows found.
 */
int get_num_rows(FILE *fp) {
    int num_lines = 0;

    char line[200]; // an arbitrary limit
    while (fgets(line, 200, fp) != NULL) {
        num_lines++;
    }

    // Reset fp to start
    fseek(fp, 0, SEEK_SET);

    return (num_lines - 1) / 2;
}

/* Implementation as declared in io.h */
void read_maze_from_file(Maze *maze, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: unable to open maze file %s. Quitting...\n", filename);
        exit(1);
    }

    maze->num_cols = get_num_cols(fp);
    maze->num_rows = get_num_rows(fp);

    create_maze(maze);

    char (*lines)[maze->line_len] = (char (*)[maze->line_len])maze->lines;
    for (int i = 0; i < maze->num_lines; i++) {
        if (fgets(lines[i], maze->line_len, fp) == NULL) {
            lines[i][0] = '\0';
        }
    }

    fclose(fp);
}

/* Implementation as declared in io.h */
void encode_maze(Maze *maze) {
    char (*lines)[maze->line_len] = (char (*)[maze->line_len])maze->lines;
    char (*m)[maze->num_cols] = (char (*)[maze->num_cols])maze->m;

    for (int r = 0; r < maze->num_rows; r++) {
        for (int c = 0; c < maze->num_cols; c++) {
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

            m[r][c] = cell_val;
        }
    }
}

/* Implementation as declared in io.h */
void print_encoded_maze(Maze *maze) {
    for (int i = 0; i < maze->num_rows; i++) {
        for (int j = 0; j < maze->num_cols; j++) {
            printf("0x%02X", (unsigned char)maze->m[i*maze->num_cols + j]);
            if (j == maze->num_cols-1) printf("\n");
            else printf(" ");
        }
    }
}

/* Implementation as declared in io.h */
void print_maze(Maze *maze, Path *path) {
    char (*m)[maze->num_cols] = (char (*)[maze->num_cols])maze->m;

    for (int r = 0; r < maze->num_rows; r++) {
        
        // --- 1. Print the North Walls Row ---
        for (int c = 0; c < maze->num_cols; c++) {
            printf("+");
            if (m[r][c] & North) {
                printf("---");
            } else {
                printf("   ");
            }
        }
        // Caps off the right side of the North boundary row
        printf("+\n");

        // --- 2. Print the Cell Middle Row (West wall, Space/*, East wall) ---
        for (int c = 0; c < maze->num_cols; c++) {
            // Print the West wall of the cell
            if (m[r][c] & West) {
                printf("|");
            } else {
                printf(" ");
            }

            // Print the cell interior center (Path marker '*' or empty space)
            if (is_on_path(r, c, path)) {
                printf(" * ");
            } else {
                printf("   ");
            }
        }
        // Caps off the very last East wall of the current row
        if (m[r][maze->num_cols - 1] & East) {
            printf("|\n");
        } else {
            printf(" \n");
        }
    }

    // --- 3. Print the Final South Wall Row ---
    // The bottom-most outer border needs to be closed out cleanly
    for (int c = 0; c < maze->num_cols; c++) {
        printf("+");
        if (m[maze->num_rows - 1][c] & South) {
            printf("---");
        } else {
            printf("   ");
        }
    }
    printf("+\n");
}
