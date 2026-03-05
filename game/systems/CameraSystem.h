#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../components/Components.h"
#include "../../engine/Resources.h"

inline void CameraSystem(entt::registry& registry)
{
    auto &window = registry.ctx().get<WindowResource>().window;
    auto &deltaTime = registry.ctx().get<TimeResource>().deltaTime;
    sf::View camera = window.getView(); 
    
    float cameraSmooth = 2;

    auto view = registry.view<TransformComponent, PlayerComponent>();

    for (auto [entity, transform] : view.each()) 
    {
        sf::Vector2f camPos = camera.getCenter();
        sf::Vector2f target = transform.position;

        sf::Vector2f newPos;
        newPos.x = camPos.x + (target.x - camPos.x) * cameraSmooth * deltaTime;
        newPos.y = camPos.y + (target.y - camPos.y) * cameraSmooth * deltaTime;
    
        camera.setCenter(newPos);
        window.setView(camera);

        break;
    }
}




