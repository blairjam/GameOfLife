#include "Cell.hpp"

Cell::Cell(bool filled)
{
    this->filled = filled;
}

const bool& Cell::isFilled() const
{
    return filled;
}

void Cell::setFilled(bool filled)
{
    this->filled = filled;
}
