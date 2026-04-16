#pragma once

#include <entt/entt.hpp>
#include <ecs/components/Components.hpp>
#include "world/WorldMap.hpp"
#include "world/TileMap.hpp"
#include "world/Camera.hpp"
#include "core/input/MouseManager.hpp"
#include "ui/Tools.hpp"

void tilePaintSystem(entt::registry &registry, WorldMap &world, TileMap &tilemap, sf::RenderWindow &window, Camera &camera, MouseManager &mouseManager)
{
    auto &tool = registry.ctx().get<ToolState>();

    if (tool.current != ToolMode::PaintTile)
    {
        return;
    }

    if (mouseManager.isJustPressed(sf::Mouse::Button::Right))
    {
        auto &tool = registry.ctx().get<ToolState>();
        tool.current = ToolMode::None;
        mouseManager.endSelection(); // terminar la seleccion para que no aparezca el cuadro de seleccion al abandonar el modo de editar tiles
    }

    if (!mouseManager.isPressed(sf::Mouse::Button::Left))
    {
        return;
    }

    sf::Vector2i pixel = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixel, camera.getView());

    int tileSize = world.getTileSize();
    int tx = static_cast<int>(std::round(worldPos.x / tileSize));
    int ty = static_cast<int>(std::round(worldPos.y / tileSize));

    if (!world.inBounds(tx, ty))
        return;

    auto &tile = world.at(tx, ty);
    tile.terrain = tool.selectedTile;

    tilemap.updateTile(tx, ty, tool.selectedTile); // Actualizar visualmente el tile
    world.setTile(tx, ty, tool.selectedTile);      // Actualizar costo y si es caminable o no
}