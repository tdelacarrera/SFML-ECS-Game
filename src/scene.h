#pragma once

#include <SFML/Graphics.hpp>

struct EngineContext; 

class Scene {
    
public:
    Scene(EngineContext& context) : context_(context) {}

    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void HandleEvent(const sf::Event& event) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

protected:
    EngineContext& context_;
};