#pragma once

#include <entt/entt.hpp>
#include "../../Engine/Resources.h"
#include "../Components/Components.h"

inline void TileMapRenderSystem(entt::registry& registry)
{
    auto& window = registry.ctx().get<WindowResource>().window;

    auto view = registry.view<TileMapComponent>();

    for(auto entity : view)
    {
        auto& tilemap = view.get<TileMapComponent>(entity);

        sf::RenderStates states;
        states.texture = tilemap.texture;

        window.draw(tilemap.vertices, states);
    }
}