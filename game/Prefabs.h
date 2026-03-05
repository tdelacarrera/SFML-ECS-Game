#pragma once

#include <entt/entt.hpp>
#include "components/Components.h"
#include "TileMap.h"

namespace Prefabs
{

inline entt::entity createPlayer(entt::registry& registry)
{
    entt::entity entity = registry.create();
    registry.emplace<TransformComponent>(entity,sf::Vector2f{0.f, 0.f},  sf::Vector2f{1.f, 1.f},  0.f);
    registry.emplace<SpriteComponent>(entity, "colonist");

    return entity;
}

inline entt::entity createTileMap(entt::registry& registry,
    const sf::Texture& texture,
    const std::vector<int>& tiles,
    unsigned int width,
    unsigned int height,
    unsigned int tileSize = 16)
    {
        auto entity = registry.create();

        TileMapComponent tilemap;
        tilemap.texture = texture;
        tilemap.tileSize = tileSize;
        tilemap.vertices = sf::VertexArray(sf::PrimitiveType::Triangles);

        TileMapData data;
        data.tiles = tiles;
        data.width = width;
        data.height = height;

        buildTileMap(tilemap, data);

        registry.ctx().emplace<TileMapComponent>(tilemap);

        return entity;
    }
}
