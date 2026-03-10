#pragma once

enum class Stage
{
    Init,
    OnEnter,
    Input,
    Update,
    Render,
    OnExit
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

    void push(GameState state)
    {
        stack.push_back(state);
    }

    void pop()
    {
        if(!stack.empty())
            stack.pop_back();
    }

    void set(GameState state)
    {
        stack.clear();
        stack.push_back(state);
    }

    size_t size() const
    {
        return stack.size();
    }
};