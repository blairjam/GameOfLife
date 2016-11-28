#include "Cell.hpp"
#include <iostream>

const sf::Color gol::Cell::DEFAULT_COLOR = sf::Color::White;
const sf::Color gol::Cell::RUNNING_COLOR = sf::Color(183, 0, 0);
const sf::Color gol::Cell::STOPPED_COLOR = sf::Color(73, 73, 73);

const std::string gol::Cell::TEXTURE_LOC = "cell.png";
const float gol::Cell::TEXTURE_SIZE = 32.0f;

std::unique_ptr<sf::Texture> gol::Cell::texture = std::make_unique<sf::Texture>();
std::unique_ptr<bool> gol::Cell::textureLoaded = std::make_unique<bool>();

gol::Cell::Cell(float width, float height, float x, float y, bool filled)
{
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->filled = filled;

    if (!*textureLoaded)
    {
        if (!texture->loadFromFile(TEXTURE_LOC))
        {
            std::cout << "Could not load cell textures." << std::endl;
            system("pause");
            exit(1);
        }
        
        *textureLoaded = true;
    }

    texture->setSmooth(true);

    sprite.setTexture(*texture);

    setFilled(filled);
    setPosition(x, y);
    setScale(width / TEXTURE_SIZE, height / TEXTURE_SIZE);
}

gol::Cell::~Cell()
{
}

void gol::Cell::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void gol::Cell::setScale(float factorX, float factorY)
{
    sprite.setScale(sf::Vector2f(factorX, factorY));
}

void gol::Cell::setFilled(bool filled)
{
    this->filled = filled;
}

const bool gol::Cell::isFilled() const
{
    return filled;
}

void gol::Cell::setColor(const sf::Color& color)
{
    sprite.setColor(color);
}

void gol::Cell::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
}
