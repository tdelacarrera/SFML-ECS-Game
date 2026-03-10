#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../components/Components.h"
#include "../World/WorldMap.h"
#include "../EntityFactory.h"
#include "../../engine/Pathfinding/Pathfinding.h"

inline void ColonistGenerationSystem(entt::registry& registry)
{
    auto& world = registry.ctx().get<WorldMap>();
    auto& pathfinding = registry.ctx().get<Pathfinding>();

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

                 if(x < 5 && y < 5)
                 {
                  if(rand() % 3 == 1){
                    entt::entity colonist = EntityFactory::createColonist(registry, x * tilemap.tileSize, y * tilemap.tileSize);
                    pathfinding.setDestination(registry, colonist, {158,125});
                  }
                 }
            }
        }
    }
}