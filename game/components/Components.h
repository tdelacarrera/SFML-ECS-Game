#pragma once

#include <SFML/Graphics.hpp>

struct TransformComponent 
{
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;
};

struct SpriteComponent 
{
    std::string textureId;
};