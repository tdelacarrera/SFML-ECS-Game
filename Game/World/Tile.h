#pragma once

struct Tile
{
    uint16_t terrain;
    float cost = 1.f;
    bool walkable;
    bool buildable;
};