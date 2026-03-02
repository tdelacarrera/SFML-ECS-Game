#include "tileMap.h"
#include <string>

TileMap::TileMap(int width, int height, int tileSize)
    : width_(width), height_(height), tileSize_(tileSize),
      tiles_(height, std::vector<Tile>(width)) {
    fill();
}

void TileMap::fill() {
    for (auto& row : tiles_) {
        for (auto& tile : row) {
            tile.type = TileType::Grass;
            setTile(2,2, TileType::Wall);
            setTile(2,3, TileType::Wall);
            setTile(2,4, TileType::Wall);
            setTile(2,5, TileType::Wall);
            setTile(5,6, TileType::Wall);
            setTile(5,8, TileType::Wall);
            setTile(5,9, TileType::Wall);
            setTile(7,9, TileType::Wall);
            setTile(7,2, TileType::Wall);
            setTile(17,22, TileType::Wall);
            setTile(12,12, TileType::Wall);
        }
    }
}

void TileMap::setTile(int x, int y, TileType type) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        tiles_[y][x].type = type;
    }
}

const Tile& TileMap::getTile(int x, int y) const {
    return tiles_[y][x];
}

void TileMap::render(sf::RenderTarget& target, const TextureManager& textures) const {
    sf::View view = target.getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f halfSize = view.getSize() / 2.f;

    // Culling
    int startX = std::max(0, static_cast<int>((center.x - halfSize.x) / tileSize_));
    int startY = std::max(0, static_cast<int>((center.y - halfSize.y) / tileSize_));
    int endX = std::min(width_, static_cast<int>((center.x + halfSize.x) / tileSize_) + 1);
    int endY = std::min(height_, static_cast<int>((center.y + halfSize.y) / tileSize_) + 1);

    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            const Tile& tile = getTile(x, y);
            std::string texName = (tile.type == TileType::Grass) ? "grass" : "wall";
            const sf::Texture& texture = textures.get(texName);
            sf::Sprite sprite(texture);
            sprite.setPosition({x * tileSize_, y * tileSize_});
            target.draw(sprite);
        }
    }
}