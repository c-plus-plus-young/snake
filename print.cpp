#include <SDL2/SDL.h>

// File for functions to handle printing text to the screen
// Each letter is 3x5 pixels, with the top left pixel being
// passed in as variables

// Define colors
const int WHITE = 0;
const int RED = 1;
const int GREEN = 2;
const int BLUE = 3;

void printChar(char c, int color, int x, int y, SDL_Renderer* renderer) {
    if (color == GREEN) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    } else if (color == RED) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    } else {
        // Default to white if color is not recognized
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    switch (c) {
        // Upper case letters
        case 'A':
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y);
            SDL_RenderDrawPoint(renderer, x + 1, y + 2);
            break;
        case 'B':
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 1);
            SDL_RenderDrawLine(renderer, x + 2, y + 3, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y);
            SDL_RenderDrawPoint(renderer, x + 1, y + 2);
            SDL_RenderDrawPoint(renderer, x + 1, y + 4);
            break;
        case 'E':
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 1, y, x + 2, y);
            SDL_RenderDrawLine(renderer, x + 1, y + 2, x + 2, y + 2);
            SDL_RenderDrawLine(renderer, x + 1, y + 4, x + 2, y + 4);
            break;
        case 'G':
            SDL_RenderDrawLine(renderer, x, y, x + 2, y);
            SDL_RenderDrawLine(renderer, x, y + 1, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y + 2, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y + 4);
            break;
        case 'M':
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y + 1);
            break;
        case 'O':
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y);
            SDL_RenderDrawPoint(renderer, x + 1, y + 4);
            break;
        case 'R':
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 1);
            SDL_RenderDrawLine(renderer, x + 2, y + 3, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y);
            SDL_RenderDrawPoint(renderer, x + 1, y + 2);
            break;
            //
            // Add cases for other letters as needed
            //
        case 'S':
            SDL_RenderDrawLine(renderer, x, y, x + 2, y);
            SDL_RenderDrawLine(renderer, x, y + 2, x + 2, y + 2);
            SDL_RenderDrawLine(renderer, x, y + 4, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x, y + 1);
            SDL_RenderDrawPoint(renderer, x + 2, y + 3);
            break;
        case 'V':
            SDL_RenderDrawLine(renderer, x, y, x, y + 3);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 3);
            SDL_RenderDrawPoint(renderer, x + 1, y + 4);
            break;
        // Lower case letters
        case 'a':
            SDL_RenderDrawLine(renderer, x, y + 2, x + 2, y + 2);
            SDL_RenderDrawLine(renderer, x + 2, y + 3, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x, y + 3);
            SDL_RenderDrawPoint(renderer, x + 1, y + 4);
            break;
        case 'k':
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y + 3);
            SDL_RenderDrawPoint(renderer, x + 2, y + 2);
            SDL_RenderDrawPoint(renderer, x + 2, y + 4);
            break;
        case 'n':
            SDL_RenderDrawLine(renderer, x, y + 2, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y + 2, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y + 2);
            break;
        case 'e':
            SDL_RenderDrawLine(renderer, x, y + 2, x + 2, y + 2);
            SDL_RenderDrawLine(renderer, x, y + 4, x + 1, y + 4);
            SDL_RenderDrawPoint(renderer, x, y + 3);
            SDL_RenderDrawPoint(renderer, x + 2, y + 3);
            break;
            //
            // Add cases for other letters as needed
            //
        // Numbers
        case '0':
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y);
            SDL_RenderDrawPoint(renderer, x + 1, y + 4);
            break;
        case '1':
            SDL_RenderDrawLine(renderer, x + 1, y, x + 1, y + 4);
            SDL_RenderDrawPoint(renderer, x, y + 1);
            SDL_RenderDrawLine(renderer, x, y + 4, x + 2, y + 4);
            break;
        case '2':
            SDL_RenderDrawLine(renderer, x, y, x + 2, y);
            SDL_RenderDrawLine(renderer, x, y + 2, x + 2, y + 2);
            SDL_RenderDrawLine(renderer, x, y + 4, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 2, y + 1);
            SDL_RenderDrawPoint(renderer, x, y + 3);
            break;
        case '3':
            SDL_RenderDrawLine(renderer, x, y, x + 2, y);
            SDL_RenderDrawLine(renderer, x, y + 2, x + 2, y + 2);
            SDL_RenderDrawLine(renderer, x, y + 4, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 2, y + 1);
            SDL_RenderDrawPoint(renderer, x + 2, y + 3);
            break;
        case '4':
            SDL_RenderDrawLine(renderer, x, y, x, y + 2);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y + 2);
            break;
        case '5':
            SDL_RenderDrawLine(renderer, x, y, x + 2, y);
            SDL_RenderDrawLine(renderer, x, y + 2, x + 2, y + 2);
            SDL_RenderDrawLine(renderer, x, y + 4, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x, y + 1);
            SDL_RenderDrawPoint(renderer, x + 2, y + 3);
            break;
        case '6':
            SDL_RenderDrawLine(renderer, x, y, x + 2, y);
            SDL_RenderDrawLine(renderer, x, y + 1, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y + 2, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y + 2);
            SDL_RenderDrawPoint(renderer, x + 1, y + 4);
            break;
        case '7':
            SDL_RenderDrawLine(renderer, x, y, x + 2, y);
            SDL_RenderDrawLine(renderer, x + 2, y + 1, x + 2, y + 2);
            SDL_RenderDrawLine(renderer, x + 1, y + 3, x + 1, y + 4);
            break;
        case '8':
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y);
            SDL_RenderDrawPoint(renderer, x + 1, y + 2);
            SDL_RenderDrawPoint(renderer, x + 1, y + 4);
            break;
        case '9':
            SDL_RenderDrawLine(renderer, x, y, x, y + 2);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y);
            SDL_RenderDrawPoint(renderer, x + 1, y + 2);
            break;
        // Symbols
        default:
            // If the letter is not implemented, print a pound sign (#) 
            SDL_RenderDrawLine(renderer, x, y, x, y + 4);
            SDL_RenderDrawPoint(renderer, x + 1, y + 1);
            SDL_RenderDrawPoint(renderer, x + 1, y + 3);
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 4);
    } 
    
    SDL_RenderPresent(renderer);
}