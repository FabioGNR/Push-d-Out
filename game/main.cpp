#include "Game.h"
#include <game/states/MainMenuState.h>

int main()
{
    engine::WindowProperties windowProperties{};
    windowProperties.title = "Push'd Out!";
    windowProperties.maximized = false;
    windowProperties.centered = true;
    windowProperties.width = 1280;
    windowProperties.height = 768;

    auto game = std::make_unique<game::Game>(windowProperties);
    auto menuState = std::make_unique<game::MainMenuState>(*game);

    game->next(std::move(menuState));
    game->init();
    game->run();

    return 0;
}
