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






int main(int argc, char* argv[]) {
    // Initialize SDL
    SDL_Surface* screen = NULL;
    if (init(&screen) == -1) {
        return 1;
    }

    // Load the game images
    SDL_Surface* x_img = NULL;
    SDL_Surface* o_img = NULL;
    SDL_Surface* bg_img = NULL;
    if (load_files(&x_img, &o_img, &bg_img) == -1) {
        clean_up(x_img, o_img, bg_img);
        return 1;
    }

    // Initialize the game board
    int board[9] = {0};
    int turn = 1;

    // Main game loop
    int quit = 0;
    while (!quit) {
        // Handle events
        quit = handle_events(screen, x_img, o_img, bg_img, board, &turn);

        // Draw the game board
        draw_board(screen, x_img, o_img, bg_img, board);

        // Check for a winner
        int winner = check_win(board);
        if (winner != 0) {
            SDL_Delay(1000);
            char message[30];
            if (winner == 1) {
                sprintf(message, "X wins!");
            }
            else if (winner == 2) {
                sprintf(message, "O wins!");
            }
            else {
                sprintf(message, "Tie game!");
            }
            SDL_WM_SetCaption(message, NULL);
            SDL_Delay(2000);
            quit = 1;
        }

        // Update the screen
        if (SDL_Flip(screen) == -1) {
            quit = 1;
        }
    }

    // Clean up and quit SDL
    clean_up(x_img, o_img, bg_img);
    return 0;
}

