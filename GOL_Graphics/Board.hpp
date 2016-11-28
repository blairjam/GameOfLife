#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include "GOLTypes.hpp"
#include "Cell.hpp"

namespace gol
{
    struct UpdatedCell
    {
        uint x;
        uint y;
        bool filled;
    };

    class Board
    {
    private:
        static const uint UPDATE_THREADS = 4;

        uint width;
        uint height;
        float cellWidth;
        float cellHeight;

        volatile bool updaterRunning;

        std::vector<std::vector<Cell>> cells;       
        std::mutex cellLock;
        //std::thread updater;
        
        const bool& shouldCellLive(uint x, uint y);
        const bool& shouldCellDie(uint x, uint y);
        const uint& numberCellNeighbors(uint x, uint y);

    public:
        Board(uint width, uint height, float cellWidth, float cellHeight);
        ~Board();
        void start();
        void stop();
        void draw(sf::RenderWindow* window);
        void handleClick(const sf::Vector2i location, const bool fill);
        void update();
    };
}
