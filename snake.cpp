#include <deque>
#include <array>

// Define directions;
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

class Snake {
    private:
        int foodSize = 3; // Number of segments to grown when food is eaten
        int eaten = 0; // Number of segments *left* to grow 
        std::deque<std::array<int, 2>> segments;
        int direction;

    public:
        Snake(int startX, int startY, int endX, int endY) {
            for (int i = startX; i <= endX; ++i) {
                segments.push_back({i, startY});
            }
            direction = LEFT; // Default direction
        }

        void addSegment(int x, int y) {
            segments.push_back({x, y});
        }

        void removeSegment() {
            if (!segments.empty()) {
                segments.pop_back();
            }
        }

        std::array<int, 2> getSegment(int index) {
            if (index >= 0 && index < segments.size()) {
                return segments[index];
            }
            return {};
        }

        void setDirection(int newDirection) {
            if (newDirection == UP && direction == DOWN 
                || newDirection == LEFT && direction == RIGHT
                || newDirection == DOWN && direction == UP
                || newDirection == RIGHT && direction == LEFT) {
                // Do nothing, as the new direction is the opposite of the current direction
            } else {
                direction = newDirection;
            }
        }

        int getEaten() {
            return eaten;
        }

        void decrementEaten() {
            eaten -= 1;
        }

        void resetEaten() {
            eaten = 0;
        }

        void incrementEaten() {
            eaten += foodSize;
        }

        // Check if snake is colliding returning false 
        // if it is and true if it is not
        bool move() {
            if (eaten > 0) {
                decrementEaten();
            } else {
                removeSegment();

                if (direction == UP) {
                    addSegment(segments.front()[0], segments.front()[1] - 1);
                } else if (direction == DOWN) {
                    addSegment(segments.front()[0], segments.front()[1] + 1);
                } else if (direction == LEFT) {
                    addSegment(segments.front()[0] - 1, segments.front()[1]);
                } else if (direction == RIGHT) {
                    addSegment(segments.front()[0] + 1, segments.front()[1]);
                }
            }
            for (int i = 1; i < segments.size(); i++) {
                if (segments.front()[0] == segments[i][0] && segments.front()[1] == segments[i][1]) {
                    return false; // Collision detected
                }
            }
            return true; // No collision
        }

        int getFoodSize() {
            return foodSize;
        }

        int getSize() {
            return segments.size();
        }

        int getDirection() {
            return direction;
        }
};