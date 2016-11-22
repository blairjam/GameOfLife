#include "CellBoard.hpp"
#include <chrono>
#include <random>
#include <iostream>

CellBoard::CellBoard(int numRows)
{
    this->numRows = numRows;

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);

    for (int i = 0; i < numRows * numRows; i++)
    {
        cells.emplace_back(Cell(engine() % 3 == 0 ? true : false));
    }
}

CellBoard::CellBoard(int numRows, bool isFilled)
{
    this->numRows = numRows;

    for (int i = 0; i < numRows * numRows; i++)
    {
        cells.emplace_back(Cell(isFilled));
    }
}

Cell& CellBoard::getCell(int x, int y)
{
    return cells[(numRows * y) + x];
}

const int& CellBoard::getNumRows() const
{
    return numRows;
}

void CellBoard::print() const
{
    for (int y = 0; y < numRows; y++)
    {
        for (int x = 0; x < numRows; x++)
        {
            const bool isFilled = cells[(numRows * y) + x].isFilled();
            if (isFilled)
                std::cout << "0";
            else
                std::cout << "X";
        }

        std::cout << "\n";
    }

    std::cout << "\n\n";
}
