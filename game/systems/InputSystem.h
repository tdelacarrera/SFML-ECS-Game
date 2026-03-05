#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "../../engine/Resources.h"

void InputSystem(entt::registry& registry)
{
    auto &events = registry.ctx().get<EventResource>().events;

    for(const auto& event : events)
    {
        if(event.is<sf::Event::KeyPressed>())
        {
            auto key = event.getIf<sf::Event::KeyPressed>();

            if(key->code == sf::Keyboard::Key::Escape)
            {
                auto &window = registry.ctx().get<WindowResource>().window;
                window.close();
            }
        }
    }
}