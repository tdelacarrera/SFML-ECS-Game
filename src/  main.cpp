#include "core/Game.hpp"
#include "scenes/MainMenuScene.hpp"

int main()
{
    Game game;

    game.getSceneManager().changeScene<MainMenuScene>();

    game.run();
}