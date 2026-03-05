#pragma once


#include <SFML/Graphics/RenderWindow.hpp>
#include "managers/sceneManager.h"
#include "managers/inputManager.h" 
#include "managers/textureManager.h"
#include "managers/soundManager.h"
#include "managers/musicManager.h"


struct EngineContext{

    InputManager input_;
    TextureManager textures_;
    SoundManager sounds_;
    MusicManager music_;
    SceneManager sceneManager_;

    EngineContext(sf::RenderWindow& window) : input_(window) {}
};

