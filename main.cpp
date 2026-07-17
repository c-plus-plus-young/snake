#include <SDL2/SDL.h>
#include <deque>
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "print.h"

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
int direction = LEFT;

// Define colors
const int WHITE = 0;
const int RED = 1;
const int GREEN = 2;
const int BLUE = 3;

// Game Setup
bool playing = false; // Forces title screen to show
int foodSize = 3; // Number of segments to grown when food is eaten
int eaten = 0; // Number of segments *left* to grow 
bool foodPlaced = false; // Whether food has been placed on the board 
std::array<int, 2> food{-1, -1}; // Food position
std::deque<std::array<int, 2>> snake;
std::array<std::array<int, 2>, W * H> board; // 2D array to represent the game board

void drawTitle(SDL_Renderer* renderer) {
    printChar('S', WHITE, 6, 4, renderer);
    printChar('n', WHITE, 10, 4, renderer);
    printChar('a', WHITE, 14, 4, renderer);
    printChar('k', WHITE, 18, 4, renderer);
    printChar('e', WHITE, 22, 4, renderer);
}

void drawSnake(std::deque<std::array<int, 2>> snake, SDL_Renderer* renderer, int color) {
    if (color == GREEN) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    } else {
        // Color must be white, as red is for food only
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } 
    
    for (int i = 0; i < snake.size(); i++) {
        int x = snake[i][0];
        int y = snake[i][1];

        SDL_RenderDrawPoint(renderer, x, y);
    }
}

// Update snake position based on direction
// returns false if snake has died
bool updateSnake(std::deque<std::array<int, 2>>& snake, int direction) {
    // Move head in direction
    if (direction == UP) {
        snake.push_front(std::array<int, 2>{snake[0][0], snake[0][1] - 1});
    } else if (direction == DOWN) {
        snake.push_front(std::array<int, 2>{snake[0][0], snake[0][1] + 1});
    } else if (direction == LEFT) {
        snake.push_front(std::array<int, 2>{snake[0][0] - 1, snake[0][1]});
    } else if (direction == RIGHT) {
        snake.push_front(std::array<int, 2>{snake[0][0] + 1, snake[0][1]});
    }

    // Check if head is colliding with walls
    if (snake[0][0] < 0 || snake[0][0] >= W || snake[0][1] < 0 || snake[0][1] >= H) {
        return false;
    }

    // Tail logic. Don't move tail if eaten > 0
    if (eaten > 0) {
        eaten -= 1;
    } else {
        snake.pop_back();
    }

    // check if head is colliding with body. It's important to check this after tail logic
    for (int i = 1; i < snake.size(); i++) {
        if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1]) {
            return false;
        }
    }
     
    // If head is on food, increment eaten
    if (snake[0][0] == food[0] && snake[0][1] == food[1]) {
        eaten += foodSize;
        foodPlaced = false;
    }

    return true;
}

void drawGameOver(SDL_Renderer* renderer, const std::deque<std::array<int, 2>>& snake) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Check length. If snake is maximum length, the game has been won
    if (snake.size() == W * H) {
        // Draw "YOU WIN" message

        


    } else {
        printChar('G', WHITE, 7, 1, renderer);
        printChar('A', WHITE, 11, 1, renderer);
        printChar('M', WHITE, 15, 1, renderer);
        printChar('E', WHITE, 19, 1, renderer);

        printChar('O', WHITE, 7, 7, renderer);
        printChar('V', WHITE, 11, 7, renderer);
        printChar('E', WHITE, 15, 7, renderer);
        printChar('R', WHITE, 19, 7, renderer);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(3000); // Wait for 3 seconds before returning to title screen

    // SDL_RenderClear(renderer);
    printChar('S', WHITE, 6, 4, renderer);
    printChar('C', WHITE, 10, 4, renderer);
    printChar('O', WHITE, 14, 4, renderer);
    printChar('R', WHITE, 18, 4, renderer);
    printChar('E', WHITE, 22, 4, renderer);
    printChar(':', WHITE, 26, 4, renderer);

    for (int i = 0; i < std::to_string(snake.size()).length(); i++) {
        printChar(std::to_string(snake.size())[i], WHITE, 30 + i * 4, 4, renderer);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(3000); // Wait for 3 seconds before returning to title screen
}

// Randomly places food in segments not occupied by the snake.
void drawFood(std::array<int, 2>& food, SDL_Renderer* renderer, const std::deque<std::array<int, 2>>& snake, const std::array<std::array<int, 2>, W * H>& board) {
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
    
    // Initialize snake as deque, and populate first 
    // three segments
    snake.push_front(std::array<int, 2>{15, 7});
    snake.push_front(std::array<int, 2>{14, 7});
    snake.push_front(std::array<int, 2>{13, 7});

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

        if (!playing) {
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
            // play game logic 
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
                if (e.type == SDL_KEYDOWN) {
                    if (SDL_GetKeyName(e.key.keysym.sym) == std::string("W")) {
                        // Snake can't turn 180 degrees
                        if (direction != DOWN) {
                            direction = UP;
                        }
                    } else if (SDL_GetKeyName(e.key.keysym.sym) == std::string("A")) {
                        if (direction != RIGHT) {
                            direction = LEFT;
                        }
                    } else if (SDL_GetKeyName(e.key.keysym.sym) == std::string("S")) {
                        if (direction != UP) {
                            direction = DOWN;
                        }
                    } else if (SDL_GetKeyName(e.key.keysym.sym) == std::string("D")) {
                        if (direction != LEFT) {
                            direction = RIGHT;
                        }
                    }
                } 
            }

            if (updateSnake(snake, direction)) {
                drawSnake(snake, renderer, GREEN);
            } else {
                drawSnake(snake, renderer, WHITE);
                playing = false;
                eaten = 0;
                direction = LEFT;
                snake.clear();
                snake.push_front(std::array<int, 2>{15, 7});
                snake.push_front(std::array<int, 2>{14, 7});
                snake.push_front(std::array<int, 2>{13, 7});
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
