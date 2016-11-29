#pragma once

#include <string>
#include <memory>
#include <SFML\Graphics.hpp>

namespace gol
{
    class Cell
    {
    private:
        static const std::string TEXTURE_LOC;
        static const float TEXTURE_SIZE;

        static std::unique_ptr<sf::Texture> texture;
        static std::unique_ptr<bool> textureLoaded;

        float width;
        float height;
        float x;
        float y;
        bool filled;

        sf::Sprite sprite;

    public:
        static const sf::Color DEFAULT_COLOR;
        static const sf::Color RUNNING_COLOR;
        static const sf::Color STOPPED_COLOR;

        Cell(float width, float height, float x, float y, bool filled);
        ~Cell();
        void setPosition(float x, float y);
        void setScale(float factorX, float factorY);
        void setFilled(bool filled);
        const bool isFilled() const;
        void setColor(const sf::Color& color);
        void draw(sf::RenderWindow* window);
		float getY() const
		{
			return y;
		}
    };
}
