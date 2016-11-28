#include "Board.hpp"
#include <iostream>
#include <unordered_set>
#include <string>
#include "Timer.hpp"

#define CLASSIC_GOL 1

gol::Board::Board(uint width, uint height, float cellWidth, float cellHeight)
{
    this->width = width;
    this->height = height;
    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;

    updaterRunning = false;

    float posX = 0.0f;
    float posY = 0.0f;

    std::unordered_set<std::string, std::vector<Cell>> createdRows;

    for (uint y = 0; y < height; y++)
    {
        std::vector<Cell> row;
        for (uint x = 0; x < width; x++)
        {
            Cell cell(cellWidth, cellHeight, posX, posY, false);
            row.push_back(cell);

            posX += cellWidth;
        }

        posX = 0.0f;
        posY += cellHeight;

        cells.push_back(row);
    }
}

gol::Board::~Board()
{
}

void gol::Board::start()
{
    updaterRunning = true;
    //updater = std::thread([this] { update(); });
}

void gol::Board::stop()
{
    updaterRunning = false;
    //updater.join();
}

void gol::Board::draw(sf::RenderWindow* window)
{
    cellLock.lock();
    for (uint y = 0; y < height; y++)
    {
        for (uint x = 0; x < width; x++)
        {
            Cell& cell = cells[y][x];
            sf::Color newColor = Cell::DEFAULT_COLOR;

            if (cell.isFilled() && updaterRunning)
            {
                newColor = Cell::RUNNING_COLOR;
            }
            else if (cell.isFilled() && !updaterRunning)
            {
                newColor = Cell::STOPPED_COLOR;
            }

            cell.setColor(newColor);
            cell.draw(window);
        }
    }
    cellLock.unlock();
}

void gol::Board::handleClick(const sf::Vector2i location, const bool fill)
{
    if (updaterRunning)
        return;

    uint cellX = location.x / cellWidth;
    uint cellY = location.y / cellHeight;

    cells[cellY][cellX].setFilled(fill);
}

void gol::Board::update()
{
    if (!updaterRunning)
        return;

    std::vector<UpdatedCell> updatedCells;

    for (uint y = 0; y < height; y++)
    {
        for (uint x = 0; x < width; x++)
        {
            const bool isCellFilled = cells[y][x].isFilled();

            bool tempDie = shouldCellDie(x, y);
            bool tempLive = shouldCellLive(x, y);

            if (isCellFilled && shouldCellDie(x, y))
                updatedCells.push_back({ x, y, false });
            else if (!isCellFilled && shouldCellLive(x, y))
                updatedCells.push_back({ x, y, true });
        }
    }

    cellLock.lock();
    for (std::vector<UpdatedCell>::iterator it = updatedCells.begin(); it != updatedCells.end(); it++)
    {
        cells[it->y][it->x].setFilled(it->filled);
    }
    cellLock.unlock();
}

const bool& gol::Board::shouldCellLive(uint x, uint y)
{
    const int neighbors = numberCellNeighbors(x, y);

    #if CLASSIC_GOL
    return neighbors == 3;
    #else
    return neighbors == 2 || neighbors == 3;
    #endif
}

const bool& gol::Board::shouldCellDie(uint x, uint y)
{
    const int neighbors = numberCellNeighbors(x, y);
    return neighbors <= 1 || neighbors >= 4;
}

const gol::uint& gol::Board::numberCellNeighbors(uint x, uint y)
{
    uint neighbors = 0;

    long _x = static_cast<long>(x);
    long _y = static_cast<long>(y);

    const bool validNorth = _y - 1 >= 0;
    const bool validSouth = _y + 1 < height;
    const bool validEast = _x + 1 < width;
    const bool validWest = _x - 1 >= 0;

    if (validNorth && validWest && cells[_y - 1][_x - 1].isFilled())
        neighbors++;

    if (validNorth && cells[_y - 1][_x].isFilled())
        neighbors++;

    if (validNorth && validEast && cells[_y - 1][_x + 1].isFilled())
        neighbors++;

    if (validEast && cells[_y][_x + 1].isFilled())
        neighbors++;

    if (validSouth && validEast && cells[_y + 1][_x + 1].isFilled())
        neighbors++;

    if (validSouth && cells[_y + 1][_x].isFilled())
        neighbors++;

    if (validSouth && validWest && cells[_y + 1][_x - 1].isFilled())
        neighbors++;

    if (validWest && cells[_y][_x - 1].isFilled())
        neighbors++;

    return neighbors;
}
