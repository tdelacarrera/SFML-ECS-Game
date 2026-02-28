#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <entt/entt.hpp>
#include "systems/movementSystem.h"
#include "systems/renderSystem.h"
#include "utils/textureCache.h"
#include "utils/soundManager.h"
#include "utils/musicManager.h"



class Game
{

    public:
        Game();
        void Run();

        bool isRunning() const;
        void processEvents();
        void update();
        void render();

    private:
        sf::RenderWindow window_;
        entt::registry registry_;
        sf::Clock clock_;

        TextureCache textures_;
        SoundManager sound_;
        MusicManager music_;

        entt::entity player_;

        MovementSystem movementSystem;
        RenderSystem renderSystem;

        void initEntities();
};