#pragma once

#include <entt/entt.hpp>
#include <functional>
#include <vector>
#include <unordered_map>

enum class Stage
{
    Init,
    Input,
    Update,
    Render
};

class SystemScheduler
{
public:

    using SystemFunc = std::function<void(entt::registry&)>;

    std::unordered_map<Stage, std::vector<SystemFunc>> systems;

    void add(Stage stage, SystemFunc sys)
    {
        systems[stage].push_back(sys);
    }

    void runOnce(entt::registry& registry)
    {
        for(auto &sys : systems[Stage::Init]) sys(registry);
    }

    void run(entt::registry& registry)
    {
        for(auto &sys : systems[Stage::Input]) sys(registry);
        for(auto &sys : systems[Stage::Update]) sys(registry);
        for(auto &sys : systems[Stage::Render]) sys(registry);
    }
};