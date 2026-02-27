#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <entt/entt.hpp>
#include "systems/movementSystem.h"
#include "systems/renderSystem.h"


class Game
{

    public:
        Game();
        void Run();

        bool IsRunning() const;
        void ProcessEvents();
        void Update();
        void Render();

    private:
        sf::RenderWindow window_;
        entt::registry registry_;
        sf::Clock clock_;

        sf::Texture tex_colonist_;
        sf::Texture tex_grass_;
        sf::Texture tex_wall_;

        entt::entity player_;

        MovementSystem movementSystem;
        RenderSystem renderSystem;

        void InitEntities();
};