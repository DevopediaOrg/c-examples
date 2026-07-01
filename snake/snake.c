/*
This implements the snake game where the snake grows each
time it eats a fruit. The game ends if the snake crashes
into a wall or its own body.

Instead of using ASCII characters, we use emojis to make
this game more colorful. When stored in memory, they will
be in UTF-8 encoding. To understand emojis,
see https://unicode.org/emoji/charts/full-emoji-list.html
To understand UTF-8,
see https://datatracker.ietf.org/doc/html/rfc3629 (sec. 3)

Here's an example of UTF-8 encoding of "brick" emoji:
- Unicode U+1F9F1
- UTF-8 encoding range:
     0001 0000-0010 FFFF >> 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  => 0001 F9F1
  =  0001 1111 1001 1111 0001 >> 11110000 10011111 10100111 10110001
  =  F0 9F A7 B1

This code works on a Windows terminal but won't work on
a Linux terminal.

Note: It's common in gaming apps to view columns along x-axis
and rows along y-axis. In this implementation, we take the
approach of rows along x-axis and columns along y-axis. Hence,
we access the game board as grid[x][y] rather than grid[y][x].

TODO (some improvements to consider)
- Make the game faster when snake exceeds some length
- Make the game faster if game is being played for too long
- Give different scores for different fruits but more valuable
  fruits must be rarer
- Fruit disappears if not consumed within a fixed time
- Award bonus points if fruit is consumed quickly
- Allow 1-3 fruits on the board at the same time
- Extend the code to run on POSIX/Linux terminals as well
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// Excludes the walls
#define WIDTH 30
#define HEIGHT 20

typedef struct snake {
    int x[WIDTH * HEIGHT]; // rows
    int y[WIDTH * HEIGHT]; // cols
    int len; // including the head at (x[0], y[0])
} Snake;
Snake snake;

typedef enum dir {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
} Direction;
Direction dir;

char *fruits[] = {"🍎", "🍌", "🍇", "🍉", "🥝", "🍍", "🍐", "🍊"};
int num_fruits = sizeof(fruits)/sizeof(char*);
typedef struct fruit {
    int x, y; // only one fruit at a time
    int which;
} Fruit;
Fruit fruit;

bool gameOver;
int score;
int tick_ms = 100;


void create_fruit() {
    bool overlaps = true;
    while (overlaps) {
        overlaps = false;
        fruit.x = rand() % HEIGHT;
        fruit.y = rand() % WIDTH;
        for (int i = 0; i < snake.len; i++) {
            if (fruit.x == snake.x[i] && fruit.y == snake.y[i]) {
                overlaps = true;
                break;
            }
        }
    }
    fruit.which = rand() % num_fruits;
}

void init_game() {
    gameOver = false;

    srand(time(NULL));
    
    dir = STOP; // game begins only when a key is pressed
    
    snake.x[0] = HEIGHT / 2;
    snake.y[0] = WIDTH / 2;
    snake.len = 1;

    create_fruit();
    
    score = 0;
}

void draw_board() {
    // Reset cursor to top-left to reduce flicker
    // TODO Improve this code to completely eliminate flicker
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    char brick[] = "🧱";

    // Top wall
    for (int i = 0; i < WIDTH + 2; i++) printf(brick);
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) { // within the walls
        printf(brick); // left wall
        for (int j = 0; j < WIDTH; j++) { // within the walls
            if (i == snake.x[0] && j == snake.y[0]) {
                printf("🐸"); // actually a frog head!
            } else if (i == fruit.x && j == fruit.y) {
                printf(fruits[fruit.which]);
            } else {
                bool is_tail = false;
                for (int k = 1; k < snake.len; k++) {
                    if (i == snake.x[k] && j == snake.y[k]) {
                        printf("🟢"); // snake body
                        is_tail = true;
                    }
                }
                if (!is_tail) printf("⬜");
            }
        }
        printf(brick); // right wall
        printf("\n");
    }

    // Bottom wall
    for (int i = 0; i < WIDTH + 2; i++) printf(brick);
    printf("\n");

    // Print score
    printf("\nScore: %d; Snake length: %d\n", score, snake.len);
    printf("Use WASD keys to move. Press Q to quit.\n");
}

void process_user_input() {
    if (_kbhit()) {
        switch (tolower(_getch())) {
            // if statements below => we can't reverse from current dir
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'q':
                gameOver = 1;
                break;
        }
    }
}

void update_board() {
    // Return if there's nothing to update
    if (gameOver || dir == STOP) return;

    // Fruit consumption
    if (snake.x[0] == fruit.x && snake.y[0] == fruit.y) {
        score += 10;

        snake.x[snake.len] = snake.x[snake.len-1];
        snake.y[snake.len] = snake.y[snake.len-1];
        snake.len++;
        
        create_fruit();    
    }

    // Move the body
    for (int i = snake.len; i > 1; i--) {
        snake.x[i-1] = snake.x[i-2];
        snake.y[i-1] = snake.y[i-2];
    }

    // Move the head
    switch (dir) {
        case LEFT:  snake.y[0]--; break;
        case RIGHT: snake.y[0]++; break;
        case UP:    snake.x[0]--; break;
        case DOWN:  snake.x[0]++; break;
        default: break;
    }

    // Wall collision
    if (snake.x[0] >= HEIGHT || snake.x[0] < 0 || snake.y[0] >= WIDTH || snake.y[0] < 0)
        gameOver = true;

    // Self-collision
    for (int i = 1; !gameOver && i < snake.len; i++) {
        if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0]) {
            gameOver = true;
            break;
        }
    }
}

int main() {
    init_game();
    while (!gameOver) {
        draw_board();
        process_user_input();
        update_board();
        Sleep(tick_ms);
    }
    printf("\nGame Over! Final Score: %d\n", score);
    return 0;
}