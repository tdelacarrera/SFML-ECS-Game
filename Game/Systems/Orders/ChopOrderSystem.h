#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "../../Components/Components.h"

inline void ChopOrderSystem(entt::registry& registry)
{
    auto& tool = registry.ctx().get<ToolState>();
    auto& mouse = registry.ctx().get<MouseManager>();
    auto& window = registry.ctx().get<WindowResource>().window;

    // Solo funciona en modo talar
    if (tool.current != ToolMode::Chop)
    {
        return;
    }

    // Posición mouse en mundo
    sf::Vector2i mousePositon = mouse.getPosition();
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePositon);

    // Iniciar selección
    if (mouse.isJustPressed(sf::Mouse::Button::Left))
    {
        mouse.startSelection(worldPosition);
    }

    // Hacer mientras se arrastra
    if (mouse.selecting())
    {
        mouse.updateSelection(worldPosition);

        sf::Vector2f start = mouse.getStart();
        sf::Vector2f end   = mouse.getEnd();

        // Normalizar rectángulo
        sf::Vector2f position(
            std::min(start.x, end.x),
            std::min(start.y, end.y)
        );

        sf::Vector2f size(
            std::abs(end.x - start.x),
            std::abs(end.y - start.y)
        );

        sf::FloatRect rect(position, size);

        // Marcar entidades dentro del area
        auto view = registry.view<TransformComponent, ChoppableComponent>();

        for (auto entity : view)
        {
            auto& t = view.get<TransformComponent>(entity);

            if (rect.contains(t.position))
            {
                registry.emplace_or_replace<ChopMarkedComponent>(entity);
            }
        }
    }

    // Terminar seleccion
    if (mouse.isJustReleased(sf::Mouse::Button::Right))
    {
        mouse.endSelection();
        tool.current = ToolMode::None;
    }
}