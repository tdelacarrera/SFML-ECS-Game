#pragma once

#include "scene.h"
#include <SFML/Graphics.hpp>
#include "prefabFactory.h"
#include "managers/textureManager.h"
#include "tileMap.h"
#include "systems/movementSystem.h"
#include "systems/renderSystem.h"
 #include <entt/entt.hpp>

class MainScene : public Scene {
public:
    MainScene(EngineContext& context);

    void OnEnter() override;
    void OnExit() override;
    void HandleEvent(const sf::Event& event) override;
    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;
    void InitTilemap();
    void InputTest();

private:
    PrefabFactory prefabs_;
    TileMap tilemap_;
    MovementSystem movementSystem_;
    RenderSystem renderSystem_;
    entt::registry registry_;
};