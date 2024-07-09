#ifndef HEADER_H
#define HEADER_H

#include <SDL/SDL.h>

#define SCREEN_WIDTH 1700
#define SCREEN_HEIGHT 800
#define SCREEN_BPP 32

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define BOARD_SIZE BOARD_WIDTH * BOARD_HEIGHT
#define EMPTY_CELL 0
#define PLAYER_X 1
#define PLAYER_O 2
#define PLAYER_TURN 0
#define PLAYER_X_TURN 1
#define PLAYER_O_TURN 2

#define CELL_WIDTH 566
#define CELL_HEIGHT 300

#define NO_WINNER 0




void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

// Function to initialize SDL and create the game window
int init(SDL_Surface** screen);

// Function to load images and create game surfaces
int load_files(SDL_Surface** x_img, SDL_Surface** o_img, SDL_Surface** bg_img);

// Function to handle game events
int handle_events(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img, int* board, int* turn);

// Function to draw the Tic Tac Toe board and pieces
void draw_board(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img, int* board);

// Function to check if there is a winner or a tie
int check_win(int* board);

// Function to free game surfaces and quit SDL
void clean_up(SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img);

#endif

