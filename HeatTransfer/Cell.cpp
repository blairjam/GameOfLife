#include "Cell.hpp"
#include <iostream>

const sf::Color ht::Cell::DEFAULT_COLOR = sf::Color::White;
const sf::Color ht::Cell::RUNNING_COLOR = sf::Color(183, 0, 0);
const sf::Color ht::Cell::STOPPED_COLOR = sf::Color(73, 73, 73);

const std::string ht::Cell::TEXTURE_LOC = "cell.png";
const float ht::Cell::TEXTURE_SIZE = 32.0f;

std::unique_ptr<sf::Texture> ht::Cell::texture = std::make_unique<sf::Texture>();
std::unique_ptr<bool> ht::Cell::textureLoaded = std::make_unique<bool>();

ht::Cell::Cell(float width, float height, float x, float y, bool filled)
{
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->filled = filled;

    // Load the texture in only once. Each cell will use the same texture.
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

ht::Cell::~Cell()
{
}

void ht::Cell::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void ht::Cell::setScale(float factorX, float factorY)
{
    sprite.setScale(sf::Vector2f(factorX, factorY));
}

void ht::Cell::setFilled(bool filled)
{
    this->filled = filled;
}

const bool ht::Cell::isFilled() const
{
    return filled;
}

void ht::Cell::setColor(const sf::Color& color)
{
    sprite.setColor(color);
}

void ht::Cell::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
}
