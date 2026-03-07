#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../components/Components.h"
#include "../../engine/Resources.h"
#include "../EntityFactory.h"

inline void AnimalGenerationSystem(entt::registry& registry)
{
    auto& world = registry.ctx().get<WorldMap>();

    world.tiles.resize(world.width * world.height);

    for(int y=0;y<world.height;y++)
    {
        for(int x=0;x<world.width;x++)
        {

        }
    }
}