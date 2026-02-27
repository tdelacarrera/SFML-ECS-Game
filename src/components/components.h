#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

struct TransformComponent 
{
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;
};

struct SpriteComponent 
{
    sf::Sprite drawable;
};