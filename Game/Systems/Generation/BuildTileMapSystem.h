#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "Components/Components.h"
#include "Engine/Resources.h"


inline bool isFilled(const WorldMap& world, int x, int y, int terrainType) {
    if (!world.inBounds(x, y)) return false;
    return world.get(x, y).terrain == terrainType;
}

inline int getBitmask(const WorldMap& world, int x, int y, int terrainType) {
    int mask = 0;
    if (isFilled(world, x, y + 1, terrainType)) mask |= 1; // S
    if (isFilled(world, x - 1, y, terrainType)) mask |= 2; // W
    if (isFilled(world, x, y - 1, terrainType)) mask |= 4; // N
    if (isFilled(world, x + 1, y, terrainType)) mask |= 8; // E
    return mask;
}

inline sf::Vector2i tileLookup[16] = {
    {0, 3}, {0, 0}, {3, 3}, {3, 0},
    {0, 2}, {0, 1}, {3, 2}, {3, 1},
    {1, 3}, {1, 0}, {2, 3}, {2, 0},
    {1, 2}, {1, 1}, {2, 2}, {2, 1}
};

inline void BuildTileMapSystem(entt::registry& registry)
{
    auto& world = registry.ctx().get<WorldMap>();
    auto view = registry.view<TileMapComponent>();

    for (auto entity : view)
    {
        auto& tilemap = view.get<TileMapComponent>(entity);
        tilemap.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        tilemap.vertices.resize(world.width * world.height * 6);

        int v = 0;
        for (int y = 0; y < world.height; y++)
        {
            for (int x = 0; x < world.width; x++)
            {
                auto& tile = world.get(x, y);
                
                int mask = getBitmask(world, x, y, tile.terrain);
                sf::Vector2i tuv = tileLookup[mask];

                int tilesPerRow = 4; // número de tiles horizontales en el tileset
                float tx = (tuv.x + tilesPerRow * tile.terrain) * world.tileSize;
                float ty = tuv.y * world.tileSize;
    
                float px = x * world.tileSize;
                float py = y * world.tileSize;

                sf::Vertex* quad = &tilemap.vertices[v];
                quad[0].position = {px, py};
                quad[1].position = {px + world.tileSize, py};
                quad[2].position = {px + world.tileSize, py + world.tileSize};
                quad[3].position = {px, py};
                quad[4].position = {px + world.tileSize, py + world.tileSize};
                quad[5].position = {px, py + world.tileSize};

                quad[0].texCoords = {tx, ty};
                quad[1].texCoords = {tx + world.tileSize, ty};
                quad[2].texCoords = {tx + world.tileSize, ty + world.tileSize};
                quad[3].texCoords = {tx, ty};
                quad[4].texCoords = {tx + world.tileSize, ty + world.tileSize};
                quad[5].texCoords = {tx, ty + world.tileSize};

                v += 6;
            }
        }
    }
}