#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <entt/entt.hpp>
#include "systems/movementSystem.h"
#include "systems/renderSystem.h"
#include "utils/textureCache.h"


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

        TextureCache textures_;

        entt::entity player_;

        MovementSystem movementSystem;
        RenderSystem renderSystem;

        void InitEntities();
};