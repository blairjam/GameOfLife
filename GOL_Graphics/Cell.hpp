#pragma once

#include <string>
#include <memory>
#include <SFML\Graphics.hpp>

namespace gol
{
    class Cell
    {
    private:
        static const std::string emptyTextureLoc;
        static const std::string filledTextureLoc;
        static const float textureSize;
        static std::unique_ptr<sf::Texture> emptyTexture;
        static std::unique_ptr<sf::Texture> filledTexture;
        static std::unique_ptr<bool> texturesLoaded;

        float width;
        float height;
        float x;
        float y;
        bool filled;
        
        sf::Sprite sprite;

    public:
        Cell(float width, float height, float x, float y, bool filled);
        ~Cell();
        void setPosition(float x, float y);
        void setScale(float factorX, float factorY);
        void setFilled(bool filled);
        const bool isFilled() const;
        const sf::Sprite& getSprite() const;
    };
}
