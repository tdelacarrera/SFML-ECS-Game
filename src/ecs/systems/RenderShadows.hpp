#pragma once

#include <entt/entt.hpp>
#include <ecs/components/Components.hpp>
#include "core/textures/TextureManager.hpp"

inline void renderShadows(entt::registry &registry, sf::RenderWindow &window, TextureManager &textures)
{
    auto view = registry.view<Position, Texture, Shadow>();

    for (auto [entity, position, texture, shadow] : view.each())
    {
        sf::Texture &tex = textures.get(texture.textureId);
        sf::Sprite drawable(tex);
        drawable.setPosition(position.value + shadow.offset);
        drawable.setColor(sf::Color(0, 0, 0, 255 * shadow.alpha));
        window.draw(drawable);
    }
}