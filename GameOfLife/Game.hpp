#pragma once

#include "CellBoard.hpp"

class Game
{
private:
    CellBoard currentBoard;
    CellBoard origninalBoard;

    const bool doesDie(const int x, const int y, const int& numRows);
    const bool doesPopulate(const int x, const int y, const int& numRows);
    const int numFilledNeighbors(const int x, const int y, const int& numRows);

public:
    Game(CellBoard board);
    ~Game() {}
    void runSerial(unsigned int iterations);
    void runParallel(unsigned int iterations);
    void printCurrentBoard() const;
};

