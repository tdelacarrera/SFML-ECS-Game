#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "Components/Components.h"

inline void PathDrawSystem(entt::registry& registry)
{
    auto &window = registry.ctx().get<WindowResource>().window;
    auto& tiles = registry.ctx().get<WorldMap>().tiles;
    auto& world = registry.ctx().get<WorldMap>();
    int tileSize = world.tileSize;

    auto view = registry.view<PathComponent>();

    for(auto entity : view)
    {
        auto& path = view.get<PathComponent>(entity);
        if(path.path.empty()) continue;

        sf::RectangleShape rect(sf::Vector2f(tileSize, tileSize));
        for(auto& tile : path.path)
        {
            rect.setFillColor(sf::Color(255, 0, 0, 80));
            rect.setPosition({tile.x * tileSize, tile.y * tileSize});
            rect.setOrigin({tile.x * 0.5f, tile.y * 0.5f});
            window.draw(rect);
        }
    }
}