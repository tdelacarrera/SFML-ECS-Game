#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "../../engine/Input/InputManager.h"

inline void InputSystem(entt::registry& registry)
{
    auto& input = registry.ctx().get<InputManager>();

    input.nextFrame();
    input.update();
}