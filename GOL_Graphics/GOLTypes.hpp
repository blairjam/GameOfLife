#pragma once

#include <vector>
#include "Cell.hpp"

namespace gol
{
    using uint = unsigned int;

    using CellRow = std::vector<Cell>;
    using CellGroup = std::vector<CellRow>;

    struct UpdatedCell
    {
        uint x;
        uint y;
        bool filled;
    };

    using UpdatedCellGroup = std::vector<UpdatedCell>;
}