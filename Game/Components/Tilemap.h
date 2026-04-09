#pragma once
#include <SFML/Graphics.hpp>

struct TileMapComponent
{
    sf::VertexArray vertices;
    const sf::Texture* texture = nullptr;

    int tilesetWidth = 0;
    sf::Texture mapDataTexture;
};