#pragma once

#include <entt/entt.hpp>
#include "../components/Components.h"

inline void MovementSystem(entt::registry& registry)
{
    auto& deltaTime = registry.ctx().get<TimeResource>().deltaTime;
    auto view = registry.view<TransformComponent>();
    
    for (auto [entity, transform] : view.each()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
            transform.position.y -= 200 * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            transform.position.y += 200 * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            transform.position.x -= 200 * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            transform.position.x += 200 * deltaTime;
        }
    }
}