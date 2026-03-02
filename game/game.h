#pragma once

#include <entt/entt.hpp>
#include "../engine/core/engine.h"
#include "../engine/core/IGame.h"
#include "prefabFactory.h"
#include "systems/movementSystem.h"
#include "systems/renderSystem.h"

class GameHUD;

class Game final : public IGame {
public:
    explicit Game(Engine& engine);

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void render() override;
    bool isRunning() const override { return engine_.window().isOpen(); }

private:
    Engine& engine_;
    entt::registry registry_;

    PrefabFactory prefabs_;
    MovementSystem movement_;
    RenderSystem render_;
};