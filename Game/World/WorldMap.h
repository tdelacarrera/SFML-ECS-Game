#pragma once

#include <vector>
#include <cstdint>

struct Tile
{
    uint16_t terrain;
    float cost = 1.f;
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

    bool inBounds(int x, int y) const
    {
        return x >= 0 && y >= 0 && x < width && y < height;
    }
};