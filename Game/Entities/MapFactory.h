#pragma once

#include <entt/entt.hpp>
#include "Components/Components.h"
#include "World/WorldMap.h"

namespace EntityFactory
{

    inline entt::entity createTileMap(entt::registry& registry, const sf::Texture& texture)
    {
        auto& world = registry.ctx().get<WorldMap>();
        auto entity = registry.create();
        auto& tilemap = registry.emplace<TileMapComponent>(entity);
        tilemap.texture = &texture;
        tilemap.tilesetWidth = texture.getSize().x / world.tileSize;

        return entity;
    }

}




