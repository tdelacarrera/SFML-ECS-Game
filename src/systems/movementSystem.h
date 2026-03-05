#pragma once

#include <entt/entt.hpp>

struct MovementSystem {
    void update(entt::registry& registry, float dt);
};