#pragma once

#include "renderSystem.h"
#include "../components/components.h"

void RenderSystem::Draw(entt::registry& registry, sf::RenderWindow& window)
{
    auto view = registry.view<TransformComponent, SpriteComponent>();

    for (auto [entity, transform, sprite] : view.each()) {
        sprite.drawable.setPosition(transform.position);
        window.draw(sprite.drawable);
    }
}