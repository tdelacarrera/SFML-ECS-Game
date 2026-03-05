#pragma once

#include "engineContext.h"
#include "engineConfig.h"

class Engine {
public:
    Engine();
    ~Engine();

    void Run();

private:
    void Init();
    void ProcessEvents();
    void Update(float dt);
    void Render();
    void Cleanup();

private:
    EngineConfig config_;
    sf::RenderWindow window_;
    EngineContext context_;
    sf::Clock clock_;
    bool running_ = true;
};