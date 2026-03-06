#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "../../engine/Resources.h"

void InputSystem(entt::registry& registry)
{
    auto& bindings = registry.ctx().get<InputBindings>();
    auto& input = registry.ctx().get<InputState>();

    for(auto& [action, key] : bindings.bindings)
    {
        bool pressed = sf::Keyboard::isKeyPressed(key);
        input.set(action, pressed);
    }
}