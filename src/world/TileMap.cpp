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
    sf::Image mapImage({width, height}, sf::Color::Black);

    for (unsigned y = 0; y < height; y++)
    {
        for (unsigned x = 0; x < width; x++)
        {
            const Tile &tile = world.getTiles()[x + y * width];

            mapImage.setPixel({x, y}, sf::Color(tile.terrain, 0, 0));
        }
    }

    mapDataTexture.loadFromImage(mapImage);
    mapDataTexture.setSmooth(false);
    mapDataTexture.setRepeated(false);
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