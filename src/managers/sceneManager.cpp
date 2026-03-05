#include "sceneManager.h"

SceneManager::~SceneManager() = default;

void SceneManager::Update(float dt) {
    if (!scenes_.empty()) {
        scenes_.back()->Update(dt);
    }
}

void SceneManager::Render(sf::RenderWindow& window) {
    for (auto& scene : scenes_) {
        scene->Render(window);
    }
}

void SceneManager::HandleEvent(const sf::Event& event) {
    if (!scenes_.empty()) {
        scenes_.back()->HandleEvent(event);
    }
}

void SceneManager::PushScene(std::unique_ptr<Scene> scene) {
    if (!scenes_.empty()) {
        scenes_.back()->OnExit();
    }
    scenes_.push_back(std::move(scene));
    if (!scenes_.empty()) { 
        scenes_.back()->OnEnter();
    }
}


void SceneManager::PopScene() {
    if (scenes_.empty()) {
        return;
    }

    scenes_.back()->OnExit();
    scenes_.pop_back();

    if (!scenes_.empty()) {
        scenes_.back()->OnEnter();
    }
}

void SceneManager::ReplaceScene(std::unique_ptr<Scene> scene) {
    PopScene();
    PushScene(std::move(scene));
}

Scene* SceneManager::GetActiveScene() {
    return scenes_.empty() ? nullptr : scenes_.back().get();
}