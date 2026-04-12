#pragma once
#include <SFML/Graphics.hpp>
#include "WorldMap.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const sf::Texture &tileset, const WorldMap &world);
    void updateMapData(const WorldMap &world);
    void update(float dt);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    float time = 0.f;

private:
    // GPU
    sf::VertexArray vertices;
    const sf::Texture *tilesetTexture = nullptr;
    sf::Texture mapDataTexture;

    // shader
    mutable sf::Shader shader;
    mutable bool shaderLoaded = false;

    // cache
    unsigned width = 0;
    unsigned height = 0;
    unsigned tileSize = 0;
    unsigned tilesPerRow = 0;
};