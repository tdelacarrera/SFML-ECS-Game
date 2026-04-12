#pragma once

#include <entt/entt.hpp>
#include <ecs/components/Components.hpp>
#include "world/WorldMap.hpp"
#include "core/input/MouseManager.hpp"
#include "core/textures/TextureManager.hpp"
#include <algorithm>

inline void renderSelectionBrackets(entt::registry &registry, sf::RenderWindow &window, WorldMap &world, TextureManager &textureManager)
{
    auto view = registry.view<Position, Selected, Texture>();

    for (auto entity : view)
    {
        auto &position = view.get<Position>(entity);
        auto &texture = view.get<Texture>(entity);

        sf::Texture &tex = textureManager.get(texture.textureId);

        sf::Sprite sprite(tex);
        sprite.setPosition(position.value);

        sf::FloatRect bounds = sprite.getGlobalBounds();

        float thickness = 2.f;

        float corner = std::min(bounds.size.x, bounds.size.y) * 0.25f;
        corner = std::clamp(corner, 6.f, 20.f);

        sf::Vector2f topLeft(bounds.position.x, bounds.position.y);
        sf::Vector2f topRight(bounds.position.x + bounds.size.x, bounds.position.y);
        sf::Vector2f bottomLeft(bounds.position.x, bounds.position.y + bounds.size.y);
        sf::Vector2f bottomRight(bounds.position.x + bounds.size.x, bounds.position.y + bounds.size.y);

        sf::Color color = sf::Color::Yellow;

        auto makeLine = [&](sf::Vector2f pos, sf::Vector2f size)
        {
            sf::RectangleShape line(size);
            line.setPosition(pos);
            line.setFillColor(color);
            window.draw(line);
        };

        // TOP LEFT
        makeLine(topLeft, {corner, thickness});
        makeLine(topLeft, {thickness, corner});

        // TOP RIGHT
        makeLine({topRight.x - corner, topRight.y}, {corner, thickness});
        makeLine({topRight.x - thickness, topRight.y}, {thickness, corner});

        // BOTTOM LEFT
        makeLine({bottomLeft.x, bottomLeft.y - thickness}, {corner, thickness});
        makeLine({bottomLeft.x, bottomLeft.y - corner}, {thickness, corner});

        // BOTTOM RIGHT
        makeLine({bottomRight.x - corner, bottomRight.y - thickness}, {corner, thickness});
        makeLine({bottomRight.x - thickness, bottomRight.y - corner}, {thickness, corner});
    }

    auto view3 = registry.view<Position, MarkedForChopping>();
    for (auto entity : view3)
    {
        auto &pos = view3.get<Position>(entity);

        sf::RectangleShape rect({world.getTileSize(), world.getTileSize()});
        rect.setPosition(pos.value);
        rect.setFillColor(sf::Color::Yellow);
        window.draw(rect);
    }
    auto view4 = registry.view<Position, MarkedForHarvest>();
    for (auto entity : view4)
    {
        auto &pos = view4.get<Position>(entity);

        sf::RectangleShape rect({world.getTileSize(), world.getTileSize()});
        rect.setPosition(pos.value);
        rect.setFillColor(sf::Color::Green);
        window.draw(rect);
    }
    auto view5 = registry.view<Position, MarkedForMining>();
    for (auto entity : view5)
    {
        auto &pos = view5.get<Position>(entity);

        sf::RectangleShape rect({world.getTileSize(), world.getTileSize()});
        rect.setPosition(pos.value);
        rect.setFillColor(sf::Color::Blue);
        window.draw(rect);
    }
}