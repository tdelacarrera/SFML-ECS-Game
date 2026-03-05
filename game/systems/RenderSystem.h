#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../components/Components.h"
#include "../../engine/Resources.h"

inline void RenderSystem(entt::registry& registry)
{
    auto &window = registry.ctx().get<WindowResource>().window;
    auto &textures = registry.ctx().get<TextureManager>();

    auto view = registry.view<TransformComponent, SpriteComponent>();

    for (auto [entity, transform, sprite] : view.each()) 
    {
        sf::Texture& tex = textures.get(sprite.textureId);
        sf::Sprite drawable(tex);
        drawable.setPosition(transform.position);
        window.draw(drawable);
    }
}