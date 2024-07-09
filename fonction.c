#include "header.h"
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include<SDL/SDL_keysym.h>
#include<string.h>
#include <stdbool.h>



void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, destination, &offset);
}







int init(SDL_Surface** screen) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Set up the game window
    *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (*screen == NULL) {
        fprintf(stderr, "Error creating game window: %s\n", SDL_GetError());
        return 1;
    }

    // Set the game window caption
    SDL_WM_SetCaption("Tic Tac Toe", NULL);

    return 0;
}


int load_files(SDL_Surface** x_img, SDL_Surface** o_img, SDL_Surface** bg_img) {
    // Load X image
    *x_img = IMG_Load("x&.png");
    if (*x_img == NULL) {
        fprintf(stderr, "Error loading X image: %s\n", SDL_GetError());
        return 1;
    }

    // Load O image
    *o_img = IMG_Load("o.bmp");
    if (*o_img == NULL) {
        fprintf(stderr, "Error loading O image: %s\n", SDL_GetError());
        return 1;
    }

    // Load background image
    *bg_img = IMG_Load("imageedit_1_6931259329.jpg");
    if (*bg_img == NULL) {
        fprintf(stderr, "Error loading background image: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}


int handle_events(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img, int* board, int* turn) {
    int quit = 0;
    SDL_Event event;
    int mouse_x = 0, mouse_y = 0;
    int play_x = -1, play_y = -1;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                mouse_x = event.button.x;
                mouse_y = event.button.y;

                // Check which cell was clicked
		play_x = (mouse_x ) / CELL_WIDTH;
		play_y = (mouse_y) / CELL_HEIGHT;


            }
        }

        // Player's turn
        if (*turn == PLAYER_X_TURN && play_x >= 0 && play_y >= 0 && board[play_x + play_y * BOARD_WIDTH] == EMPTY_CELL) {
            board[play_x + play_y * BOARD_WIDTH] = PLAYER_X;
            *turn = PLAYER_O_TURN;
            play_x = -1;
            play_y = -1;
        }
        // Computer's turn
        else if (*turn == PLAYER_O_TURN) {
            // Randomly select an empty cell
            int empty_count = 0;
            for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
                if (board[i] == EMPTY_CELL) {
                    empty_count++;
                }
            }
            if (empty_count == 0) {
                // Board is full, game over
                quit = 1;
            } else {
                int random_index = rand() % empty_count;
                int index = 0;
                for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
                    if (board[i] == EMPTY_CELL) {
                        if (index == random_index) {
                            board[i] = PLAYER_O;
                            *turn = PLAYER_X_TURN;
                            break;
                        }
                        index++;
                    }
                }
            }
        }

        // Draw the board
        draw_board(screen, x_img, o_img, bg_img, board);
        
        // Check for win
        int winner = check_win(board);
        if (winner != EMPTY_CELL) {
            quit = 1;
            if (winner == PLAYER_X) {
                printf("Player X wins!\n");
            } else if (winner == PLAYER_O) {
                printf("Player O wins!\n");
            } else {
                printf("It's a draw!\n");
            }
        }

        SDL_UpdateRect(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_Delay(10);
    }

    return 0;
}





void draw_board(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img, int* board) {
    // Draw the background image
    apply_surface(0, 0, bg_img, screen, NULL);

    // Draw the X and O pieces
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            int cell = board[row * 3 + col];
            if (cell == 1) {
                apply_surface(col * (SCREEN_WIDTH / 3)+250, row * (SCREEN_HEIGHT / 3)+80, x_img, screen, NULL);
            } else if (cell == 2) {
                apply_surface(col * (SCREEN_WIDTH / 3)+250, row * (SCREEN_HEIGHT / 3)+80, o_img, screen, NULL);
            }
        }
    }

    // Draw the grid lines
    
}


int check_win(int* board) {
    // Check rows
    for (int row = 0; row < 3; row++) {
        if (board[row * 3] != 0 && board[row * 3] == board[row * 3 + 1] && board[row * 3] == board[row * 3 + 2]) {
            return board[row * 3];
        }
    }

    // Check columns
    for (int col = 0; col < 3; col++) {
        if (board[col] != 0 && board[col] == board[col + 3] && board[col] == board[col + 6]) {
            return board[col];
        }
    }

    // Check diagonals
    if (board[0] != 0 && board[0] == board[4] && board[0] == board[8]) {
        return board[0];
    }
    if (board[2] != 0 && board[2] == board[4] && board[2] == board[6]) {
        return board[2];
    }

    // Check for tie game
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            return 0;
        }
    }
    return -1;
}



void clean_up(SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img) {
    // Free the X image
    if (x_img != NULL) {
        SDL_FreeSurface(x_img);
        x_img = NULL;
    }

    // Free the O image
    if (o_img != NULL) {
        SDL_FreeSurface(o_img);
        o_img = NULL;
    }

    // Free the background image
    if (bg_img != NULL) {
        SDL_FreeSurface(bg_img);
        bg_img = NULL;
    }

    // Quit SDL
    SDL_Quit();
}

