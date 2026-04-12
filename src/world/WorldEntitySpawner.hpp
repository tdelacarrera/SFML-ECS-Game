#pragma once
#include <entt/entt.hpp>
#include "world/WorldMap.hpp"

class WorldEntitySpawner
{
public:
    static void spawn(entt::registry &registry, const WorldMap &world);
};