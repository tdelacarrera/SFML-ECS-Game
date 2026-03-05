#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../components/Components.h"
#include "../../engine/Resources.h"

inline void CameraSystem(entt::registry& registry)
{
    auto &window = registry.ctx().get<WindowResource>().window;
    sf::View windowview = window.getDefaultView();

    auto view = registry.view<TransformComponent, PlayerComponent>();

    for (auto [entity, transform] : view.each()) 
    {
        windowview.setCenter(transform.position);
        window.setView(windowview);
    }
}