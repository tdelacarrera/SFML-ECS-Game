#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "../Components/Components.h"


inline void CancelOrderSystem(entt::registry& registry)
{
    auto& tool = registry.ctx().get<ToolState>();
    auto& mouse = registry.ctx().get<MouseManager>();
    auto& window = registry.ctx().get<WindowResource>().window;

    // Solo funciona en modo cancelar
    if (tool.current != ToolMode::Cancel)
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


        //Mejorar
        auto view = registry.view<MineMarkedComponent, TransformComponent>();

        for (auto entity : view)
        {
            const auto& transform = view.get<TransformComponent>(entity);

            if (rect.contains(transform.position))
            {
                registry.remove<MineMarkedComponent>(entity);
            }
        }
        auto view2 = registry.view<ChopMarkedComponent, TransformComponent>();

        for (auto entity : view2)
        {
            const auto& transform = view2.get<TransformComponent>(entity);

            if (rect.contains(transform.position))
            {
                registry.remove<ChopMarkedComponent>(entity);
            }
        }
        auto view3 = registry.view<HarvestMarkedComponent, TransformComponent>();

        for (auto entity : view3)
        {
            const auto& transform = view2.get<TransformComponent>(entity);

            if (rect.contains(transform.position))
            {
                registry.remove<HarvestMarkedComponent>(entity);
            }
        }
    }
}