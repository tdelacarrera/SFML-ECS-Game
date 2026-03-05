#include "mainScene.h"
#include "engineContext.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

MainScene::MainScene(EngineContext& context) :
    Scene(context), tilemap_(200, 200, 16)
{
}

void MainScene::OnEnter() {

    context_.textures_.load("grass",    "content/textures/tile1.png");
    context_.textures_.load("wall",     "content/textures/tile2.png");
    context_.textures_.load("colonist", "content/textures/colonist.png");

    context_.sounds_.load("walk", "content/sounds/walk.wav");
    context_.sounds_.load("test", "content/sounds/test.ogg");

    context_.music_.load("music", "content/music/music2.ogg");
    context_.music_.play("music");

    prefabs_.spawnColonist(registry_, {10.f, 10.f});
    prefabs_.spawnEnemy(registry_,   {10.f, 40.f});

    tilemap_.setTileSize(16);
    tilemap_.registerTile(0, TileDefinition{"grass"});
    tilemap_.registerTile(1, TileDefinition{"wall"});
    InitTilemap();
    InputTest();
}

void MainScene::OnExit() {
}

void MainScene::HandleEvent(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto* keyEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyEvent && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
            context_.sceneManager_.PopScene();  // O ReplaceScene si quieres cambiar
        }
    }
}

void MainScene::Update(float dt) {

    movementSystem_.update(registry_, dt);
}


void MainScene::Render(sf::RenderWindow& window) {
    tilemap_.render(window, context_.textures_);
    renderSystem_.draw(registry_, context_.textures_, window);
}

void MainScene::InitTilemap()
{
    size_t groundLayer = tilemap_.addLayer("ground", 0);
    size_t wallLayer = tilemap_.addLayer("wallLayer", 1);

    tilemap_.setTile(groundLayer, 2, 2, 0);
    tilemap_.setTile(groundLayer, 6, 2, 0);

    for (int y = 0; y < tilemap_.getHeight(); y++) {
        for (int x = 0; x < tilemap_.getWidth(); x++) {
            tilemap_.setTile(groundLayer, x, y, 0);
        }
    }

    for (int x = 5; x < 30; x++) {
        tilemap_.setTile(wallLayer, x, 5, 1);
    }
    for (int y = 5; y < 50; y++) {
        tilemap_.setTile(wallLayer, 4, y, 1);
    }
}

void MainScene::InputTest()
{
    if (context_.input_.isActionJustPressed(Action::MoveRight)) std::cout <<"Move Right"<<std::endl;
    if (context_.input_.isActionJustReleased(Action::MoveLeft)) std::cout <<"Move Left"<<std::endl;
    if (context_.input_.isActionActive(Action::MoveUp)) std::cout <<"Move Up"<<std::endl;
    if (context_.input_.isActionActive(Action::MoveDown)) std::cout <<"Move Down"<<std::endl;
}