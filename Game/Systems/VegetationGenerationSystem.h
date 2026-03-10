#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../Components/Components.h"
#include "../../Engine/Resources.h"
#include "../EntityFactory.h"

inline void VegetationGenerationSystem(entt::registry& registry)
{
    auto& world = registry.ctx().get<WorldMap>();

    auto view = registry.view<TileMapComponent>();

    for(auto entity : view)
    {
        auto& tilemap = view.get<TileMapComponent>(entity);

        int tilesetWidth = tilemap.texture->getSize().x / tilemap.tileSize;

        int v = 0;

        for(int y=0; y<world.height; y++)
        {
            for(int x=0; x<world.width; x++)
            {
                 auto& tile = world.get(x,y);
            
                if(rand() % 3 == 1 && tile.terrain == 3){
                    EntityFactory::createTree(registry, x * tilemap.tileSize, y * tilemap.tileSize);
                }

            }
        }
    }
}