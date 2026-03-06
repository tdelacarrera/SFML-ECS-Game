#pragma once

#include "Game.h"
#include "systems/InputSystem.h"
#include "systems/MovementSystem.h"
#include "systems/RenderSystem.h"
#include "systems/TileMapRenderSystem.h"
#include "systems/BackgroundMusicSystem.h"
#include "systems/CameraSystem.h"
#include "systems/UiRenderSystem.h"
#include "systems/UiEventSystem.h"
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

    engine.addSystem(Stage::Init, BackgroundMusicSystem);
    engine.addSystem(Stage::Input, UiEventSystem);
    engine.addSystem(Stage::Input, InputSystem);
    engine.addSystem(Stage::Update, MovementSystem);
    engine.addSystem(Stage::Update, CameraSystem);
    engine.addSystem(Stage::Render, TileMapRenderSystem);
    engine.addSystem(Stage::Render, RenderSystem);
    engine.addSystem(Stage::Render, UiRenderSystem);


    Prefabs::createPlayer(registry);
    Prefabs::createTileMap(registry, textures.get("tileset"));
    Prefabs::createUIButton(registry, "Click", 300, 250);
    Prefabs::createHUD(registry);
   // Prefabs::createMainMenu(registry);
}
