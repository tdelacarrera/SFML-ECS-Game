#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <FastNoiseLite.h>
#include "../components/Components.h"
#include "../../engine/Resources.h"
#include "../EntityFactory.h"

inline void TerrainGenerationSystem(entt::registry& registry)
{
    FastNoiseLite noise;
    
    auto& world = registry.ctx().get<WorldMap>();

    world.tiles.resize(world.width * world.height);

    for(int y=0;y<world.height;y++)
    {
        for(int x=0;x<world.width;x++)
        {
            float n = noise.GetNoise((float)x, (float)y);

            auto& tile = world.get(x,y);

            if(n < -0.4){
                tile.terrain = 0;  
            }    
            else if(n < -0.1){
                tile.terrain = 1; 
            }
            else if(n < 0.2)
            {
                 tile.terrain = 2; 
            }
            else if(n < 0.5){
                 tile.terrain = 3; 
            }
            else
            {
                tile.terrain = 4;   
            }        
            tile.walkable = true;
            tile.buildable = true;
        }
    }
}