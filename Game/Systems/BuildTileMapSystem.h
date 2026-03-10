#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../Components/Components.h"
#include "../../Engine/Resources.h"

inline void BuildTileMapSystem(entt::registry& registry)
{
    auto& world = registry.ctx().get<WorldMap>();

    auto view = registry.view<TileMapComponent>();

    for(auto entity : view)
    {
        auto& tilemap = view.get<TileMapComponent>(entity);

        tilemap.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        tilemap.vertices.resize(world.width * world.height * 6);

        int tilesetWidth = tilemap.texture->getSize().x / tilemap.tileSize;

        int v = 0;

        for(int y=0; y<world.height; y++)
        {
            for(int x=0; x<world.width; x++)
            {
                auto& tile = world.get(x,y);

                int tileNumber = tile.terrain;

                int tu = tileNumber % tilesetWidth;
                int tv = tileNumber / tilesetWidth;

                float px = x * tilemap.tileSize;
                float py = y * tilemap.tileSize;

                float tx = tu * tilemap.tileSize;
                float ty = tv * tilemap.tileSize;

                sf::Vertex* quad = &tilemap.vertices[v];

                quad[0].position = {px, py};
                quad[1].position = {px + tilemap.tileSize, py};
                quad[2].position = {px + tilemap.tileSize, py + tilemap.tileSize};

                quad[3].position = {px, py};
                quad[4].position = {px + tilemap.tileSize, py + tilemap.tileSize};
                quad[5].position = {px, py + tilemap.tileSize};

                quad[0].texCoords = {tx, ty};
                quad[1].texCoords = {tx + tilemap.tileSize, ty};
                quad[2].texCoords = {tx + tilemap.tileSize, ty + tilemap.tileSize};

                quad[3].texCoords = {tx, ty};
                quad[4].texCoords = {tx + tilemap.tileSize, ty + tilemap.tileSize};
                quad[5].texCoords = {tx, ty + tilemap.tileSize};

                v += 6;
            }
        }
    }
}