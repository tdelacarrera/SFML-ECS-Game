#pragma once

#include <entt/entt.hpp>
#include <ecs/components/Components.hpp>
#include "core/textures/TextureManager.hpp"

inline void renderSystem(entt::registry &registry, sf::RenderWindow &window, TextureManager &textures)
{
    auto view = registry.view<Position, Texture>();

    for (auto [entity, position, Texture] : view.each())
    {
        sf::Texture &tex = textures.get(Texture.textureId);
        sf::Sprite drawable(tex);
        drawable.setPosition(position.value);
        window.draw(drawable);
    }
}

