#pragma once

#include <vector>
#include "Cell.hpp"

class CellBoard
{
    int numRows;
    std::vector<Cell> cells;
public:
    CellBoard(int numRows);
    CellBoard(int numRows, bool isFilled);
    ~CellBoard() {}
    Cell& getCell(int x, int y);
    const int& getNumRows() const;
    void print() const;
};
