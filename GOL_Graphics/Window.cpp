#include "Window.hpp"
#include <iostream>
#include <SFML\System.hpp>

gol::Window::Window(uint width, uint height, std::string title, uint cellsWidth, uint cellsHeight)
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

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Close);
    board = std::make_unique<Board>(cellsWidth, cellsHeight, static_cast<float>(width) / static_cast<float>(cellsWidth), static_cast<float>(height) / static_cast<float>(cellsHeight));
}

gol::Window::~Window()
{
}

void gol::Window::run()
{
    // Start new thread for rendering.
    window->setActive(false);
    renderer = std::thread([this] { render(); });

    sf::Clock updateClock;

    // Handle game logic here.
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

void gol::Window::delayedUpdate()
{
    board->update();
}

void gol::Window::update()
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

void gol::Window::render()
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

void gol::Window::handleEvents(sf::Event& eve)
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

void gol::Window::handleMousePressed()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        leftMouseButtonPressed = true;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        rightMouseButtonPressed = true;
}

void gol::Window::handleMouseReleased()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		leftMouseButtonPressed = false;
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
		rightMouseButtonPressed = false;
}

void gol::Window::handleKeyPressed()
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
    {
        std::cout << "Plus: " << updateDelayMultiplier << std::endl;
        if (updateDelayMultiplier < MAX_UPDATE_DELAY_MULT)
            updateDelayMultiplier++;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
    {
        std::cout << "Minus: " << updateDelayMultiplier << std::endl;
        if (updateDelayMultiplier > MIN_UPDATE_DELAY_MULT)
            updateDelayMultiplier--;
    }
}
