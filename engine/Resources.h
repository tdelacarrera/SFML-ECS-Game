#pragma once

#include <SFML/Graphics.hpp>

struct WindowResource
{
    sf::RenderWindow window;
};

struct TimeResource
{
    float deltaTime = 0;
};

struct TileMapResource {
    unsigned int width;
    unsigned int height;
    unsigned int tileSize;
    sf::Texture texture;
    sf::VertexArray vertices;
    std::vector<int> tiles;
};