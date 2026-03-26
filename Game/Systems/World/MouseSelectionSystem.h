#pragma once

#include <algorithm>
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../../../Engine/Input/MouseManager.h"
#include "../../../Engine/Textures/TextureManager.h"

inline void MouseSelectionSystem(entt::registry& registry)
{
    auto& mouse = registry.ctx().get<MouseManager>();
    auto& window = registry.ctx().get<WindowResource>().window;

    sf::Vector2i mousePositon = mouse.getPosition();
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePositon);

    if(mouse.isPressed(sf::Mouse::Button::Left) && !mouse.selecting())
    {
        mouse.startSelection(worldPosition);
    }

    if(mouse.selecting())
    {
        
         mouse.updateSelection(worldPosition);

        //Logica para Seleccionar las entidades bajo el cuadro de seleccion
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


        //Logica para Seleccionar una sola entidad por click
        float dx = std::abs(end.x - start.x);
        float dy = std::abs(end.y - start.y);

        bool isClick = (dx < 5.f && dy < 5.f);


        if(isClick)
        {
            for(auto entity : view)
            {
                auto& transform = view.get<TransformComponent>(entity);

                //area del rectangulo de seleccion para el click
                float radius = 32.f;
                sf::FloatRect bounds({transform.position.x, transform.position.y}, {radius * 2, radius * 2});

                if(bounds.contains(end))
                {
                    registry.emplace_or_replace<SelectedComponent>(entity);
                    break;
                }
                else
                {
                    if(registry.all_of<SelectedComponent>(entity))
                    {
                        registry.remove<SelectedComponent>(entity);
                    }
                }
            }
        }

    }

    if(!mouse.isPressed(sf::Mouse::Button::Left) && mouse.selecting())
    {
        mouse.endSelection();
    }
}