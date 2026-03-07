#pragma once

#include <entt/entt.hpp>
#include "../../engine/Resources.h"


inline void WorldGenerationSystem(entt::registry& registry)
{
    auto& world = registry.ctx().get<WorldMap>();

    world.tiles.resize(world.width * world.height);

    for(int y=0;y<world.height;y++)
    {
        for(int x=0;x<world.width;x++)
        {
            auto& tile = world.get(x,y);

            tile.terrain = 0;
            tile.walkable = true;
            tile.buildable = true;
        }
    }
}