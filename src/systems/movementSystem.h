#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../utils/soundManager.h"

struct MovementSystem {
    void update(entt::registry& registry, SoundManager& sound_, float dt);
};