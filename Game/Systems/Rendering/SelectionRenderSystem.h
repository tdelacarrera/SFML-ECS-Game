#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "Engine/Input/MouseManager.h"

inline void drawSelectionBracket(sf::RenderWindow& window, sf::Vector2f topLeft, float tileSize)
{
    float size = tileSize;
    float corner = 8.f;
    float thickness = 2.f;

    sf::Vector2f topRight = {topLeft.x + size, topLeft.y};
    sf::Vector2f bottomLeft = {topLeft.x, topLeft.y + size};
    sf::Vector2f bottomRight = {topLeft.x + size, topLeft.y + size};

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

inline void SelectionRenderSystem(entt::registry& registry)
{
    auto& world = registry.ctx().get<WorldMap>();
    auto& window = registry.ctx().get<WindowResource>().window;
    auto view = registry.view<TransformComponent, SelectedComponent>();

    //DEBUG
    //ELIMINAR
    auto view2 = registry.view<TransformComponent, ChopMarkedComponent>();

    for (auto entity : view2)
    {
        auto& t = view2.get<TransformComponent>(entity);

        sf::RectangleShape rect({world.tileSize,world.tileSize});
        rect.setPosition(t.position);

        rect.setFillColor(sf::Color(255, 0, 0, 100));

        window.draw(rect);
    }
    auto view3 = registry.view<TransformComponent, MineMarkedComponent>();

    for (auto entity : view3)
    {
        auto& t = view3.get<TransformComponent>(entity);

        sf::RectangleShape rect({world.tileSize, world.tileSize});
        rect.setPosition(t.position);

        rect.setFillColor(sf::Color(0, 0, 255, 100));

        window.draw(rect);
    }

    auto view4 = registry.view<TransformComponent, HarvestMarkedComponent>();

    for (auto entity : view4)
    {
        auto& t = view4.get<TransformComponent>(entity);

        sf::RectangleShape rect({world.tileSize, world.tileSize});
        rect.setPosition(t.position);

        rect.setFillColor(sf::Color(0, 255, 0, 100));

        window.draw(rect);
    }
    //ELIMINAR


    for(auto entity : view)
    {
        auto& transform = view.get<TransformComponent>(entity);

        drawSelectionBracket(window, transform.position, world.tileSize);
    }

    auto& mouse = registry.ctx().get<MouseManager>();

    if(!mouse.selecting())
        return;

    sf::Vector2f start = mouse.getStart();
    sf::Vector2f end = mouse.getEnd();

    // normalizar rectángulo
    sf::Vector2f position(
        std::min(start.x, end.x),
        std::min(start.y, end.y)
    );

    sf::Vector2f size(
        std::abs(end.x - start.x),
        std::abs(end.y - start.y)
    );

    sf::RectangleShape rect;

    rect.setPosition(position);
    rect.setSize(size);

    
    rect.setFillColor(sf::Color(0,255,0,40));
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(2);

    window.draw(rect);
}