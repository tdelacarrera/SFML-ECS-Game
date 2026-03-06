#pragma once

#include <entt/entt.hpp>
#include "../components/Components.h"

inline void MovementSystem(entt::registry& registry)
{
    auto& deltaTime = registry.ctx().get<TimeResource>().deltaTime;
    auto view = registry.view<TransformComponent, PlayerComponent>();
    auto& input = registry.ctx().get<InputState>();
    
    for (auto [entity, transform] : view.each()) {
        if(input.isPressed(InputAction::MoveUp))
           transform.position.y -= 200 * deltaTime;

        if(input.isPressed(InputAction::MoveDown))
           transform.position.y += 200 * deltaTime;

        if(input.isPressed(InputAction::MoveLeft))
           transform.position.x -= 200 * deltaTime;

        if(input.isPressed(InputAction::MoveRight))
            transform.position.x += 200 * deltaTime;

        break;
    }
}