#include "Game.hpp"
#include <iostream>
#include <omp.h>

Game::Game(CellBoard board)
    : currentBoard(board), origninalBoard(board)
{
}

void Game::runSerial(unsigned int iterations)
{
    currentBoard = origninalBoard;

    int numRows = currentBoard.getNumRows();

    CellBoard newBoard(numRows, false);

    for (unsigned int i = 0; i < iterations; i++)
    {
        for (int i = 0; i < numRows * numRows; i++)
        {
            int y = i / numRows;
            int x = i % numRows;

            const bool isFilled = currentBoard.getCell(x, y).isFilled();
            if (isFilled && !doesDie(x, y, numRows))
            {
                newBoard.getCell(x, y).setFilled(true);
            }
            else if (!isFilled && doesPopulate(x, y, numRows))
            {
                newBoard.getCell(x, y).setFilled(true);
            }
        }

        currentBoard = newBoard;
    }
}

void Game::runParallel(unsigned int iterations)
{
    currentBoard = origninalBoard;

    int numRows = currentBoard.getNumRows();

    CellBoard newBoard(numRows, false);

    bool flagged = false;

    for (unsigned int i = 0; i < iterations; i++)
    {
        #pragma omp parallel for shared(newBoard)
        for (int i = 0; i < numRows * numRows; i++)
        {
            if (omp_get_num_threads() == 1 && !flagged)
            {
                std::cout << "Only 1 thread." << std::endl;
                flagged = true;
            }
            int y = i / numRows;
            int x = i % numRows;

            const bool isFilled = currentBoard.getCell(x, y).isFilled();
            if (isFilled && !doesDie(x, y, numRows))
            {
                newBoard.getCell(x, y).setFilled(true);
            }
            else if (!isFilled && doesPopulate(x, y, numRows))
            {
                newBoard.getCell(x, y).setFilled(true);
            }
        }

        currentBoard = newBoard;
    }
}

const bool Game::doesDie(const int x, const int y, const int& numRows)
{
    const int filledNeighbors = numFilledNeighbors(x, y, numRows);
    return filledNeighbors <= 1 || filledNeighbors >= 4;
}

const bool Game::doesPopulate(const int x, const int y, const int& numRows)
{
    const int filledNeighbors = numFilledNeighbors(x, y, numRows);
    return filledNeighbors > 1 && filledNeighbors < 4;
}

const int Game::numFilledNeighbors(const int x, const int y, const int& numRows)
{
    int filledNeighbors = 0;

    const bool validNorth = y - 1 >= 0;
    const bool validSouth = y + 1 < numRows;
    const bool validEast = x + 1 < numRows;
    const bool validWest = x - 1 >= 0;

    // Northwest
    if (validNorth && validWest && currentBoard.getCell(x - 1, y - 1).isFilled())
        filledNeighbors++;

    // North
    if (validNorth && currentBoard.getCell(x, y - 1).isFilled())
        filledNeighbors++;

    // Northeast
    if (validNorth && validEast && currentBoard.getCell(x + 1, y - 1).isFilled())
        filledNeighbors++;

    // East
    if (validEast && currentBoard.getCell(x + 1, y).isFilled())
        filledNeighbors++;

    // Southeast
    if (validSouth && validEast && currentBoard.getCell(x + 1, y + 1).isFilled())
        filledNeighbors++;

    // South
    if (validSouth && currentBoard.getCell(x, y + 1).isFilled())
        filledNeighbors++;

    // Southwest
    if (validSouth && validWest && currentBoard.getCell(x - 1, y + 1).isFilled())
        filledNeighbors++;

    // West
    if (validWest && currentBoard.getCell(x - 1, y).isFilled())
        filledNeighbors++;

    return filledNeighbors;
}

void Game::printCurrentBoard() const
{
    currentBoard.print();
}
