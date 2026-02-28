#include "game.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "components/components.h"

Game::Game() : window_(sf::VideoMode({1000, 800}), "SFML Game")
{
    window_.setFramerateLimit(60);
    window_.setMouseCursorVisible(false);
    
    textures_.load("grass", "content/textures/tile1.png");
    textures_.load("wall", "content/textures/tile2.png");
    textures_.load("colonist", "content/textures/colonist.png");

    sound_.load("walk", "content/sounds/walk.wav");
    sound_.load("test", "content/sounds/test.ogg");

    music_.load("music", "content/music/music2.ogg");
    music_.play("music");
    
    initEntities();
}

bool Game::isRunning() const
{
    return window_.isOpen();
}

void Game::initEntities()
{
    player_ = registry_.create();
    registry_.emplace<TransformComponent>(player_,sf::Vector2f{0.f, 0.f},  sf::Vector2f{1.f, 1.f},  0.f);
    registry_.emplace<SpriteComponent>(player_, "colonist");
    registry_.emplace<SoundComponent>(player_, "test");
}

void Game::processEvents()
{
    while (const std::optional event = window_.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        window_.close();
    }
}

void Game::update()
{
    float dt = clock_.restart().asSeconds();
    movementSystem.update(registry_, sound_, dt);
}

void Game::render()
{
    window_.clear(sf::Color::Black);

    window_.setView(view_);

    renderSystem.draw(registry_, textures_, window_);

    window_.display();

}