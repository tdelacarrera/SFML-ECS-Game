#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "Components/Components.h"
#include "Entities/Entities.h"
#include "Pathfinding/Pathfinding.h"
#include "Engine/Input/MouseManager.h"
#include "Engine/Resources.h"

inline void SetColonistPathSystem(entt::registry& registry)
{
    auto& pathfinding = registry.ctx().get<Pathfinding>();
    auto& mouse = registry.ctx().get<MouseManager>();
    auto& window = registry.ctx().get<WindowResource>().window;
    auto& world = registry.ctx().get<WorldMap>();
    int tileSize = world.tileSize;

    sf::Vector2i mousePositon = mouse.getPosition();
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePositon);

    auto view = registry.view<ColonistComponent, SelectedComponent>();

    for (auto entity : view)
    {
        if(mouse.isJustPressed(sf::Mouse::Button::Right))
        {
            sf::Vector2i tilePos;
            tilePos.x = static_cast<int>(worldPosition.x) / tileSize;
            tilePos.y = static_cast<int>(worldPosition.y) / tileSize;

            pathfinding.setDestination(registry, entity, {tilePos.x, tilePos.y});
        }
        
    }
}

