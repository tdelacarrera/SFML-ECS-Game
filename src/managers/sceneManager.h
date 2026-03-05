#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../scene.h"


class SceneManager {
public:
    SceneManager() = default;
    ~SceneManager();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(sf::RenderWindow& window);
    void HandleEvent(const sf::Event& event);

    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    void ReplaceScene(std::unique_ptr<Scene> scene);

    Scene* GetActiveScene();

private:
    std::vector<std::unique_ptr<Scene>> scenes_;
};