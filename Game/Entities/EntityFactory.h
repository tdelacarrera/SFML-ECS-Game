#pragma once

#include <entt/entt.hpp>
#include "../Components/Components.h"

namespace EntityFactory
{

    inline entt::entity createTree(entt::registry& registry, float x, float y)
    {
        entt::entity entity = registry.create();
        registry.emplace<TransformComponent>(entity,sf::Vector2f{x, y},  sf::Vector2f{1.f, 1.f},  0.f);
        registry.emplace<SpriteComponent>(entity, "tree");

        return entity;
    }

    inline entt::entity createAnimal(entt::registry& registry, float x, float y)
    {
        entt::entity entity = registry.create();
        registry.emplace<TransformComponent>(entity,sf::Vector2f{x, y},  sf::Vector2f{1.f, 1.f},  0.f);
        registry.emplace<SpriteComponent>(entity, "animal");
        registry.emplace<AnimalComponent>( entity, sf::Vector2f{x,y}, 40.f,  0.f);

        return entity;
    }

    inline entt::entity createColonist(entt::registry& registry, float x, float y)
    {
        entt::entity entity = registry.create();
        registry.emplace<TransformComponent>(entity,sf::Vector2f{x, y},  sf::Vector2f{1.f, 1.f},  0.f);
        registry.emplace<SpriteComponent>(entity, "colonist");

        return entity;
    }

}



