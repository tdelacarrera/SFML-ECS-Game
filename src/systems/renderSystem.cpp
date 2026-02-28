#pragma once

#include "renderSystem.h"
#include "../components/components.h"

void RenderSystem::Draw(entt::registry& registry, TextureCache& textures, sf::RenderWindow& window)
{
    auto view = registry.view<TransformComponent, SpriteComponent>();

    for (auto [entity, transform, sprite] : view.each()) 
    {
        sf::Texture& tex = textures.Get(sprite.textureKey);
        sf::Sprite drawable(tex);
        drawable.setPosition(transform.position);
        window.draw(drawable);
    }
}
