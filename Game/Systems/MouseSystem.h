#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "../../Engine/Input/MouseManager.h"
#include "../../Engine/Resources.h"

inline void MouseSystem(entt::registry& registry)
{
    auto& mouse = registry.ctx().get<MouseManager>();
    auto& events = registry.ctx().get<EventResource>().events;
    auto& window = registry.ctx().get<WindowResource>().window;

    mouse.clearFrame();

    for(auto& event : events)
    {
        if(const auto* e = event.getIf<sf::Event::MouseMoved>())
        {
            mouse.setPosition({e->position.x, e->position.y});
        }

        if(const auto* e = event.getIf<sf::Event::MouseButtonPressed>())
        {
            mouse.setButton(e->button, true);
        }

        if(const auto* e = event.getIf<sf::Event::MouseButtonReleased>())
        {
            mouse.setButton(e->button, false);
        }

        if(const auto* e = event.getIf<sf::Event::MouseWheelScrolled>())
        {
            mouse.setWheel(e->delta);
        }
    }

    mouse.setPosition(sf::Mouse::getPosition(window));
}