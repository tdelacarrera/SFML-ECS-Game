#pragma once

#include <algorithm>
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../../Engine/Input/MouseManager.h"
#include "../../Engine/Textures/TextureManager.h"
#include <iostream>

inline void MouseSelectionSystem(entt::registry& registry)
{
    auto& mouse = registry.ctx().get<MouseManager>();
    auto& window = registry.ctx().get<WindowResource>().window;

    sf::Vector2i pixel = mouse.getPosition();
    sf::Vector2f world = window.mapPixelToCoords(pixel);

    if(mouse.isPressed(sf::Mouse::Button::Left) && !mouse.selecting())
    {
        mouse.startSelection(world);
    }

    if(mouse.selecting())
    {
         mouse.updateSelection(world);

        sf::Vector2f start = mouse.getStart();
        sf::Vector2f end = mouse.getEnd();

        sf::FloatRect selectionRect({std::min(start.x, end.x),std::min(start.y, end.y)},{std::abs(end.x - start.x),std::abs(end.y - start.y)});

        auto view = registry.view<TransformComponent, SelectableComponent>();


        for(auto entity : view)
        {
            auto& transform = view.get<TransformComponent>(entity);

            if(selectionRect.contains(transform.position))
            {
                registry.emplace_or_replace<SelectedComponent>(entity);
            }
            //Actualizar eliminando las entidades seleccionadas al cambiar  el tamaño del cuadro de seleccion
            else
            {
                if(registry.all_of<SelectedComponent>(entity))
                {
                    registry.remove<SelectedComponent>(entity);
                }
            }
        }

    }

    if(!mouse.isPressed(sf::Mouse::Button::Left) && mouse.selecting())
    {
        mouse.endSelection();
    }
}