#pragma once

#include <string>
#include <vector>
#include <thread>
#include <SFML\Graphics.hpp>
#include "Cell.hpp"

namespace gol
{
    class Window
    {
    private:
        int width;
        int height;
        std::string title;
        int cellsWidth;
        int cellsHeight;

        sf::RenderWindow window;
        std::vector<Cell> cells; 
        std::thread renderer;

        void render();
        void draw();

    public:
        Window(int width, int height, std::string title, int cellsWidth, int cellsHeight);
        ~Window();
        void run();
    };
}
