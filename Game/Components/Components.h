#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

struct UiWidgetComponent
{
    tgui::Widget::Ptr widget;
};

struct UiHudTag {};

struct UiMenuTag {};

struct UiPauseMenuTag {};

struct TransformComponent 
{
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;
};

struct SpriteComponent 
{
    std::string textureId;
};

struct TileMapComponent
{
    const sf::Texture* texture;

    int tileSize;

    int width;
    int height;

    int tilesetWidth; // cantidad de tiles en el tileset

    sf::VertexArray vertices;
};

struct AnimalComponent
{
    sf::Vector2f direction;
    float speed;
    float changeDirectionTimer;
};

struct PathComponent
{
    std::vector<sf::Vector2i> path;
    int currentIndex = 0;
};


struct SelectedComponent {};

struct SelectableComponent {};

struct ChoppableComponent {};

struct ChopMarkedComponent {};

struct MinableComponent {};

struct MineMarkedComponent {};

struct HarvestableComponent {};

struct HarvestMarkedComponent {};


//HUD
enum class ToolMode
{
    None,
    Chop,
    Mine,
    Harvest,
    Build,
    Cancel,
    ZoneStorage
};

struct ToolState
{
    ToolMode current = ToolMode::None;
};

struct ResourceData
{
    int wood = 0;
    int food = 0;
    int stone = 0;
};
