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
    std::string textureId;
};

struct SoundComponent {
    std::string soundKey;
    bool triggerOnce = true;
    float volume = 100.f;
    float pitch = 1.f;
    bool played = false;
};