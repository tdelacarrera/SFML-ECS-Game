#pragma once

#include <vector>
#include <cstdint>

//solo datos para renderizado
struct TileMapComponent
{
    const sf::Texture* texture;
    int tilesetWidth;
    sf::VertexArray vertices;
};