#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../components/Components.hpp"
#include "core/input/MouseManager.hpp"
#include "world/Camera.hpp"

enum class ToolMode
{
    None,
    Mine,
    Chop,
    Harvest,
    Cancel
};

struct ToolState
{
    ToolMode current = ToolMode::None;
};

inline void toolApplicationSystem(entt::registry &registry, entt::entity entity)
{

    auto &toolState = registry.ctx().get<ToolState>();

    switch (toolState.current)
    {
    case ToolMode::Mine:
        if (registry.all_of<Minable>(entity))
            registry.emplace_or_replace<MarkedForMining>(entity);
        break;

    case ToolMode::Chop:
        if (registry.all_of<Choppable>(entity))
            registry.emplace_or_replace<MarkedForChopping>(entity);
        break;

    case ToolMode::Harvest:
        if (registry.all_of<Harvestable>(entity))
            registry.emplace_or_replace<MarkedForHarvest>(entity);
        break;

    case ToolMode::Cancel:
        registry.remove<MarkedForMining>(entity);
        registry.remove<MarkedForChopping>(entity);
        registry.remove<MarkedForHarvest>(entity);
        break;

    default:
        break;
    }
}

inline void ChopOrderSystem(entt::registry &registry, sf::RenderWindow &window, Camera &camera, MouseManager mouseManager)
{
    auto &tool = registry.ctx().get<ToolState>();

    // Solo funciona en modo talar
    if (tool.current != ToolMode::Chop)
    {
        return;
    }

    // Posición mouse en mundo
    sf::Vector2i mousePositon = mouseManager.getPosition();
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePositon, camera.getView());

    // Iniciar selección
    if (mouseManager.isJustPressed(sf::Mouse::Button::Left))
    {
        mouseManager.startSelection(worldPosition);
    }

    // Hacer mientras se arrastra
    if (mouseManager.isSelecting())
    {
        mouseManager.updateSelection(worldPosition);

        sf::Vector2f start = mouseManager.getSelectionStart();
        sf::Vector2f end = mouseManager.getSelectionEnd();

        // Normalizar rectángulo
        sf::Vector2f position(
            std::min(start.x, end.x),
            std::min(start.y, end.y));

        sf::Vector2f size(
            std::abs(end.x - start.x),
            std::abs(end.y - start.y));

        sf::FloatRect rect(position, size);

        // Marcar entidades dentro del area
        auto view = registry.view<Position, Choppable>();

        for (auto entity : view)
        {
            auto &position = view.get<Position>(entity);

            if (rect.contains(position.value))
            {
                registry.emplace_or_replace<MarkedForChopping>(entity);
            }
        }
    }

    // Terminar seleccion
    if (mouseManager.isJustReleased(sf::Mouse::Button::Right))
    {
        mouseManager.endSelection();
        tool.current = ToolMode::None;
    }
}

inline void MineOrderSystem(entt::registry &registry, sf::RenderWindow &window, Camera &camera, MouseManager mouseManager)
{
    auto &tool = registry.ctx().get<ToolState>();

    // Solo funciona en modo minar
    if (tool.current != ToolMode::Mine)
    {
        return;
    }

    // Posición mouse en mundo
    sf::Vector2i mousePositon = mouseManager.getPosition();
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePositon, camera.getView());

    // Iniciar selección
    if (mouseManager.isJustPressed(sf::Mouse::Button::Left))
    {
        mouseManager.startSelection(worldPosition);
    }

    // Hacer mientras se arrastra
    if (mouseManager.isSelecting())
    {
        mouseManager.updateSelection(worldPosition);

        sf::Vector2f start = mouseManager.getSelectionStart();
        sf::Vector2f end = mouseManager.getSelectionEnd();

        // Normalizar rectángulo
        sf::Vector2f position(
            std::min(start.x, end.x),
            std::min(start.y, end.y));

        sf::Vector2f size(
            std::abs(end.x - start.x),
            std::abs(end.y - start.y));

        sf::FloatRect rect(position, size);

        // Marcar entidades dentro del area
        auto view = registry.view<Position, Minable>();

        for (auto entity : view)
        {
            auto &position = view.get<Position>(entity);

            if (rect.contains(position.value))
            {
                registry.emplace_or_replace<MarkedForMining>(entity);
            }
        }
    }

    // Terminar seleccion
    if (mouseManager.isJustReleased(sf::Mouse::Button::Right))
    {
        mouseManager.endSelection();
        tool.current = ToolMode::None;
    }
}

inline void HarvestOrderSystem(entt::registry &registry, sf::RenderWindow &window, Camera &camera, MouseManager mouseManager)
{
    auto &tool = registry.ctx().get<ToolState>();

    // Solo funciona en modo cosechar
    if (tool.current != ToolMode::Harvest)
    {
        return;
    }

    // Posición mouse en mundo
    sf::Vector2i mousePositon = mouseManager.getPosition();
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePositon, camera.getView());

    // Iniciar selección
    if (mouseManager.isJustPressed(sf::Mouse::Button::Left))
    {
        mouseManager.startSelection(worldPosition);
    }

    // Hacer mientras se arrastra
    if (mouseManager.isSelecting())
    {
        mouseManager.updateSelection(worldPosition);

        sf::Vector2f start = mouseManager.getSelectionStart();
        sf::Vector2f end = mouseManager.getSelectionEnd();

        // Normalizar rectángulo
        sf::Vector2f position(
            std::min(start.x, end.x),
            std::min(start.y, end.y));

        sf::Vector2f size(
            std::abs(end.x - start.x),
            std::abs(end.y - start.y));

        sf::FloatRect rect(position, size);

        // Marcar entidades dentro del area
        auto view = registry.view<Position, Harvestable>();

        for (auto entity : view)
        {
            auto &position = view.get<Position>(entity);

            if (rect.contains(position.value))
            {
                registry.emplace_or_replace<MarkedForHarvest>(entity);
            }
        }
    }

    // Terminar seleccion
    if (mouseManager.isJustReleased(sf::Mouse::Button::Right))
    {
        mouseManager.endSelection();
        tool.current = ToolMode::None;
    }
}

inline void CancelOrderSystem(entt::registry &registry, sf::RenderWindow &window, Camera &camera, MouseManager &mouseManager)
{
    auto &tool = registry.ctx().get<ToolState>();

    // Solo funciona en modo cancelar
    if (tool.current != ToolMode::Cancel)
    {
        return;
    }

    // Posición mouse en mundo
    sf::Vector2i mousePositon = mouseManager.getPosition();
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePositon, camera.getView());

    // Iniciar selección
    if (mouseManager.isJustPressed(sf::Mouse::Button::Left))
    {
        mouseManager.startSelection(worldPosition);
    }

    // Hacer mientras se arrastra
    if (mouseManager.isSelecting())
    {
        mouseManager.updateSelection(worldPosition);

        sf::Vector2f start = mouseManager.getSelectionStart();
        sf::Vector2f end = mouseManager.getSelectionEnd();

        // Normalizar rectángulo
        sf::Vector2f position(
            std::min(start.x, end.x),
            std::min(start.y, end.y));

        sf::Vector2f size(
            std::abs(end.x - start.x),
            std::abs(end.y - start.y));

        sf::FloatRect rect(position, size);

        auto view = registry.view<MarkedForMining, Position>();

        for (auto entity : view)
        {
            const auto &position = view.get<Position>(entity);

            if (rect.contains(position.value))
            {
                registry.remove<MarkedForMining>(entity);
            }
        }
        auto view2 = registry.view<MarkedForChopping, Position>();

        for (auto entity : view2)
        {
            const auto &position = view2.get<Position>(entity);

            if (rect.contains(position.value))
            {
                registry.remove<MarkedForChopping>(entity);
            }
        }
        auto view3 = registry.view<MarkedForHarvest, Position>();

        for (auto entity : view3)
        {
            const auto &position = view3.get<Position>(entity);

            if (rect.contains(position.value))
            {
                registry.remove<MarkedForHarvest>(entity);
            }
        }
    }
}