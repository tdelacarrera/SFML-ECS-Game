#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "../../Components/Components.h"

inline void PathDrawSystem(entt::registry& registry)
{
    //TODO: REMOVE HARCODED VALUE
    int tileSize = 64;
    auto &window = registry.ctx().get<WindowResource>().window;
    auto& tiles = registry.ctx().get<WorldMap>().tiles;

    auto view = registry.view<PathComponent>();

    for(auto entity : view)
    {
        auto& path = view.get<PathComponent>(entity);
        if(path.path.empty()) continue;

        sf::RectangleShape rect(sf::Vector2f(tileSize, tileSize));
        rect.setFillColor(sf::Color(255, 0, 0, 80));
        for(auto& tile : path.path)
        {
            rect.setPosition({tile.x * tileSize, tile.y * tileSize});
            rect.setOrigin({tile.x * 0.5f, tile.y * 0.5f});
            window.draw(rect);
        }
    }
}