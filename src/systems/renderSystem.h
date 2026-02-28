#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../utils/textureCache.h"

struct RenderSystem {
    void Draw(entt::registry& registry, TextureCache& textures, sf::RenderWindow& window);
};