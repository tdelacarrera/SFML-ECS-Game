#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

struct MovementSystem {
    void Update(entt::registry& registry, float dt);
};