#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../utils/textureManager.h"

struct RenderSystem {
    void draw(entt::registry& registry, TextureManager& textures, sf::RenderWindow& window);
};