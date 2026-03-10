#pragma once

#include <entt/entt.hpp>
#include "../Components/Components.h"
#include "../World/WorldMap.h"

namespace EntityFactory
{

    inline entt::entity createTileMap(entt::registry& registry, const sf::Texture& texture)
    {
        auto entity = registry.create();

        auto& world = registry.ctx().get<WorldMap>();

        auto& tilemap = registry.emplace<TileMapComponent>(entity);

        tilemap.texture = &texture;
        tilemap.tileSize = 64;

        tilemap.width = world.width;
        tilemap.height = world.height;

        tilemap.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

        return entity;
    }

}



