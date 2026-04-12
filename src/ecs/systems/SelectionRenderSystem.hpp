#pragma once

#include <entt/entt.hpp>
#include <ecs/components/Components.hpp>
#include "world/WorldMap.hpp"
#include "core/input/MouseManager.hpp"

inline void selectionRenderSystem(entt::registry &registry, sf::RenderWindow &window, MouseManager &mouseManager)
{
    if (!mouseManager.isSelecting())
        return;

    sf::Vector2f start = mouseManager.getSelectionStart();
    sf::Vector2f end = mouseManager.getSelectionEnd();

    sf::Vector2f position(std::min(start.x, end.x), std::min(start.y, end.y));
    sf::Vector2f size(std::abs(end.x - start.x), std::abs(end.y - start.y));

    sf::RectangleShape rect;
    rect.setPosition(position);
    rect.setSize(size);
    rect.setFillColor(sf::Color(0, 255, 0, 40));
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(2.f);

    window.draw(rect);
}