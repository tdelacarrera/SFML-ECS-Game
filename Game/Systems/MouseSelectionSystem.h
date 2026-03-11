#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../../Engine/Input/MouseManager.h"
#include "../../Engine/Textures/TextureManager.h"

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
    }

    if(!mouse.isPressed(sf::Mouse::Button::Left) && mouse.selecting())
    {
        mouse.endSelection();
    }
}