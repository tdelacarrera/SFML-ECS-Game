#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../utils/audioManager.h"

struct MovementSystem {
    void update(entt::registry& registry, AudioManager& sounds_, float dt);
};