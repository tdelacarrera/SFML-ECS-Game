#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <entt/entt.hpp>
#include "systems/movementSystem.h"
#include "systems/renderSystem.h"
#include "utils/textureManager.h"
#include "utils/soundManager.h"
#include "utils/musicManager.h"
#include "utils/tileMap.h"
#include "utils/entityFactory.h"

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
        sf::View view_;
        entt::registry registry_;
        sf::Clock clock_;

        TextureManager textures_;
        SoundManager sound_;
        MusicManager music_;
        TileMap tilemap_;
        EntityFactory entities_;

        entt::entity player_;

        MovementSystem movementSystem_;
        RenderSystem renderSystem_;
};