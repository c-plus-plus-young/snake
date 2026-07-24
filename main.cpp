#include <SDL2/SDL.h>
#include <deque>
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "print.h"
#include "snake.h"

// Initialize screen 
const int W = 30;
const int H = 20;
const int SCALE = 30;
int screen[H][W];

// Frame Data
const int TARGET_FPS = 15;
const int FRAME_DELAY = 1000 / TARGET_FPS;
Uint32 frameStart;
int frameTime;

// Define directions;
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

// Define colors
const int WHITE = 0;
const int RED = 1;
const int GREEN = 2;
const int BLUE = 3;

// Game Setup
bool playing = false; // Forces title screen to show
bool foodPlaced = false; // Whether food has been placed on the board 
std::array<int, 2> food{-1, -1}; // Food position
std::array<std::array<int, 2>, W * H> board; // 2D array to represent the game board
waitCount = 0; // Counter for waiting on various screens

void drawTitle(SDL_Renderer* renderer) {
    printString("Snake", WHITE, 6, 4, renderer);
}

void drawSnake(Snake snake, SDL_Renderer* renderer, int color) {
    if (color == GREEN) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    } else {
        // Color must be white, as red is for food only
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } 
    
    
    for (int i = 0; i < snake.getSize(); i++) {
        std::array<int, 2> segment = snake.getSegment(i);
        int x = segment[0];
        int y = segment[1];

        SDL_RenderDrawPoint(renderer, x, y);
    }
}

// Update snake position based on direction
// returns false if snake has died
bool updateSnake(Snake snake, int direction) {
    bool returnVal = snake.move();
     
    // If head is on food, increment eaten
    if (snake.getSegment(0)[0] == food[0] && snake.getSegment(0)[1] == food[1]) {
        snake.incrementEaten();
        foodPlaced = false;
    }

    return returnVal;
}

void drawGameOver(SDL_Renderer* renderer, Snake snake) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Check length. If snake is maximum length, the game has been won
    if (snake.getSize() >= W * H) {
        printString("YOU", WHITE, 7, 1, renderer);
        printString("WIN", WHITE, 7, 7, renderer);
    } else {
        printString("GAME", WHITE, 7, 1, renderer);
        printString("OVER", WHITE, 7, 7, renderer);
    }
    SDL_RenderPresent(renderer);
    waitCount = 3 * FRAME_DELAY; // Wait for 3 seconds before returning to title screen

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    printString("SCORE:", WHITE, 3, 4, renderer);

    for (int i = 0; i < std::to_string(snake.getSize()).length(); i++) {
        std::cout << snake.getSize() << "\n";
        // printChar(std::to_string(snake.getSize()), WHITE, 7 + i * 4, 10, renderer);
    }
    SDL_RenderPresent(renderer);
    waitCount = 3 * FRAME_DELAY; // Wait for 3 seconds before returning to title screen
}

// Randomly places food in segments not occupied by the snake.
void drawFood(std::array<int, 2>& food, SDL_Renderer* renderer, Snake snake, const std::array<std::array<int, 2>, W * H>& board) {
    if (!foodPlaced) {
        std::vector<std::array<int, 2>> availableSpaces;
        for (int i = 0; i < board.size(); i++) {
            if (std::find(snake.begin(), snake.end(), board[i]) == snake.end()) {
                availableSpaces.push_back(board[i]);
            }
        }

        if (!availableSpaces.empty()) {
            int randomIndex = rand() % availableSpaces.size();
            food = availableSpaces[randomIndex];
            foodPlaced = true;
        } else {
            // No available spaces left, game over
            playing = false;
            drawGameOver(renderer, snake);
        }
    }
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, food[0], food[1]);
}

// int main(int argc, char* argv[]) {
int main(int argc, char* argv[]) {
    Snake snake(15, 7, 13, 7); // Initialize snake with starting segments

    // Initialize Board
    for (int i = 0; i < W * H; i++) {
        board[i] = std::array<int, 2>{i % W, i / W};
    }
    
    // Initialize SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;

    // // Initialize controller
    // SDL_GameController* controller = nullptr;

    SDL_CreateWindowAndRenderer(W * SCALE, H * SCALE, 
        0, &window, &renderer);
    SDL_RenderSetScale(renderer, SCALE, SCALE);

    // Make taskbar title
    SDL_SetWindowTitle(window, "Snake");
    // Make taskbar icon

    SDL_Surface* icon = SDL_LoadBMP("./sprites/system/snake_icon.bmp");
    if (icon != nullptr) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    } else {
        std::cout << "Failed to load icon: " << SDL_GetError() << "\n";
    }

    while (running) {
        frameStart = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        waitCount = 0;

        if (!playing) {
            if (waitCount <= 0) {
                // Render title screen and animation
                drawTitle(renderer);
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        running = false;
                    } else if (e.type == SDL_KEYDOWN) {
                        std::cout << "Key pressed: " << SDL_GetKeyName(e.key.keysym.sym) << "\n";
                        if (SDL_GetKeyName(e.key.keysym.sym) == std::string("W") || SDL_GetKeyName(e.key.keysym.sym) == std::string("A") || SDL_GetKeyName(e.key.keysym.sym) == std::string("S") || SDL_GetKeyName(e.key.keysym.sym) == std::string("D")) {
                            playing = true;
                            std::cout << "Starting game...\n";
                        } else {
                            drawTitle(renderer);


                            // title screen animation logic
                        }
                    } 
                }
            } else {
                waitCount -= 1 * FRAME_DELAY;
                if (waitCount <= 0) {
                    waitCount = 0;
                    waiting = false;
                }
            }
        } else {
            // play game logic 
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
                if (e.type == SDL_KEYDOWN) {
                    if (SDL_GetKeyName(e.key.keysym.sym) == std::string("W")) {
                        // Snake can't turn 180 degrees
                        if (snake.getDirection() != DOWN) {
                            snake.setDirection(UP);
                        }
                    } else if (SDL_GetKeyName(e.key.keysym.sym) == std::string("A")) {
                        if (snake.getDirection() != RIGHT) {
                            snake.setDirection(LEFT);
                        }
                    } else if (SDL_GetKeyName(e.key.keysym.sym) == std::string("S")) {
                        if (snake.getDirection() != UP) {
                            snake.setDirection(DOWN);
                        }
                    } else if (SDL_GetKeyName(e.key.keysym.sym) == std::string("D")) {
                        if (snake.getDirection() != LEFT) {
                            snake.setDirection(RIGHT);
                        }
                    }
                } 
            }

            if (updateSnake(snake, direction)) {
                drawSnake(snake, renderer, GREEN);
            } else {
                drawSnake(snake, renderer, WHITE);
                playing = false;
                snake.resetEaten();
                snake.setDirection(LEFT);
                snake.clear();
                snake.addSegment(std::array<int, 2>{15, 7});
                snake.addSegment(std::array<int, 2>{14, 7});
                snake.addSegment(std::array<int, 2>{13, 7});
                drawGameOver(renderer, snake);
            }
            drawFood(food, renderer, snake, board);
        }

        SDL_RenderPresent(renderer);

        // wait until next frame
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 0;
}
