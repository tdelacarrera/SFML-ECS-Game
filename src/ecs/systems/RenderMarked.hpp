#pragma once

#include <entt/entt.hpp>
#include <ecs/components/Components.hpp>
#include "world/WorldMap.hpp"
#include "core/input/MouseManager.hpp"
#include "core/textures/TextureManager.hpp"
#include <algorithm>

inline void renderMarked(entt::registry &registry, sf::RenderWindow &window, WorldMap &world)
{

    auto view1 = registry.view<Position, MarkedForChopping>();
    for (auto entity : view1)
    {
        auto &position = view1.get<Position>(entity);

        sf::RectangleShape rect(sf::Vector2f(static_cast<float>(world.getTileSize()), static_cast<float>(world.getTileSize())));
        rect.setPosition(position.value);
        rect.setFillColor(sf::Color::Yellow);
        window.draw(rect);
    }

    auto view2 = registry.view<Position, MarkedForHarvest>();
    for (auto entity : view2)
    {
        auto &position = view2.get<Position>(entity);

        sf::RectangleShape rect(sf::Vector2f(static_cast<float>(world.getTileSize()), static_cast<float>(world.getTileSize())));
        rect.setPosition(position.value);
        rect.setFillColor(sf::Color::Green);
        window.draw(rect);
    }

    auto view3 = registry.view<Position, MarkedForMining>();
    for (auto entity : view3)
    {
        auto &position = view3.get<Position>(entity);

        sf::RectangleShape rect(sf::Vector2f(static_cast<float>(world.getTileSize()), static_cast<float>(world.getTileSize())));
        rect.setPosition(position.value);
        rect.setFillColor(sf::Color::Blue);
        window.draw(rect);
    }
}