#include "../engine/core/engine.h"
#include "game.h"

void runGame(IGame& game, Engine& engine) {
    game.init();

    while (engine.window().isOpen()) {
        float dt = engine.getDeltaTime();

        game.handleInput();
        game.update(dt);
        game.render();

        engine.window().display();
    }
}

int main()
{
    Engine engine(1280, 720, "SFML Game");
    Game game(engine);
    runGame(game, engine);
    return 0;
}

