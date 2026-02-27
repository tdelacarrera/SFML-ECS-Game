#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

struct RenderSystem {
    void Draw(entt::registry& registry, sf::RenderWindow& window);
};