#include "engine.h"
#include "IGame.h"

Engine::Engine(unsigned w, unsigned h, const std::string& title)
    : window_(sf::VideoMode({w, h}), title, sf::Style::Close | sf::Style::Titlebar),
      tilemap_(100, 100, 16),
      gui_(window_),
      input_(window_)
{
    window_.setFramerateLimit(60);
    window_.setMouseCursorVisible(true);
}

float Engine::getDeltaTime() {
    return clock_.restart().asSeconds();
}

void Engine::setGameView() {
    window_.setView(view_);
}