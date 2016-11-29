#include <string>
#include "Window.hpp"

const int WIDTH = 800;
const int HEIGHT = 800;
const std::string TITLE = "GoL";
const int CELLS_W = 800;
const int CELLS_H = 800;

int main()
{
    std::string title = TITLE + " " + std::to_string(CELLS_W) + "x" + std::to_string(CELLS_H);
    gol::Window window(WIDTH, HEIGHT, title, CELLS_W, CELLS_H);
    window.run();

    return 0;
}
