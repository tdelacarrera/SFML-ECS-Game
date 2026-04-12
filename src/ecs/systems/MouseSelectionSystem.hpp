#pragma once
#include <algorithm>
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "core/input/MouseManager.hpp"
#include <ecs/components/Components.hpp>

inline void mouseSelectionSystem(entt::registry &registry, const sf::RenderWindow &window, const Camera &camera, MouseManager &mouseManager)
{
    sf::Vector2i mousePixel = mouseManager.getPosition();
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePixel, camera.getView());

    // iniciar seleccion
    if (mouseManager.isJustPressed(sf::Mouse::Button::Left))
    {
        mouseManager.startSelection(worldPosition);
    }

    if (mouseManager.isSelecting())
    {
        mouseManager.updateSelection(worldPosition);

        // Solo procesar selección mientras se está arrastrando
        sf::Vector2f start = mouseManager.getSelectionStart();
        sf::Vector2f end = mouseManager.getSelectionEnd();

        sf::Vector2f position(std::min(start.x, end.x), std::min(start.y, end.y));
        sf::Vector2f size(std::abs(end.x - start.x), std::abs(end.y - start.y));

        sf::FloatRect selectionRect(position, size);

        // Marcar entidades dentro del rectángulo
        auto view = registry.view<Position, Selectable>();
        for (auto entity : view)
        {
            const auto &pos = view.get<Position>(entity);

            if (selectionRect.contains(pos.value))
            {
                registry.emplace_or_replace<Selected>(entity);
            }
            else
            {
                registry.remove<Selected>(entity);
            }
        }

        // Logica para Seleccionar una sola entidad por click
        float dx = std::abs(end.x - start.x);
        float dy = std::abs(end.y - start.y);

        bool isClick = (dx < 5.f && dy < 5.f);

        if (isClick)
        {
            for (auto entity : view)
            {
                auto &position = view.get<Position>(entity);

                // area del rectangulo de seleccion para el click
                float radius = 48.f;
                sf::FloatRect bounds({position.value.x, position.value.y}, {radius * 2, radius * 2});

                if (bounds.contains(end))
                {
                    registry.emplace_or_replace<Selected>(entity);
                    break;
                }
                else
                {
                    if (registry.all_of<Selected>(entity))
                    {
                        registry.remove<Selected>(entity);
                    }
                }
            }
        }
    }

    if (mouseManager.isJustReleased(sf::Mouse::Button::Left))
    {
        mouseManager.endSelection();
    }
}