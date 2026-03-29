#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "Components/Components.h"
#include "Engine/Resources.h"
#include "Entities/Entities.h"

inline void StoneGenerationSystem(entt::registry& registry)
{
    auto& world = registry.ctx().get<WorldMap>();

    auto view = registry.view<TileMapComponent>();
    

 

    for(int y=0; y<world.height; y++)
    {
        for(int x=0; x<world.width; x++)
        {
            auto& tile = world.get(x,y);
            
            if(tile.terrain == 4){
                EntityFactory::createStone(registry, x * world.tileSize, y * world.tileSize);
            }
         }
    }
    
}