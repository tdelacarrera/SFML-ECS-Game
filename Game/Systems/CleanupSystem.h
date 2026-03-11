#pragma once

#include <entt/entt.hpp>
#include "../Components/Components.h"

inline void CleanupSystem(entt::registry& registry)
{
    auto view = registry.view<TransformComponent, SpriteComponent>();

    for(auto entity : view)
    {
        registry.destroy(entity);
    }
    auto view2 = registry.view<TileMapComponent>();

    for(auto entity : view2)
    {
        registry.destroy(entity);
    }
}