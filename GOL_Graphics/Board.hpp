#pragma once

#include <thread>
#include "GOLTypes.hpp"
#include "Cell.hpp"

namespace gol
{
    class Board
    {
    private:
        static const uint UPDATE_THREADS = 4;

        uint width;
        uint height;
        float cellWidth;
        float cellHeight;

        volatile bool updaterRunning;

        CellGroup cells;
        
		void createRow(float posY, uint rowNum);
		void updateRow(uint rowNum, UpdatedCellGroup& updatedCells);
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
