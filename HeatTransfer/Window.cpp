#include "Window.hpp"
#include <iostream>
#include <SFML\System.hpp>

ht::Window::Window(uint width, uint height, std::string title, uint cellsWidth, uint cellsHeight)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->cellsWidth = cellsWidth;
    this->cellsHeight = cellsHeight;
    this->updateDelayMultiplier = DEF_UPDATE_DELAY_MULT;

    this->updateDelay = std::make_unique<uint>(DEF_UPDATE_DELAY_MULT * DEF_UPDATE_DELAY_MULT);

    leftMouseButtonPressed = false;
    rightMouseButtonPressed = false;
    spacePressed = false;

    uint dispWidth = sf::VideoMode::getDesktopMode().width;
    uint dispHeight = sf::VideoMode::getDesktopMode().height;
    uint windowPosX = (dispWidth / 2) - (width / 2);
    uint windowPosY = (dispHeight / 2) - (height / 2);

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Close);
    window->setPosition(sf::Vector2i(windowPosX, windowPosY));
    board = std::make_unique<Board>(cellsWidth, cellsHeight,
                                    static_cast<float>(width) / static_cast<float>(cellsWidth),
                                    static_cast<float>(height) / static_cast<float>(cellsHeight));
}

ht::Window::~Window()
{
}

void ht::Window::run()
{
    // Start new thread for rendering.
    window->setActive(false);
    renderer = std::thread([this] { render(); });

    sf::Clock updateClock;
    while (window->isOpen())
    {
        *updateDelay = updateDelayMultiplier * updateDelayMultiplier;

        sf::Event eve;
        while (window->pollEvent(eve))
        {
            handleEvents(eve);
        }

        update();

        if (updateClock.getElapsedTime().asMilliseconds() >= *updateDelay)
        {
            delayedUpdate();
            updateClock.restart();
        }
    }

    renderer.join();
}

void ht::Window::delayedUpdate()
{
    board->update();
}

void ht::Window::update()
{
    sf::Vector2i pos = sf::Mouse::getPosition(*window);

    if (leftMouseButtonPressed)
    {
        board->handleClick(pos, true);
    }

    if (rightMouseButtonPressed)
    {
        board->handleClick(pos, false);
    }
}

void ht::Window::render()
{
    // Create a clock for tracking fps.
    sf::Clock clock;
    int frameCount = 0;

    while (window->isOpen())
    {
        window->clear(sf::Color::White);
        board->draw(window.get());
        window->display();

        // If 1 second has passed, display and reset frame count.
        if (clock.getElapsedTime().asMilliseconds() >= 1000)
        {
            window->setTitle(title + " | " + std::to_string(*updateDelay) + "ms delay | " + std::to_string(frameCount) + "fps");
            frameCount = 0;
            clock.restart();
        }

        frameCount++;
    }
}

void ht::Window::handleEvents(sf::Event& eve)
{
    switch (eve.type)
    {
        case sf::Event::Closed:
        {
            window->close();
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            handleMousePressed();
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            handleMouseReleased();
            break;
        }
        case sf::Event::KeyPressed:
        {
            handleKeyPressed();
            break;
        }
        default:
            break;
    }
}

void ht::Window::handleMousePressed()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        leftMouseButtonPressed = true;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        rightMouseButtonPressed = true;
}

void ht::Window::handleMouseReleased()
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        leftMouseButtonPressed = false;
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
        rightMouseButtonPressed = false;
}

void ht::Window::handleKeyPressed()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (spacePressed)
        {
            board->stop();
            spacePressed = false;
        }
        else
        {
            board->start();
            spacePressed = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) && updateDelayMultiplier < MAX_UPDATE_DELAY_MULT)
    {
        updateDelayMultiplier++;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) && updateDelayMultiplier > MIN_UPDATE_DELAY_MULT)
    {
        updateDelayMultiplier--;
    }
}
