#include "SceneManager.hpp"
#include "Game.hpp"

SceneManager::SceneManager(Game &game, sf::RenderWindow &win)
    : game(game), window(win)
{
}

Scene *SceneManager::getCurrentScene()
{
    return currentScene.get();
}