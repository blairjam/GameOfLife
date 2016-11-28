#include "Window.hpp"
#include <iostream>
#include <SFML\System.hpp>

gol::Window::Window(int width, int height, std::string title, int cellsWidth, int cellsHeight)
    : window(sf::VideoMode(width, width), title)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->cellsWidth = cellsWidth;
    this->cellsHeight = cellsHeight;

    float squareWidth = static_cast<float>(width) / static_cast<float>(cellsWidth);
    float squareHeight = static_cast<float>(height) / static_cast<float>(cellsHeight);

    float posY = 0.0f;
    float posX = 0.0f;

    for (int y = 0; y < cellsHeight; y++)
    {
        for (int x = 0; x < cellsWidth; x++)
        {
            Cell cell(squareWidth, squareHeight, posX, posY, true);
            cells.push_back(cell);

            posX += squareWidth;
        }

        posX = 0.0f;
        posY += squareHeight;
    }
}

gol::Window::~Window()
{
}

void gol::Window::run()
{
    // Start new thread for rendering.
    window.setActive(false);
    renderer = std::thread([this] { render(); });

    // Handle game logic here.
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    
                    break;
                }
                default:
                    break;
            }
        }
    }

    renderer.join();
}

void gol::Window::render()
{
    // Create a clock for tracking fps.
    sf::Clock clock;
    int frameCount = 0;

    while (window.isOpen())
    {
        window.clear(sf::Color::White);
        draw();
        window.display();

        // If 1 second has passed, display and reset frame count.
        if (clock.getElapsedTime().asMilliseconds() >= 1000)
        {
            window.setTitle(title + " | " + std::to_string(frameCount) + "fps");
            frameCount = 0;
            clock.restart();
        }

        frameCount++;
    }
}

void gol::Window::draw()
{

    for (std::vector<Cell>::iterator it = cells.begin(); it != cells.end(); it++)
    {
        window.draw(it->getSprite());
    }
}
