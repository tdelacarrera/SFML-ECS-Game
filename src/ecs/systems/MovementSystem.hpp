#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <ecs/components/Components.hpp>
#include "core/SceneManager.hpp"
#include "core/input/InputManager.hpp"
#include "core/input/MouseManager.hpp"
#include <iostream>

inline void movementSystem(entt::registry &registry, float dt, MouseManager &mouseManager)
{

    auto view = registry.view<Position, PathFollower>();

    for (auto entity : view)
    {
        auto &pos = registry.get<Position>(entity);
        auto &path = registry.get<PathFollower>(entity);

        // Si hay un camino seguirlo
        if (!path.waypoints.empty() && path.currentIndex < path.waypoints.size())
        {
            sf::Vector2f target = path.waypoints[path.currentIndex];
            sf::Vector2f dir = target - pos.value;
            float distance = std::hypot(dir.x, dir.y);

            if (distance < path.arrivalDistance)
            {
                ++path.currentIndex;
                if (path.currentIndex >= path.waypoints.size())
                {
                    path.waypoints.clear();
                    path.currentIndex = 0;
                    continue;
                }
                target = path.waypoints[path.currentIndex];
                dir = target - pos.value;
                distance = std::hypot(dir.x, dir.y);
            }

            if (distance > 0.0f)
            {
                dir /= distance;
                pos.value += dir * path.speed * dt;
            }
            continue;
        }
    }
}