#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "../../engine/Resources.h"

inline void InputSystem(entt::registry& registry)
{
    auto &window = registry.ctx().get<WindowResource>().window;

    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
            window.close();
    }
}