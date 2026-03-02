#include "game.h"
#include "gameHUD.h"

Game::Game(Engine& engine) 
    : engine_(engine)
{
}

void Game::init()
{
    engine_.textures().load("grass",    "content/textures/tile1.png");
    engine_.textures().load("wall",     "content/textures/tile2.png");
    engine_.textures().load("colonist", "content/textures/colonist.png");

    engine_.sounds().load("walk", "content/sounds/walk.wav");
    engine_.sounds().load("test", "content/sounds/test.ogg");

    engine_.music().load("music", "content/music/music2.ogg");
    engine_.music().play("music");

    engine_.setGameView();

    engine_.gui().setView(std::make_unique<GameHUD>());

    prefabs_.spawnColonist(registry_, {10.f, 10.f});
    prefabs_.spawnEnemy(registry_,   {10.f, 40.f});

    engine_.tilemap().setTileSize(16);
    engine_.tilemap().registerTile(0, TileDefinition{"grass"});
    engine_.tilemap().registerTile(1, TileDefinition{"wall"});

    initTilemap();
}

void Game::handleInput()
{
    while (const std::optional event = engine_.window().pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            engine_.window().close();

        engine_.gui().processEvent(*event);
    }
}

void Game::update(float dt)
{
    movement_.update(registry_, engine_.sounds(), dt);
    engine_.input().update();
    inputTest();
}

void Game::render()
{
    engine_.window().clear(sf::Color(18, 18, 28));

    engine_.setGameView();

    engine_.tilemap().render(engine_.window(), engine_.textures());

    render_.draw(registry_, engine_.textures(), engine_.window());

    engine_.gui().render();
}


void Game::initTilemap()
{
    size_t groundLayer = engine_.tilemap().addLayer("ground", 0);
    size_t wallLayer = engine_.tilemap().addLayer("wallLayer", 1);

    engine_.tilemap().setTile(groundLayer, 2, 2, 0);
    engine_.tilemap().setTile(groundLayer, 6, 2, 0);

    for (int y = 0; y < engine_.tilemap().getHeight(); y++) {
        for (int x = 0; x < engine_.tilemap().getWidth(); x++) {
            engine_.tilemap().setTile(groundLayer, x, y, 0);
        }
    }

    for (int x = 5; x < 30; x++) {
        engine_.tilemap().setTile(wallLayer, x, 5, 1);
    }
    for (int y = 5; y < 50; y++) {
        engine_.tilemap().setTile(wallLayer, 4, y, 1);
    }
}

void Game::inputTest()
{
    if (engine_.input().isActionJustPressed(Action::MoveRight)) std::cout <<"Move Right"<<std::endl;
    if (engine_.input().isActionJustReleased(Action::MoveLeft)) std::cout <<"Move Left"<<std::endl;
    if (engine_.input().isActionActive(Action::MoveUp)) std::cout <<"Move Up"<<std::endl;
    if (engine_.input().isActionActive(Action::MoveDown)) std::cout <<"Move Down"<<std::endl;
}