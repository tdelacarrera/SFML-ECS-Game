#pragma once

#include <entt/entt.hpp>
#include "../../engine/Resources.h"
#include "../components/Components.h"

inline void TileMapRenderSystem(entt::registry& registry)
{
    auto &window = registry.ctx().get<WindowResource>().window;

    auto &tilemap = registry.ctx().get<TileMapResource>();

    sf::RenderStates states;
    states.texture = &tilemap.texture;
    window.draw(tilemap.vertices, states);
    
}

