#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../components/Components.h"
#include "../../engine/Resources.h"
#include "../EntityFactory.h"

inline void AnimalMovementSystem(entt::registry& registry)
{
    auto& deltaTime = registry.ctx().get<TimeResource>().deltaTime;

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
        }

        transform.position += animal.direction * animal.speed * deltaTime;
    }
}