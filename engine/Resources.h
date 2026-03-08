#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

struct WindowResource
{
    sf::RenderWindow window;
};

struct TimeResource
{
    float deltaTime = 0;
};

struct EventResource
{
    std::vector<sf::Event> events;
};

struct GuiResource
{
    tgui::SFML_GRAPHICS::Gui gui;
};

struct Tile
{
    uint16_t terrain;   // grass, dirt, stone
    bool walkable;
    bool buildable;
};

struct WorldMap
{
    int width;
    int height;

    std::vector<Tile> tiles;

    Tile& get(int x, int y)
    {
        return tiles[x + y * width];
    }
};