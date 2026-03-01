#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "textureManager.h"

enum class TileType {
    Grass,
    Wall
};

struct Tile {
    TileType type = TileType::Grass;
};

class TileMap {
private:
    int width_;
    int height_;
    int tileSize_;
    std::vector<std::vector<Tile>> tiles_;

public:
    TileMap(int width, int height, int tileSize);
    void fill();
    void setTile(int x, int y, TileType type);
    const Tile& getTile(int x, int y) const;
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getTileSize() const { return tileSize_; }
    void render(sf::RenderTarget& target, const TextureManager& textures) const;
};