#pragma once

#include <entt/entt.hpp>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "GameStateStack.h"
#include <iostream>



class SystemScheduler
{
public:

    using SystemFunc = std::function<void(entt::registry&)>;

    struct ScheduledSystem
    {
        SystemFunc func;
        std::vector<GameState> states;
    };

    std::unordered_map<Stage, std::vector<ScheduledSystem>> systems;

    void add(Stage stage, SystemFunc sys, std::vector<GameState> states = {})
    {
        systems[stage].push_back({sys, states});
    }

    void runOnce(entt::registry& registry)
    {
        auto& stateStack = registry.ctx().get<GameStateStack>();
        GameState state = stateStack.current();
        runStage(Stage::Init, registry, state);
        runStage(Stage::OnEnter, registry, state);
    }

    void run(entt::registry& registry)
    {
        auto& stateStack = registry.ctx().get<GameStateStack>();
        GameState state = stateStack.current();

        // detectar cambio de estado
        
        size_t currentStackSize = stateStack.size();
        std::cout<<currentStackSize<<std::endl;

        if(currentStackSize > lastStackSize)
        {
            runStage(Stage::OnEnter, registry, state);
        }

        else if(currentStackSize < lastStackSize)
        {
            runStage(Stage::OnExit, registry, lastState);
        }
        lastStackSize = currentStackSize;
        lastState = state;
        

        runStage(Stage::Input, registry, state);
        
        runStage(Stage::Update, registry, state);
        
        runStage(Stage::Render, registry, state);
    }

private:
    GameState lastState;
    size_t lastStackSize;
    
    bool isAllowed(GameState state, const std::vector<GameState>& allowed)
    {
        if(allowed.empty())
            return true;

        return std::find(allowed.begin(), allowed.end(), state) != allowed.end();
    }

    void runStage(Stage stage, entt::registry& registry, GameState state)
    {
        auto it = systems.find(stage);

        if(it == systems.end())
            return;

        for(auto& sys : it->second)
        {
            if(isAllowed(state, sys.states))
                sys.func(registry);
        }
    }
};