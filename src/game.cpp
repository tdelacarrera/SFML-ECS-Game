#include "game.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "components/components.h"

Game::Game() :
    window_(sf::VideoMode({1000, 800}), "SFML Game")
{
    window_.setFramerateLimit(60);
    window_.setMouseCursorVisible(false);
    
    textures_.Load("grass",    "Content/Textures/tile1.png");
    textures_.Load("wall",     "Content/Textures/tile2.png");
    textures_.Load("colonist", "Content/Textures/colonist.png");

    InitEntities();
}

bool Game::IsRunning() const
{
    return window_.isOpen();
}

void Game::InitEntities()
{
    player_ = registry_.create();
    registry_.emplace<TransformComponent>(player_,sf::Vector2f{0.f, 0.f},  sf::Vector2f{1.f, 1.f},  0.f);
    registry_.emplace<SpriteComponent>(player_, sf::Sprite(textures_.Get("colonist")));
}

void Game::ProcessEvents()
{
    while (const std::optional event = window_.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        window_.close();
    }
}

void Game::Update()
{
    float dt = clock_.restart().asSeconds();
    movementSystem.Update(registry_, dt);
   
}

void Game::Render()
{
    window_.clear(sf::Color::Black);

    renderSystem.Draw(registry_, window_);

    window_.display();

}

