#pragma once
#include <deque>
#include <array>

class Snake {
    private:
        int foodSize;
        int eaten; 
        std::deque<std::array<int, 2>> segments;
        int direction;
        int boardWidth;
        int boardHeight;

    public:
        Snake(int startX, int startY, int endX, int endY, int boardWidth, int boardHeight);

        void addSegment(int x, int y);

        void removeSegment();

        void setDirection(int newDirection);

        void decrementEaten();

        int getFoodSize() const;

        bool move();
        
        void clear();

        void resetEaten();

        void incrementEaten();

        int getEaten() const;

        int getSize() const;

        std::array<int, 2> getSegment(int index) const;

        int getDirection() const;

        bool findSegment(int x, int y) const;
};