#pragma once
#include <SFML/Graphics.hpp>
#include "WorldMap.hpp"
#include <cstdint>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const sf::Texture &tileset, const WorldMap &world);
    void updateMapData(const WorldMap &world);
    void updateTile(int x, int y, uint16_t terrain);
    void update(float dt);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    float time = 0.f;
    std::vector<std::uint8_t> mapDataPixels;

    // GPU
    sf::VertexArray vertices;
    const sf::Texture *tilesetTexture = nullptr;
    sf::Texture mapDataTexture;

    // shader
    bool useShader = true;
    mutable sf::Shader shader;
    mutable bool shaderLoaded = false;

    // cache
    unsigned width = 0;
    unsigned height = 0;
    unsigned tileSize = 0;
    unsigned tilesPerRow = 0;
};