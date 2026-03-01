#include "game.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "components/components.h"

Game::Game() : window_(sf::VideoMode({1000, 800}), "SFML Game"), tilemap_(255 , 255, 16), entities_(registry_)
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

    view_.setSize({window_.getSize().x, window_.getSize().y});
    view_.setCenter({0.f, 0.f});
    
    prefabs_.spawnColonist(registry_, {10, 10});
    prefabs_.spawnEnemy(registry_, {10, 40});

}

bool Game::isRunning() const
{
    return window_.isOpen();
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
    movementSystem_.update(registry_, sound_, dt);
}

void Game::render()
{
    window_.clear(sf::Color::Black);

    window_.setView(view_);

    tilemap_.render(window_, textures_);
    renderSystem_.draw(registry_, textures_, window_);

    window_.display();

}