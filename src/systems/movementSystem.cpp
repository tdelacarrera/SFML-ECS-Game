#pragma once

#include "movementSystem.h"
#include "../components/components.h"

void MovementSystem::update(entt::registry& registry, float dt)
{
    auto view = registry.view<TransformComponent>();
    
    for (auto [entity, transform] : view.each()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
            transform.position.y -= 200 * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            transform.position.y += 200 * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            transform.position.x -= 200 * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            transform.position.x += 200 * dt;
        }
    }
}