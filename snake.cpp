#include <deque>
#include <array>
#include "snake.h"
#include <iostream>

// Define directions;
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

Snake::Snake(int startX, int startY, int endX, int endY, int boardWidth, int boardHeight) {
    foodSize = 3; // Number of segments to grown when food is eaten
    eaten = 0; // Number of segments *left* to grow
    this->boardWidth = boardWidth;
    this->boardHeight = boardHeight;
    for (int i = startX; i <= endX; ++i) {
        segments.push_back({i, startY});
    }
    direction = LEFT; // Default direction
}

void Snake::addSegment(int x, int y) {
    segments.push_front({x, y});
}

void Snake::removeSegment() {
    if (!segments.empty()) {
        segments.pop_back();
    }
}

std::array<int, 2> Snake::getSegment(int index) const {
    if (index >= 0 && index < segments.size()) {
        return segments[index];
    }
    return {};
}

void Snake::setDirection(int newDirection) {
    if (newDirection == UP && direction == DOWN 
        || newDirection == LEFT && direction == RIGHT
        || newDirection == DOWN && direction == UP
        || newDirection == RIGHT && direction == LEFT) {
        // Do nothing, as the new direction is the opposite of the current direction
    } else {
        direction = newDirection;
    }
}

int Snake::getEaten() const {
    return eaten;
}

void Snake::decrementEaten() {
    eaten -= 1;
}

void Snake::resetEaten() {
    eaten = 0;
}

void Snake::incrementEaten() {
    eaten += foodSize;
}

// Check if snake is colliding returning false 
// if it is and true if it is not
bool Snake::move() {
    std::cout << "move(): size = " << segments.size() << '\n';
    std::cout << "direction = " << direction << '\n';
    if (eaten > 0) {
        decrementEaten();
    } else {
        removeSegment();
    }

    if (direction == UP) {
        addSegment(segments.front()[0], segments.front()[1] - 1);
    } else if (direction == DOWN) {
        addSegment(segments.front()[0], segments.front()[1] + 1);
    } else if (direction == LEFT) {
        addSegment(segments.front()[0] - 1, segments.front()[1]);
    } else if (direction == RIGHT) {
        addSegment(segments.front()[0] + 1, segments.front()[1]);
    }
    if (segments.front()[0] < 0 || segments.front()[0] >= boardWidth || segments.front()[1] < 0 || segments.front()[1] >= boardHeight) {
        return false; // Collision with wall
    }
    for (int i = 1; i < segments.size(); i++) {
        if (segments.front()[0] == segments[i][0] && segments.front()[1] == segments[i][1]) {
            return false; // Collision detected
        }
    }
    return true; // No collision
}

int Snake::getFoodSize() const {
    return foodSize;
}

int Snake::getSize() const {
    return segments.size();
}

int Snake::getDirection() const {
    return direction;
}

bool Snake::findSegment(int x, int y) const {
    for (const auto& segment : segments) {
        if (segment[0] == x && segment[1] == y) {
            return true;
        }
    }
    return false;
}

void Snake::clear() {
    segments.clear();
}