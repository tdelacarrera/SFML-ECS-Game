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
#include "systems/TestOnExitSystem.h"
#include "systems/WorldGenerationSystem.h"
#include "systems/BuildTileMapSystem.h"
#include "Prefabs.h"

void Game::load(Engine& engine)
{
    auto& registry = engine.getRegistry();

    auto& sounds = registry.ctx().get<SoundManager>();
    auto& music = registry.ctx().get<MusicManager>();
    auto& textures = registry.ctx().get<TextureManager>();
    auto& bindings = registry.ctx().get<InputBindings>();

    bindings.bind("move_up", sf::Keyboard::Key::W);
    bindings.bind("move_down", sf::Keyboard::Key::S);
    bindings.bind("move_left", sf::Keyboard::Key::A);
    bindings.bind("move_right", sf::Keyboard::Key::D);

    music.load("music1", "assets/music/music2.ogg");
    sounds.load("test2", "assets/sounds/test2.mp3");
    textures.load("colonist", "assets/textures/tile2.png");
    textures.load("tileset", "assets/textures/tileset.png");


    engine.addSystem(Stage::OnEnter, BackgroundMusicSystem, {GameState::Playing});
    engine.addSystem(Stage::OnEnter, WorldGenerationSystem, {GameState::Playing});
    engine.addSystem(Stage::OnEnter, BuildTileMapSystem, {GameState::Playing});
    engine.addSystem(Stage::Input, InputSystem, {GameState::Playing});
    engine.addSystem(Stage::Update, MovementSystem, {GameState::Playing});
    engine.addSystem(Stage::Update, CameraSystem, {GameState::Playing});
    engine.addSystem(Stage::Render, TileMapRenderSystem, {GameState::Playing});
    engine.addSystem(Stage::Render, RenderSystem, {GameState::Playing});

    engine.addSystem(Stage::Input, UiEventSystem, {GameState::Menu, GameState::Playing});
    engine.addSystem(Stage::Render, UiRenderSystem, {GameState::Menu, GameState::Playing});
    engine.addSystem(Stage::OnExit, TestOnExitSystem, {GameState::Menu});


    Prefabs::createPlayer(registry);
    Prefabs::createTileMap(registry, textures.get("tileset"));
    Prefabs::createUIButton(registry, "Click", 300, 250);
    Prefabs::createHUD(registry);
    Prefabs::createMainMenu(registry);
}
