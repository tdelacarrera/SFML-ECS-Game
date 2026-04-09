inline void TileMapRenderSystem(entt::registry& registry)
{
    auto& window = registry.ctx().get<WindowResource>().window;

    static sf::Shader shader;

    static bool loaded = false;
    if(!loaded)
    {
        shader.loadFromFile("assets/shaders/tilemap.frag", sf::Shader::Type::Fragment);
        loaded = true;
    }

    auto& world = registry.ctx().get<WorldMap>();

    auto view = registry.view<TileMapComponent>();

    for(auto entity : view)
    {
        auto& tilemap = view.get<TileMapComponent>(entity);

        sf::RenderStates states;
        states.texture = tilemap.texture;
        states.shader = &shader;
        auto view = window.getView();

        shader.setUniform("tileset", *tilemap.texture);
        shader.setUniform("mapData", tilemap.mapDataTexture);
        shader.setUniform("mapSize", sf::Vector2f(world.width, world.height));
        shader.setUniform("tilesPerRow", (float)tilemap.tilesetWidth);
        shader.setUniform("tileSize", (float)world.tileSize);
        states.texture = nullptr;

        window.draw(tilemap.vertices, states);
    }
}