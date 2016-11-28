#include "Cell.hpp"
#include <iostream>

const std::string gol::Cell::emptyTextureLoc = "empty.png";
const std::string gol::Cell::filledTextureLoc = "filled.png";
const float gol::Cell::textureSize = 32.0f;
std::unique_ptr<sf::Texture> gol::Cell::emptyTexture(new sf::Texture());
std::unique_ptr<sf::Texture> gol::Cell::filledTexture(new sf::Texture());
std::unique_ptr<bool> gol::Cell::texturesLoaded(new bool);

gol::Cell::Cell(float width, float height, float x, float y, bool filled)
    : width(width), height(height), x(x), y(y), filled(filled)
{
    if (!(*texturesLoaded = emptyTexture->loadFromFile(emptyTextureLoc) && filledTexture->loadFromFile(filledTextureLoc)))
    {
        std::cout << "Could not load cell textures." << std::endl;
        system("pause");
        exit(1);
    }

    emptyTexture->setSmooth(true);
    filledTexture->setSmooth(true);

    setFilled(filled);
    setPosition(x, y);
    setScale(width / textureSize, height / textureSize);
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

    if (filled)
        sprite.setTexture(*filledTexture);
    else
        sprite.setTexture(*emptyTexture);
}

const bool gol::Cell::isFilled() const
{
    return filled;
}

const sf::Sprite& gol::Cell::getSprite() const
{
    return sprite;
}
