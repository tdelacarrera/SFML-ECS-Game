#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../Components/Components.h"
#include "../../Engine/Resources.h"
#include "../../Engine/Textures/TextureManager.h"

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
        sf::Vector2u size = tex.getSize();
        drawable.setOrigin({size.x * 0.5, size.y * 0.5});
        window.draw(drawable);
    }
}