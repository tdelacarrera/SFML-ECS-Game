#pragma once

#include <vector>
#include <cassert>
#include <cstdint>
#include <FastNoiseLite.h>

struct Tile
{
    uint16_t terrain = 0;
    float cost = 1.f;
    bool walkable = true;
    bool buildable = true;
};

class WorldMap
{
public:
    WorldMap(int w, int h, int tileSize = 32)
        : width(w), height(h), tileSize(tileSize), tiles(w * h) {}

    void generate(int seed = 1337)
    {
        FastNoiseLite noise;
        noise.SetSeed(seed);
        noise.SetFrequency(0.05f);

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                Tile &tile = at(x, y);
                float n = noise.GetNoise((float)x, (float)y);

                applyTerrain(tile, n);
            }
        }
    }

    Tile &at(int x, int y)
    {
        assert(inBounds(x, y));
        return tiles[index(x, y)];
    }

    const Tile &at(int x, int y) const
    {
        assert(inBounds(x, y));
        return tiles[index(x, y)];
    }

    bool inBounds(int x, int y) const
    {
        return x >= 0 && y >= 0 && x < width && y < height;
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getTileSize() const { return tileSize; }
    std::vector<Tile> getTiles() const { return tiles; }

private:
    int width;
    int height;
    int tileSize;

    std::vector<Tile> tiles;

    int index(int x, int y) const
    {
        return x + y * width;
    }

    void applyTerrain(Tile &tile, float n)
    {
        if (n < -0.4f)
        {
            tile = {1, 1.f, false, false};
        }
        else if (n < -0.1f)
        {
            tile = {7, 1.f, true, false};
        }
        else if (n < 0.2f)
        {
            tile = {6, 5.f, true, true};
        }
        else if (n < 0.8f)
        {
            tile = {10, 1.f, true, true};
        }
        else
        {
            tile = {4, 10.f, true, true};
        }
    }
};