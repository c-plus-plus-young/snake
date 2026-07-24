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
            direction = newDirection;
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

        int getFoodSize() {
            return foodSize;
        }

        int addSegment() {
            //
            return 0;
        }

        int getSize() {
            return segments.size();
        }

        int getDirection() {
            return direction;
        }
};