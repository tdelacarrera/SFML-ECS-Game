#pragma once
#include <memory>
#include "Scene.hpp"

class Game;

class SceneManager
{
public:
    SceneManager(Game &game, sf::RenderWindow &win);

    template <typename T, typename... Args>
    void changeScene(Args &&...args)
    {
        if (currentScene)
            currentScene->onDestroy();

        currentScene = std::make_unique<T>(std::forward<Args>(args)...);
        currentScene->setSceneManager(this);
        currentScene->setWindow(window);
        currentScene->onCreate();
    }

    template <typename T, typename... Args>
    void requestSceneChange(Args &&...args)
    {
        nextScene = [this, args...]()
        {
            changeScene<T>(args...);
        };
    }

    void applyPendingChange()
    {
        if (nextScene)
        {
            nextScene();
            nextScene = nullptr;
        }
    }
    Scene *getCurrentScene();
    Game &getGame() { return game; }

private:
    Game &game;
    std::unique_ptr<Scene> currentScene;
    sf::RenderWindow &window;
    std::function<void()> nextScene = nullptr;
};