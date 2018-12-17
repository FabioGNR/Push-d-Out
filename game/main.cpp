#include "Game.h"
#include <game/states/MainMenuState.h>

int main()
{
    game::Game::DEBUG = true;
    engine::WindowProperties windowProperties{};
    windowProperties.title = "Push'd Out!";
    windowProperties.maximized = true;
    windowProperties.centered = true;
    windowProperties.width = 1280;
    windowProperties.height = 768;

    auto game = std::make_unique<game::Game>(windowProperties);
    game->next(std::make_unique<game::MainMenuState>(*game));
    game->init();
    game->run();

    return 0;
}
