#pragma once
#include <entt/entt.hpp>
#include "world/Pathfinding.hpp"
#include "world/Camera.hpp"
#include "core/input/MouseManager.hpp"
#include "ecs/components/Components.hpp"

inline void pathfindingSystem(entt::registry &registry,
                              const WorldMap &world,
                              const sf::RenderWindow &window,
                              const Camera &camera,
                              MouseManager &mouseManager)
{
    if (!mouseManager.isJustPressed(sf::Mouse::Button::Right))
        return;

    // Convertir posición del ratón a coordenadas del mundo
    sf::Vector2i mouseScreen = mouseManager.getPosition();
    sf::Vector2f mouseWorld = window.mapPixelToCoords(mouseScreen, camera.getView());

    // Procesar solo entidades que tienen PathFollower + Position
    auto view = registry.view<Position, PathFollower>();

    for (auto entity : view)
    {
        const auto &pos = registry.get<Position>(entity).value;

        auto path = findPath(world, pos, mouseWorld);

        if (!path.empty())
        {
            auto &follower = registry.get<PathFollower>(entity);
            follower.waypoints = std::move(path);
            follower.currentIndex = 0;
        }
    }
}