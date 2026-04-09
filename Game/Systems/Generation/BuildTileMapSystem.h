#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "Components/Components.h"
#include "Engine/Resources.h"

inline void BuildTileMapSystem(entt::registry& registry)
{
    auto& world = registry.ctx().get<WorldMap>();

    auto view = registry.view<TileMapComponent>();

    for(auto entity : view)
    {
        auto& tilemap = view.get<TileMapComponent>(entity);

        tilemap.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        tilemap.vertices.resize(world.width * world.height * 6);

        int tilesetWidth = tilemap.texture->getSize().x / world.tileSize;

        int v = 0;

        for(int y=0; y<world.height; y++)
        {
            for(int x=0; x<world.width; x++)
            {
                auto& tile = world.get(x,y);

                int tileNumber = tile.terrain;

                int tu = tileNumber % tilemap.tilesetWidth;
                int tv = tileNumber / tilemap.tilesetWidth;

                float px = x * world.tileSize;
                float py = y * world.tileSize;

                float tx = tu * world.tileSize;
                float ty = tv * world.tileSize;

                sf::Vertex* quad = &tilemap.vertices[v];

                quad[0].position = {px, py};
                quad[1].position = {px + world.tileSize, py};
                quad[2].position = {px + world.tileSize, py + world.tileSize};

                quad[3].position = {px, py};
                quad[4].position = {px + world.tileSize, py + world.tileSize};
                quad[5].position = {px, py + world.tileSize};

                float mapWidth  = (float)world.width;
                float mapHeight = (float)world.height;

                quad[0].texCoords = { (float)x / mapWidth, (float)y / mapHeight };
                quad[1].texCoords = { (float)(x+1) / mapWidth, (float)y / mapHeight };
                quad[2].texCoords = { (float)(x+1) / mapWidth, (float)(y+1) / mapHeight };

                quad[3].texCoords = { (float)x / mapWidth, (float)y / mapHeight };
                quad[4].texCoords = { (float)(x+1) / mapWidth, (float)(y+1) / mapHeight };
                quad[5].texCoords = { (float)x / mapWidth, (float)(y+1) / mapHeight };

                v += 6;
            }
        }
            
        sf::Image mapImage({(unsigned)world.width, (unsigned)world.height}, sf::Color::Black);

        for(int y = 0; y < world.height; y++)
        {
            for(int x = 0; x < world.width; x++)
            {
                auto& tile = world.get(x,y);

                mapImage.setPixel({(unsigned)x,(unsigned)y}, sf::Color(tile.terrain,0,0));
            }
        }

        tilemap.mapDataTexture.loadFromImage(mapImage);
        tilemap.mapDataTexture.setSmooth(false);
        tilemap.mapDataTexture.setRepeated(false);

        }
        
    }