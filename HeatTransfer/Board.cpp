#include "Board.hpp"
#include <iostream>
#include <string>
#include "Timer.hpp"

#define CLASSIC_GOL 1
#define UPDATE_MAX 250000

ht::Board::Board(uint width, uint height, float cellWidth, float cellHeight)
{
    this->width = width;
    this->height = height;
    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;

    updaterRunning = false;

    cells.resize(height);

    // Build board in parallel. Each created row is stored in the unordered_map to be inserted into the final vector.
    #pragma omp parallel
    {
        #pragma omp for
        for (int y = 0; y < height; y++)
        {
            createRow(y * cellHeight, y);
        }
    }
}

ht::Board::~Board()
{
}

void ht::Board::start()
{
    updaterRunning = true;
}

void ht::Board::stop()
{
    updaterRunning = false;
}

void ht::Board::draw(sf::RenderWindow* window)
{
    // Call draw for each cell. Assign color before drawing.
    for (uint y = 0; y < height; y++)
    {
        for (uint x = 0; x < width; x++)
        {
            sf::Color newColor = Cell::DEFAULT_COLOR;

            if (cells[y][x].isFilled() && updaterRunning)
            {
                newColor = Cell::RUNNING_COLOR;
            }
            else if (cells[y][x].isFilled() && !updaterRunning)
            {
                newColor = Cell::STOPPED_COLOR;
            }

            cells[y][x].setColor(newColor);
            cells[y][x].draw(window);
        }
    }
}

void ht::Board::handleClick(const sf::Vector2i location, const bool fill)
{
    if (updaterRunning)
        return;

    // Find location of cell with integer division.
    uint cellX = location.x / cellWidth;
    uint cellY = location.y / cellHeight;

    // If position is out of bounds, return.
    if (cellX >= width || cellY >= height)
        return;

    cells[cellY][cellX].setFilled(fill);
}

void ht::Board::update()
{
    if (!updaterRunning)
        return;

    UpdatedCellGroup updatedCells;

    // Run update in parallel if fewer than 250,000 cells. Otherwise the speed is fast enough.
    #pragma omp parallel shared(updatedCells) if(width * height >= UPDATE_MAX) 
    {
        #pragma omp for schedule(guided)
        for (int y = 0; y < height; y++)
        {
            updateRow(y, updatedCells);
        }
    }

    // Updated needed cells.
    for (UpdatedCellGroup::iterator it = updatedCells.begin(); it != updatedCells.end(); it++)
    {
        if (it->y >= height || it->y < 0)
            int d = 0;
        if (it->x >= width || it->x < 0)
            int d = 1;

        cells[it->y][it->x].setFilled(it->filled);
    }
}

void ht::Board::createRow(float posY, uint rowNum)
{
    CellRow row;

    float posX = 0.0f;

    // Create cells for the row.
    for (uint x = 0; x < width; x++)
    {
        row.push_back(Cell(cellWidth, cellHeight, posX, posY, false));
        posX += cellWidth;
    }

    cells[rowNum] = row;
}

void ht::Board::updateRow(uint rowNum, UpdatedCellGroup& updatedCells)
{
    // Iterate through cells and decide if it should be updated.
    for (uint x = 0; x < width; x++)
    {
        const bool isCellFilled = cells[rowNum][x].isFilled();

        if (isCellFilled && shouldCellDie(x, rowNum))
        {
            #pragma omp critical
        {
            updatedCells.push_back({ x, rowNum, false });
        }
        }
        else if (!isCellFilled && shouldCellLive(x, rowNum))
        {
            #pragma omp critical
        {
            updatedCells.push_back({ x, rowNum, true });
        }
        }
    }
}

const bool& ht::Board::shouldCellLive(uint x, uint y)
{
    const int neighbors = numberCellNeighbors(x, y);

    // Decide if cell should be populated based on number of neighbors.
    #if CLASSIC_GOL
    return neighbors == 3;
    #else
    return neighbors == 2 || neighbors == 3;
    #endif
}

const bool& ht::Board::shouldCellDie(uint x, uint y)
{
    const int neighbors = numberCellNeighbors(x, y);

    // Decide if cell should be unpopulated based on number of people.
    return neighbors <= 1 || neighbors >= 4;
}

const ht::uint& ht::Board::numberCellNeighbors(uint x, uint y)
{
    uint neighbors = 0;

    long _x = static_cast<long>(x);
    long _y = static_cast<long>(y);

    // Check that cell locations are valid.
    const bool validNorth = _y - 1 >= 0;
    const bool validSouth = _y + 1 < height;
    const bool validEast = _x + 1 < width;
    const bool validWest = _x - 1 >= 0;

    // Test if neighbor is filled, updated count if it is.

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
