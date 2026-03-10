#include "../Engine/Engine.h"
#include "Game.h"

int main()
{
    Engine engine;

    engine.init();

    Game game;

    game.load(engine);

    engine.run();
}