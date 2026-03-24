#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/MouseManager.h"

inline void InputSystem(entt::registry& registry)
{
    auto& input = registry.ctx().get<InputManager>();
    auto& mouse = registry.ctx().get<MouseManager>();

    input.nextFrame();
    input.update();
    mouse.update();
    mouse.clearFrame();
}