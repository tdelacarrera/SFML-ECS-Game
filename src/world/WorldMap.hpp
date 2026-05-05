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

struct TileDef
{
    uint16_t terrain;
    float cost;
    bool walkable;
    bool buildable;
};

class WorldMap
{
public:
    WorldMap(int w, int h, int tileSize = 32)
        : width(w), height(h), tileSize(tileSize), tiles(w * h)
    {

        initTileDefs();
    }

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

                uint16_t terrain;

                if (n < -0.4f)
                    terrain = 0;
                else if (n < -0.1f)
                    terrain = 3;
                else if (n < 0.2f)
                    terrain = 1;
                else if (n < 0.8f)
                    terrain = 2;
                else
                    terrain = 4;

                setTile(x, y, terrain);
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
    std::vector<Tile> getTiles() const & { return tiles; }

    void setTile(int x, int y, uint16_t terrain)
    {
        Tile &tile = at(x, y);

        auto it = tileDefs.find(terrain);

        if (it != tileDefs.end())
        {
            const TileDef &def = it->second;

            tile.terrain = def.terrain;
            tile.cost = def.cost;
            tile.walkable = def.walkable;
            tile.buildable = def.buildable;
        }
        else
        {
            // fallback
            tile.terrain = terrain;
            tile.cost = 1.f;
            tile.walkable = true;
            tile.buildable = true;
        }
    }

    void initTileDefs()
    {
        tileDefs[0] = {0, 0.f, true, true};
        tileDefs[1] = {1, 0.f, true, true};
        tileDefs[2] = {2, 0.f, false, false};
        tileDefs[3] = {3, 0.f, true, true};
        tileDefs[4] = {1, 0.f, true, true};
    }

private:
    int width;
    int height;
    int tileSize;

    std::vector<Tile> tiles;
    std::unordered_map<uint16_t, TileDef> tileDefs;

    int index(int x, int y) const
    {
        return x + y * width;
    }
};