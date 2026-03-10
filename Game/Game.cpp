#pragma once

#include "Game.h"
#include "Systems/InputSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/TileMapRenderSystem.h"
#include "Systems/BackgroundMusicSystem.h"
#include "Systems/TitleScreenMusicSystem.h"
#include "Systems/CameraSystem.h"
#include "Systems/UiRenderSystem.h"
#include "Systems/UiEventSystem.h"
#include "Systems/TerrainGenerationSystem.h"
#include "Systems/BuildTileMapSystem.h"
#include "Systems/VegetationGenerationSystem.h"
#include "Systems/AnimalGenerationSystem.h"
#include "Systems/AnimalMovementSystem.h"
#include "Systems/ColonistGenerationSystem.h"
#include "Systems/UiPauseMenuShowSystem.h"
#include "Systems/PauseInputSystem.h"
#include "Systems/UiMainMenuShowSystem.h"
#include "Systems/PathFollowSystem.h"
#include "Systems/PathDrawSystem.h"
#include "Entities/EntityFactory.h"
#include "Entities/MapFactory.h"
#include "Entities/UiFactory.h"
#include "../Engine/Audio/SoundManager.h"
#include "../Engine/Audio/MusicManager.h"
#include "../Engine/Textures/TextureManager.h"
#include "World/WorldMap.h"
#include "Pathfinding/Pathfinding.h"

void Game::load(Engine& engine)
{
    auto& registry = engine.getRegistry();

    auto& sounds = registry.ctx().get<SoundManager>();
    auto& music = registry.ctx().get<MusicManager>();
    auto& textures = registry.ctx().get<TextureManager>();
    auto& input = registry.ctx().get<InputManager>();
    auto& states = registry.ctx().get<GameStateStack>();

    registry.ctx().emplace<WorldMap>(255,255);
    registry.ctx().emplace<Pathfinding>();
    
    states.push(GameState::Menu);

    input.bind("move_up", sf::Keyboard::Key::W);
    input.bind("move_down", sf::Keyboard::Key::S);
    input.bind("move_left", sf::Keyboard::Key::A);
    input.bind("move_right", sf::Keyboard::Key::D);
    input.bind("zoom_in", sf::Keyboard::Key::Q);
    input.bind("zoom_out", sf::Keyboard::Key::E);
    input.bind("pause", sf::Keyboard::Key::Escape);

    music.load("music1", "assets/music/music1.ogg");
    music.load("music2", "assets/music/music4.ogg");
    sounds.load("test2", "assets/sounds/test2.mp3");
    sounds.load("cat", "assets/sounds/cat.ogg");
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
    engine.addSystem(Stage::Render, UiPauseMenuShowSystem, {GameState::Paused});
    engine.addSystem(Stage::OnExit, UiMainMenuShowSystem, {GameState::Paused});
    

    engine.addSystem(Stage::Input, PauseInputSystem, {GameState::Playing, GameState::Paused});
    engine.addSystem(Stage::Input, UiEventSystem, {GameState::Menu, GameState::Playing, GameState::Paused});
    engine.addSystem(Stage::Input, InputSystem, {GameState::Playing, GameState::Paused});

    engine.addSystem(Stage::Update, AnimalMovementSystem, {GameState::Playing});
    engine.addSystem(Stage::Update, PathFollowSystem, {GameState::Playing});
    engine.addSystem(Stage::Update, CameraSystem, {GameState::Playing});
    
    engine.addSystem(Stage::Render, TileMapRenderSystem, {GameState::Playing, GameState::Paused});
    engine.addSystem(Stage::Render, PathDrawSystem, {GameState::Playing, GameState::Paused});
    engine.addSystem(Stage::Render, RenderSystem, {GameState::Playing, GameState::Paused});
    engine.addSystem(Stage::Render, UiRenderSystem, {GameState::Menu, GameState::Playing,  GameState::Paused});

    EntityFactory::createTileMap(registry, textures.get("tileset"));
    EntityFactory::createHUD(registry);
    EntityFactory::createMainMenu(registry, textures.get("background"));
    EntityFactory::createPauseMenu(registry);
}
