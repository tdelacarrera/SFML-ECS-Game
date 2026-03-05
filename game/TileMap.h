#include "components/Components.h"
#include <SFML/Graphics.hpp>

struct TileMapData
{
    std::vector<int> tiles;
    unsigned int width;
    unsigned int height;
};


void buildTileMap(TileMapComponent& tilemap, const TileMapData& data) {
    tilemap.width = data.width;
    tilemap.height = data.height;
    tilemap.vertices.clear();

    for (unsigned int j = 0; j < data.height; ++j) {
        for (unsigned int i = 0; i < data.width; ++i) {
            int tileNumber = data.tiles[i + j * data.width];

            int tilesPerRow = tilemap.texture.getSize().x / tilemap.tileSize;
            int tu = tileNumber % tilesPerRow;
            int tv = tileNumber / tilesPerRow;

            float x = i * tilemap.tileSize;
            float y = j * tilemap.tileSize;

            float ts = static_cast<float>(tilemap.tileSize);
            float tx = tu * ts;
            float ty = tv * ts;

            tilemap.vertices.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::White, sf::Vector2f(tx, ty)));
            tilemap.vertices.append(sf::Vertex(sf::Vector2f(x + ts, y), sf::Color::White, sf::Vector2f(tx + ts, ty)));
            tilemap.vertices.append(sf::Vertex(sf::Vector2f(x + ts, y + ts), sf::Color::White, sf::Vector2f(tx + ts, ty + ts)));

            tilemap.vertices.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::White, sf::Vector2f(tx, ty)));
            tilemap.vertices.append(sf::Vertex(sf::Vector2f(x + ts, y + ts), sf::Color::White, sf::Vector2f(tx + ts, ty + ts)));
            tilemap.vertices.append(sf::Vertex(sf::Vector2f(x, y + ts), sf::Color::White, sf::Vector2f(tx, ty + ts)));
        }
    }
}
