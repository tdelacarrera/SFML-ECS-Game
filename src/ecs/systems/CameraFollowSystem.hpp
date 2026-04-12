#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <ecs/components/Components.hpp>
#include "core/SceneManager.hpp"
#include "core/input/InputManager.hpp"
#include "core/input/MouseManager.hpp"
#include "world/Camera.hpp"
#include <iostream>

inline void cameraFollowSystem(entt::registry &registry, Camera &camera)
{
    auto view = registry.view<Position, Controllable>();

    for (auto entity : view)
    {
        auto &pos = view.get<Position>(entity);
        camera.setTarget(pos.value);
        break;
    }
}