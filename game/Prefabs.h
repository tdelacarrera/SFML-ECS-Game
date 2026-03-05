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
    registry.emplace<PlayerComponent>(entity);

    return entity;
}

inline entt::entity createColonist(entt::registry& registry)
{
    entt::entity entity = registry.create();
    registry.emplace<TransformComponent>(entity,sf::Vector2f{50.f, 50.f},  sf::Vector2f{1.f, 1.f},  0.f);
    registry.emplace<SpriteComponent>(entity, "colonist");

    return entity;
}

inline entt::entity createTileMap(entt::registry& registry, const sf::Texture& texture)
    {
        auto entity = registry.create();

        TileMapComponent tilemap;
        tilemap.texture = texture;
        tilemap.tileSize = 16;
        tilemap.width = 255;
        tilemap.height = 255;
        tilemap.vertices = sf::VertexArray(sf::PrimitiveType::Triangles);
        tilemap.tiles.resize(tilemap.width*tilemap.height);

        for (unsigned int j = 0; j < tilemap.height; ++j) {
            for (unsigned int i = 0; i < tilemap.width; ++i) {
                if ((i + j) % 2 == 0)
                    tilemap.tiles[i + j * tilemap.width] = 0;
                else
                    tilemap.tiles[i + j * tilemap.width] = 1;
            }
        }

        buildTileMap(tilemap);

        registry.emplace<TileMapComponent>(entity, tilemap);

        return entity;
    }
}
