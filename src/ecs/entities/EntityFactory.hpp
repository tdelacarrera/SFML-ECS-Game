#pragma once
#include <entt/entt.hpp>

class EntityFactory
{
public:
    static entt::entity createPawn(entt::registry &registry, float x, float y);
    static entt::entity createTree(entt::registry &registry, float x, float y);
    static entt::entity createPlant(entt::registry &registry, float x, float y);
    static entt::entity createStone(entt::registry &registry, float x, float y);
    static entt::entity createAnimal(entt::registry &registry, float x, float y);
};