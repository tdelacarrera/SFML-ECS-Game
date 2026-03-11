#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../Components/Components.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/MouseManager.h"

inline void CameraSystem(entt::registry& registry)
{
    auto& window = registry.ctx().get<WindowResource>().window;
    auto& deltaTime = registry.ctx().get<TimeResource>().deltaTime;
    auto& input = registry.ctx().get<InputManager>();
    auto& mouse = registry.ctx().get<MouseManager>();

    sf::View camera = window.getView();

    float speed = 600.f;
    float zoomSpeed = 1.5f;

    sf::Vector2f movement{0.f,0.f};


    // camera movement 
    if(input.pressed("move_up"))
        movement.y -= speed * deltaTime;

    if(input.pressed("move_down"))
        movement.y += speed * deltaTime;

    if(input.pressed("move_left"))
        movement.x -= speed * deltaTime;

    if(input.pressed("move_right"))
        movement.x += speed * deltaTime;

    camera.move(movement);

    //zoom with mouse wheel
    float wheel = mouse.getWheel();

    if(wheel != 0.f)
    {
        float zoomFactor = 1.f - wheel * 0.1f;
        camera.zoom(zoomFactor);
    }

    // zoom
    if(input.pressed("zoom_in"))
        camera.zoom(1.f + zoomSpeed * deltaTime);

    if(input.pressed("zoom_out"))
        camera.zoom(1.f - zoomSpeed * deltaTime);

    window.setView(camera);


    sf::Vector2f camCenter = camera.getCenter();
    sf::Listener::setPosition(sf::Vector3f(camCenter.x, camCenter.y, 0.f));
    sf::Listener::setDirection(sf::Vector3f(0.f, 1.f, 0.f));

}
