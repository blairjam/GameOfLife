#pragma once

class Cell
{
private:
    bool filled;
public:
    Cell(bool filled);
    ~Cell() {}
    const bool& isFilled() const;
    void setFilled(bool isFilled);
};
