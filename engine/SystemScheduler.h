#pragma once

#include <entt/entt.hpp>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>

enum class Stage
{
    Init,
    Input,
    Update,
    Render
};

enum class GameState
{
    Menu,
    Playing,
    Paused
};

struct GameStateStack
{
    std::vector<GameState> stack;

    GameState current() const
    {
        return stack.empty() ? GameState::Menu : stack.back();
    }

    void push(GameState s)
    {
        stack.push_back(s);
    }

    void pop()
    {
        if(!stack.empty())
            stack.pop_back();
    }

    void set(GameState s)
    {
        stack.clear();
        stack.push_back(s);
    }
};

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
        runStage(Stage::Init, registry, stateStack.current());
    }

    void run(entt::registry& registry)
    {
        auto& stateStack = registry.ctx().get<GameStateStack>();
        GameState state = stateStack.current();

        runStage(Stage::Input, registry, state);
        runStage(Stage::Update, registry, state);
        runStage(Stage::Render, registry, state);
    }

private:

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