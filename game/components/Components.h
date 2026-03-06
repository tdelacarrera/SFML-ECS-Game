#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

struct UiWidgetComponent
{
    tgui::Widget::Ptr widget;
};

struct UiRootComponent
{
};

struct UiHudTag {};

struct UiMenuTag {};

struct TransformComponent 
{
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;
};

struct PlayerComponent {};

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