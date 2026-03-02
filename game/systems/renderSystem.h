#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../../engine/graphics/textureManager.h"

struct RenderSystem {
    void draw(entt::registry& registry, TextureManager& textures, sf::RenderWindow& window);
};