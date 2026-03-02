#pragma once
#include <SFML/Graphics.hpp>

class IGame {
public:
    virtual ~IGame() = default;
    
    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
};