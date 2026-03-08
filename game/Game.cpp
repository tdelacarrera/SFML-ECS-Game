#pragma once

#include "Game.h"
#include "systems/InputSystem.h"
#include "systems/RenderSystem.h"
#include "systems/TileMapRenderSystem.h"
#include "systems/BackgroundMusicSystem.h"
#include "systems/TitleScreenMusicSystem.h"
#include "systems/CameraSystem.h"
#include "systems/UiRenderSystem.h"
#include "systems/UiEventSystem.h"
#include "systems/TerrainGenerationSystem.h"
#include "systems/BuildTileMapSystem.h"
#include "systems/VegetationGenerationSystem.h"
#include "systems/AnimalGenerationSystem.h"
#include "systems/AnimalMovementSystem.h"
#include "systems/ColonistGenerationSystem.h"
#include "systems/UiPauseMenuShowSystem.h"
#include "systems/PauseInputSystem.h"
#include "EntityFactory.h"

void Game::load(Engine& engine)
{
    auto& registry = engine.getRegistry();

    auto& sounds = registry.ctx().get<SoundManager>();
    auto& music = registry.ctx().get<MusicManager>();
    auto& textures = registry.ctx().get<TextureManager>();
    auto& bindings = registry.ctx().get<InputBindings>();
    auto& states = registry.ctx().get<GameStateStack>();
    
    states.push(GameState::Menu);

    bindings.bind("move_up", sf::Keyboard::Key::W);
    bindings.bind("move_down", sf::Keyboard::Key::S);
    bindings.bind("move_left", sf::Keyboard::Key::A);
    bindings.bind("move_right", sf::Keyboard::Key::D);
    bindings.bind("zoom_in", sf::Keyboard::Key::Q);
    bindings.bind("zoom_out", sf::Keyboard::Key::E);
    bindings.bind("pause", sf::Keyboard::Key::Space);

    music.load("music1", "assets/music/music1.ogg");
    music.load("music2", "assets/music/music4.ogg");
    sounds.load("test2", "assets/sounds/test2.mp3");
    textures.load("tree", "assets/textures/tree.png");
    textures.load("tileset", "assets/textures/tilemap64.png");
    textures.load("colonist", "assets/textures/colonist.png");
    textures.load("animal", "assets/textures/animal.png");
    textures.load("background", "assets/textures/background.png");

    engine.addSystem(Stage::OnEnter, TitleScreenMusicSystem, {GameState::Menu});
    engine.addSystem(Stage::OnEnter, BackgroundMusicSystem, {GameState::Playing});
    engine.addSystem(Stage::OnEnter, TerrainGenerationSystem, {GameState::Playing});
    engine.addSystem(Stage::OnEnter, BuildTileMapSystem, {GameState::Playing});
    engine.addSystem(Stage::OnEnter, VegetationGenerationSystem, {GameState::Playing});
    engine.addSystem(Stage::OnEnter, AnimalGenerationSystem, {GameState::Playing});
    engine.addSystem(Stage::OnEnter, ColonistGenerationSystem, {GameState::Playing});
    
    engine.addSystem(Stage::Input, InputSystem, {GameState::Playing});
    engine.addSystem(Stage::Input, PauseInputSystem, {GameState::Playing, GameState::Paused});
    engine.addSystem(Stage::Input, UiEventSystem, {GameState::Menu, GameState::Playing});

    engine.addSystem(Stage::Update, AnimalMovementSystem, {GameState::Playing});
    engine.addSystem(Stage::Update, CameraSystem, {GameState::Playing});
    
    engine.addSystem(Stage::Render, UiPauseMenuShowSystem, {GameState::Paused});
    engine.addSystem(Stage::Render, TileMapRenderSystem, {GameState::Playing, GameState::Paused});
    engine.addSystem(Stage::Render, RenderSystem, {GameState::Playing, GameState::Paused});
    engine.addSystem(Stage::Render, UiRenderSystem, {GameState::Menu, GameState::Playing,  GameState::Paused});

    EntityFactory::createTileMap(registry, textures.get("tileset"));
    EntityFactory::createHUD(registry);
    EntityFactory::createMainMenu(registry, textures.get("background"));
    EntityFactory::createPauseMenu(registry);
}
