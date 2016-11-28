#include <string>
#include "Window.hpp"

const int WIDTH = 1000;
const int HEIGHT = 1000;
const std::string TITLE = "GoL";
const int CELLS_W = 1000;
const int CELLS_H = 1000;

int main()
{
    std::string title = TITLE + " " + std::to_string(CELLS_W) + "x" + std::to_string(CELLS_H);
    gol::Window window(WIDTH, HEIGHT, title, CELLS_W, CELLS_H);
    window.run();

    return 0;
}
