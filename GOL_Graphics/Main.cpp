#include "Window.hpp"

#define WIDTH 1000
#define HEIGHT 1000
#define CELLS_W 50
#define CELLS_H 50
#define TITLE "GOL"

int main()
{
    gol::Window window(WIDTH, HEIGHT, TITLE, CELLS_W, CELLS_H);
    window.run();

    return 0;
}
