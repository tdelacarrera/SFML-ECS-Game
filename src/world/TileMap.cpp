#include "TileMap.hpp"
#include <iostream>

bool TileMap::load(const sf::Texture &tileset, const WorldMap &world)
{
    tilesetTexture = &tileset;

    width = world.getWidth();
    height = world.getHeight();
    tileSize = world.getTileSize();

    tilesPerRow = tileset.getSize().x / tileSize;

    // crear geometria
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(width * height * 6);

    int v = 0;

    for (unsigned y = 0; y < height; y++)
    {
        for (unsigned x = 0; x < width; x++)
        {
            const Tile &tile = world.getTiles()[x + y * width];
            int tileNumber = tile.terrain;

            int tu = tileNumber % tilesPerRow;
            int tv = tileNumber / tilesPerRow;

            float px = x * tileSize;
            float py = y * tileSize;

            float tx = tu * tileSize;
            float ty = tv * tileSize;

            sf::Vertex *quad = &vertices[v];

            // posiciones
            quad[0].position = {px, py};
            quad[1].position = {px + tileSize, py};
            quad[2].position = {px + tileSize, py + tileSize};

            quad[3].position = {px, py};
            quad[4].position = {px + tileSize, py + tileSize};
            quad[5].position = {px, py + tileSize};

            // UV normales
            float mapW = (float)width;
            float mapH = (float)height;

            quad[0].texCoords = {x / mapW, y / mapH};
            quad[1].texCoords = {(x + 1) / mapW, y / mapH};
            quad[2].texCoords = {(x + 1) / mapW, (y + 1) / mapH};

            quad[3].texCoords = {x / mapW, y / mapH};
            quad[4].texCoords = {(x + 1) / mapW, (y + 1) / mapH};
            quad[5].texCoords = {x / mapW, (y + 1) / mapH};

            v += 6;
        }
    }

    // textura de datos
    updateMapData(world);

    // shader
    {
        if (!shader.loadFromFile("assets/shaders/tilemap.frag", sf::Shader::Type::Fragment))
        {
            std::cerr << "Error cargando shader tilemap\n";
        }
        shaderLoaded = true;
    }

    return true;
}

void TileMap::updateMapData(const WorldMap &world)
{
    width = world.getWidth();
    height = world.getHeight();

    mapDataPixels.resize(static_cast<size_t>(width) * height * 4);

    for (unsigned y = 0; y < height; ++y)
    {
        for (unsigned x = 0; x < width; ++x)
        {
            const Tile &tile = world.getTiles()[x + y * width];
            std::uint8_t terrainId = static_cast<std::uint8_t>(tile.terrain);

            size_t idx = (static_cast<size_t>(x) + static_cast<size_t>(y) * width) * 4;

            mapDataPixels[idx + 0] = terrainId; // R = terrain ID
            mapDataPixels[idx + 1] = 0;
            mapDataPixels[idx + 2] = 0;
            mapDataPixels[idx + 3] = 255; // A
        }
    }

    if (!mapDataTexture.resize({width, height}))
    {
        std::cerr << "Error al redimensionar mapDataTexture\n";
        return;
    }

    mapDataTexture.update(mapDataPixels.data());
    mapDataTexture.setSmooth(false);
    mapDataTexture.setRepeated(false);
}

void TileMap::updateTile(int x, int y, uint16_t terrain)
{
    if (x < 0 || y < 0 || x >= static_cast<int>(width) || y >= static_cast<int>(height))
        return;

    size_t idx = (x + y * width) * 4;

    mapDataPixels[idx + 0] = (uint8_t)terrain;
    mapDataPixels[idx + 1] = 0;
    mapDataPixels[idx + 2] = 0;
    mapDataPixels[idx + 3] = 255;

    mapDataTexture.update(
        &mapDataPixels[idx],
        {1, 1},
        {(unsigned)x, (unsigned)y});
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!tilesetTexture)
        return;

    states.transform *= getTransform();

    states.texture = nullptr;
    states.shader = &shader;

    // uniforms
    shader.setUniform("tileset", *tilesetTexture);
    shader.setUniform("mapData", mapDataTexture);
    shader.setUniform("mapSize", sf::Vector2f(width, height));
    shader.setUniform("tilesPerRow", (float)tilesPerRow);
    shader.setUniform("time", time);

    target.draw(vertices, states);
}

void TileMap::update(float dt)
{
    time += dt;
}