#pragma once

#include <entt/entt.hpp>
#include "../components/Components.h"

inline void MovementSystem(entt::registry& registry)
{
    auto& deltaTime = registry.ctx().get<TimeResource>().deltaTime;
    auto view = registry.view<TransformComponent, PlayerComponent>();
    auto& input = registry.ctx().get<InputState>();
    
    for (auto [entity, transform] : view.each()) {
        if(input.pressed("move_up"))
           transform.position.y -= 200 * deltaTime;

        if(input.pressed("move_down"))
           transform.position.y += 200 * deltaTime;

        if(input.pressed("move_left"))
           transform.position.x -= 200 * deltaTime;

        if(input.pressed("move_right"))
            transform.position.x += 200 * deltaTime;

        break;
    }
}