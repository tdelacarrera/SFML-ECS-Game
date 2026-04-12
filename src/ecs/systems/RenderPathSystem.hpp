#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "ecs/components/Components.hpp"

inline void renderPathSystem(const entt::registry &registry, sf::RenderWindow &window)
{
    auto view = registry.view<Position, PathFollower, PathDebug>();

    for (auto entity : view)
    {
        const auto &debug = registry.get<PathDebug>(entity);
        const auto &follower = registry.get<PathFollower>(entity);

        if (!debug.showPath || follower.waypoints.empty())
            continue;

        const auto &path = follower.waypoints;

        sf::VertexArray line(sf::PrimitiveType::LineStrip, path.size());

        for (size_t i = 0; i < path.size(); ++i)
        {
            line[i].position = path[i];
            line[i].color = debug.color;
        }

        // fade último punto
        line[path.size() - 1].color.a = 160;

        window.draw(line);

        // Dibujar puntos
        sf::CircleShape dot(3.f);
        dot.setFillColor(sf::Color::Yellow);

        for (const auto &p : path)
        {
            dot.setPosition(p - sf::Vector2f(3.f, 3.f));
            window.draw(dot);
        }
    }
}