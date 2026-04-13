#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "ecs/components/Components.hpp"

inline void renderPathSystem(const entt::registry &registry, sf::RenderWindow &window)
{
    auto view = registry.view<Position, PathFollower, PathDebug, Selected>();

    for (auto entity : view)
    {
        const auto &debug = registry.get<PathDebug>(entity);
        const auto &follower = registry.get<PathFollower>(entity);

        if (!debug.showPath || follower.waypoints.empty())
            continue;

        size_t start = follower.currentIndex;
        if (start >= follower.waypoints.size())
            continue;

        const auto &path = follower.waypoints;

        sf::VertexArray line(sf::PrimitiveType::LineStrip, path.size() - start);

        for (size_t i = start; i < path.size(); ++i)
        {
            sf::Vertex v;
            v.position = path[i];
            v.color = debug.color;

            line[i - start] = v;
        }

        window.draw(line);

        sf::CircleShape dot(3.f);
        dot.setFillColor(sf::Color::Yellow);

        for (size_t i = start; i < path.size(); ++i)
        {
            dot.setPosition(path[i] - sf::Vector2f(3.f, 3.f));
            window.draw(dot);
        }
    }
}