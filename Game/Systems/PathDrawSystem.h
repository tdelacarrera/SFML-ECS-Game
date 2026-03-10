#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "../Components/Components.h"

inline void PathDrawSystem(entt::registry& registry)
{
    int tileSize = 64;
    auto &window = registry.ctx().get<WindowResource>().window;
    auto& tiles = registry.ctx().get<WorldMap>().tiles;

    auto view = registry.view<PathComponent>();

    for(auto entity : view)
    {
        auto& path = view.get<PathComponent>(entity);
        if(path.path.empty()) continue;

       /* sf::VertexArray lines(sf::PrimitiveType::Lines, path.path.size());
        for(size_t i = 0; i < path.path.size(); ++i)
        {
            lines[i].position = sf::Vector2f(
                path.path[i].x * tileSize + tileSize*0.5f,
                path.path[i].y * tileSize + tileSize*0.5f
            );
            lines[i].color = sf::Color::Red;
        }
        window.draw(lines);
            */

        sf::RectangleShape rect(sf::Vector2f(tileSize, tileSize));
        rect.setFillColor(sf::Color(255, 0, 0, 80)); // rojo semitransparente
        for(auto& tile : path.path)
        {
            rect.setPosition({tile.x * tileSize, tile.y * tileSize});
            window.draw(rect);
        }
    }
}