#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "textureManager.h"

struct TileDefinition {
    std::string textureName;
};

struct TileLayer {
    std::vector<std::vector<int>> tiles;
    int zOrder = 0;
};

class TileMap {
public:
    TileMap(int mapWidth, int mapHeight, int tilePixelSize = 32);

    void setTileSize(int pixels) { tileSize_ = pixels; }
    int getTileSize() const { return tileSize_; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    void registerTile(int id, const TileDefinition& def);
    const TileDefinition* getTileDef(int id) const;

    size_t addLayer(const std::string& name = "default", int zOrder = 0);
    void setLayerData(size_t layerIndex, const std::vector<std::vector<int>>& data);
    void setTile(size_t layer, int x, int y, int tileId);
    int getTileId(size_t layer, int x, int y) const;

    void render(sf::RenderTarget& target, const TextureManager& textures) const;

private:
    int width_;
    int height_;
    int tileSize_;

    std::unordered_map<int, TileDefinition> tileDefs_;
    std::vector<TileLayer> layers_;
    std::unordered_map<std::string, size_t> layerByName_;

    void getVisibleRange(const sf::View& view, int& startX, int& startY, int& endX, int& endY) const;
};