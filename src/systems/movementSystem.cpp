#pragma once

#include "movementSystem.h"
#include "../components/components.h"

void MovementSystem::update(entt::registry& registry, SoundManager& sound_, float dt)
{
    auto view = registry.view<TransformComponent, SoundComponent>();
    
    for (auto [entity, transform, sound] : view.each()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
            transform.position.y -= 200 * dt;
            //sound_.play(sound.soundKey, sound.volume, sound.pitch);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            transform.position.y += 200 * dt;
            //sound_.play(sound.soundKey, sound.volume, sound.pitch);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            transform.position.x -= 200 * dt;
            //sound_.play(sound.soundKey, sound.volume, sound.pitch);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            transform.position.x += 200 * dt;
            //sound_.play(sound.soundKey, sound.volume, sound.pitch);
        }
    }
}