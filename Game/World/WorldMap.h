#pragma once

#include "Tile.h"

struct WorldMap
{
    int width;
    int height;

    int tileSize = 64;

    std::vector<Tile> tiles;

    Tile& get(int x, int y)
    {
        assert(inBounds(x, y));
        return tiles[x + y * width];
    }

    bool inBounds(int x, int y) const
    {
        return x >= 0 && y >= 0 && x < width && y < height;
    }
};