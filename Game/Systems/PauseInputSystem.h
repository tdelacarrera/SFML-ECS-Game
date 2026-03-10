#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/GameState/GameStateStack.h"


inline void PauseInputSystem(entt::registry& registry)
{
    auto& input = registry.ctx().get<InputManager>();
    auto& states = registry.ctx().get<GameStateStack>();

    if(input.justPressed("pause"))
    {
        GameState state = states.current();

        if(state == GameState::Playing){
            
            states.push(GameState::Paused);
        }
        else if(state == GameState::Paused)
        {
            states.pop();
        }
    }
}