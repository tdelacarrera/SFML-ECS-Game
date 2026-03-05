#pragma once

#include "Game.h"
#include "systems/InputSystem.h"
#include "systems/MovementSystem.h"
#include "systems/RenderSystem.h"
#include "systems/TileMapRenderSystem.h"
#include "systems/PlayBackgroundMusic.h"
#include "Prefabs.h"

void Game::load(Engine& engine)
{
    auto& registry = engine.getRegistry();

    auto& sounds = registry.ctx().get<SoundManager>();
    auto& music = registry.ctx().get<MusicManager>();
    auto& textures = registry.ctx().get<TextureManager>();

    music.load("music1", "assets/music/music2.ogg");
    sounds.load("test2", "assets/sounds/test2.mp3");
    textures.load("colonist", "assets/textures/tile2.png");
    textures.load("tileset", "assets/textures/tileset.png");

    engine.addSystem(Stage::Init, PlayBackgroundMusic);
    engine.addSystem(Stage::Input, InputSystem);
    engine.addSystem(Stage::Update, MovementSystem);
    engine.addSystem(Stage::Render, TileMapRenderSystem);
    engine.addSystem(Stage::Render, RenderSystem);
    

    Prefabs::createPlayer(registry);


    TileMapData mapData;
    mapData.width = 10;
    mapData.height = 10;
    mapData.tiles.resize(mapData.width * mapData.height);

    for (unsigned int j = 0; j < mapData.height; ++j) {
        for (unsigned int i = 0; i < mapData.width; ++i) {
            if ((i + j) % 2 == 0)
                mapData.tiles[i + j * mapData.width] = 0;
            else
                mapData.tiles[i + j * mapData.width] = 1;
        }
    }

    auto tilemapEntity = Prefabs::createTileMap(registry, textures.get("tileset"), mapData.tiles, mapData.width, mapData.height, 16);

}
