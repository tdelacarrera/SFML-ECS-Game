#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../Components/Components.h"
#include "../../Engine/Resources.h"
#include "../EntityFactory.h"
#include "../../Engine/Audio/SoundManager.h"

inline void AnimalMovementSystem(entt::registry& registry)
{
    auto& deltaTime = registry.ctx().get<TimeResource>().deltaTime;
    auto& sound = registry.ctx().get<SoundManager>();
    
    auto view = registry.view<TransformComponent, AnimalComponent>();

    for(auto [entity, transform, animal] : view.each())
    {
        animal.changeDirectionTimer -= deltaTime;

        if(animal.changeDirectionTimer <= 0.f)
        {
            float angle = (rand() % 360) * 3.14159f / 180.f;

            animal.direction =
            {
                std::cos(angle),
                std::sin(angle)
            };

            animal.changeDirectionTimer = 2.f + (rand() % 3);
            sound.play("cat", 100.f, 1.f, transform.position, 400.f);
        }

        transform.position += animal.direction * animal.speed * deltaTime;
    }
}