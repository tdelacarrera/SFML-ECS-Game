#pragma once
#include <SFML/Graphics.hpp>
#include "../graphics/textureManager.h"
#include "../graphics/tileMap.h"
#include "../audio/soundManager.h"
#include "../audio/musicManager.h"
#include "../gui/guiManager.h"
#include "../input/inputManager.h"

class Engine final {
public:
    explicit Engine(unsigned int width = 1280, unsigned int height = 720, const std::string& title = "Game");

    sf::RenderWindow& window() noexcept { return window_; }
    const sf::RenderWindow& window() const noexcept { return window_; }
    sf::View& view() noexcept { return view_; }
    TextureManager& textures() noexcept { return textures_; }
    SoundManager& sounds() noexcept { return sounds_; }
    MusicManager& music() noexcept { return music_; }
    TileMap& tilemap() noexcept { return tilemap_; }
    GuiManager& gui() noexcept { return gui_; }
    InputManager& input() noexcept { return input_; }
    float getDeltaTime();
    void setGameView();

private:
    sf::RenderWindow window_;
    sf::Clock clock_;
    sf::View view_;

    TextureManager textures_;
    SoundManager sounds_;
    MusicManager music_;
    TileMap tilemap_;
    GuiManager gui_;
    InputManager input_;
};