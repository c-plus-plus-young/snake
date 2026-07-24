#pragma once
#include <deque>
#include <array>

class Snake {
    private:
        int foodSize;
        int eaten; 
        std::deque<std::array<int, 2>> segments;
        int direction;

    public:
        Snake(int startX, int startY, int endX, int endY);

        void addSegment(int x, int y);

        void removeSegment();

        std::array<int, 2> getSegment(int index);

        void setDirection(int newDirection);

        int getEaten();

        void decrementEaten();

        int getFoodSize();

        int addSegment();

        int getSize();
};