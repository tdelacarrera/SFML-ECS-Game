#pragma once

#include "renderSystem.h"
#include "../components/components.h"

void RenderSystem::draw(entt::registry& registry, TextureManager& textures, sf::RenderWindow& window)
{
    auto view = registry.view<TransformComponent, SpriteComponent>();

    for (auto [entity, transform, sprite] : view.each()) 
    {
        sf::Texture& tex = textures.get(sprite.textureId);
        sf::Sprite drawable(tex);
        drawable.setPosition(transform.position);
        window.draw(drawable);
    }
}
