#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../../Engine/Input/MouseManager.h"

inline void SelectionRenderSystem(entt::registry& registry)
{
    auto& window = registry.ctx().get<WindowResource>().window;
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