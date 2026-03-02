#include "tileMap.h"
#include <stdexcept>

TileMap::TileMap(int w, int h, int tileSize)
    : width_(w), height_(h), tileSize_(tileSize)
{
}

size_t TileMap::addLayer(const std::string& name, int zOrder)
{
    TileLayer layer;
    layer.tiles.assign(height_, std::vector<int>(width_, -1));
    layer.zOrder = zOrder;

    size_t index = layers_.size();
    layers_.push_back(std::move(layer));

    if (!name.empty()) {
        layerByName_[name] = index;
    }

    // Ordenar por zOrder
    std::sort(layers_.begin(), layers_.end(),
              [](const TileLayer& a, const TileLayer& b) { return a.zOrder < b.zOrder; });

    return index;
}

void TileMap::registerTile(int id, const TileDefinition& def)
{
    tileDefs_[id] = def;
}

const TileDefinition* TileMap::getTileDef(int id) const
{
    auto it = tileDefs_.find(id);
    return (it != tileDefs_.end()) ? &it->second : nullptr;
}

void TileMap::setLayerData(size_t layerIndex, const std::vector<std::vector<int>>& data)
{
    if (layerIndex >= layers_.size()) return;
    if (data.size() != static_cast<size_t>(height_) || data[0].size() != static_cast<size_t>(width_)) return;
    layers_[layerIndex].tiles = data;
}

void TileMap::setTile(size_t layer, int x, int y, int tileId)
{
    if (layer >= layers_.size() || x < 0 || x >= width_ || y < 0 || y >= height_) return;
    layers_[layer].tiles[y][x] = tileId;
}

int TileMap::getTileId(size_t layer, int x, int y) const
{
    if (layer >= layers_.size() || x < 0 || x >= width_ || y < 0 || y >= height_) return -1;
    return layers_[layer].tiles[y][x];
}

void TileMap::getVisibleRange(const sf::View& view, int& sx, int& sy, int& ex, int& ey) const
{
    sf::Vector2f center = view.getCenter();
    sf::Vector2f halfSize = view.getSize() / 2.f;

    sx = std::max(0, static_cast<int>((center.x - halfSize.x) / tileSize_) - 1);
    sy = std::max(0, static_cast<int>((center.y - halfSize.y) / tileSize_) - 1);
    ex = std::min(width_,  static_cast<int>((center.x + halfSize.x) / tileSize_) + 2);
    ey = std::min(height_, static_cast<int>((center.y + halfSize.y) / tileSize_) + 2);
}

void TileMap::render(sf::RenderTarget& target, const TextureManager& textures) const
{
    sf::View view = target.getView();
    int startX, startY, endX, endY;
    getVisibleRange(view, startX, startY, endX, endY);

    for (const auto& layer : layers_) {
        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                int id = layer.tiles[y][x];
                if (id < 0) continue;

                const TileDefinition* def = getTileDef(id);
                if (!def) continue;

                const sf::Texture& tex = textures.get(def->textureName);
                sf::Sprite sprite(tex);
                sprite.setPosition({x * tileSize_, y * tileSize_});
                target.draw(sprite);
            }
        }
    }
}