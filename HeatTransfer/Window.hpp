#pragma once

#include <string>
#include <vector>
#include <thread>
#include <memory>
#include <SFML\Graphics.hpp>
#include "HTTypes.hpp"
#include "Board.hpp"

namespace ht
{
    class Window
    {
    private:
        static const uint DEF_UPDATE_DELAY_MULT = 20;
        static const uint MAX_UPDATE_DELAY_MULT = 50;
        static const uint MIN_UPDATE_DELAY_MULT = 0;

        uint width;
        uint height;
        std::string title;
        uint cellsWidth;
        uint cellsHeight;
        uint updateDelayMultiplier;

        std::unique_ptr<uint> updateDelay;

        bool leftMouseButtonPressed;
        bool rightMouseButtonPressed;
        bool spacePressed;

        std::unique_ptr<sf::RenderWindow> window;
        std::thread renderer;

        std::unique_ptr<Board> board;

        void delayedUpdate();
        void update();
        void render();
        void handleEvents(sf::Event& eve);
        void handleMousePressed();
        void handleMouseReleased();
        void handleKeyPressed();

    public:
        Window(uint width, uint height, std::string title, uint cellsWidth, uint cellsHeight);
        ~Window();
        void run();
    };
}
