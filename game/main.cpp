#include "Game.h"

#include <engine/input/KeyMap.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <engine/ui/components/CustomAction.h>

#include <game/states/GameState.h>
#include <game/states/MainMenuState.h>
#include <game/states/PauseMenuState.h>
#include <game/themes/Earth.h>

int main()
{
    engine::WindowProperties windowProperties{};
    windowProperties.title = "Push'd Out!";
    windowProperties.maximized = false;
    windowProperties.centered = true;
    windowProperties.width = 1280;
    windowProperties.height = 768;

    auto game = std::make_unique<game::Game>(windowProperties);

    auto menuState = std::make_shared<game::MainMenuState>(game->getInputManager());

    menuState->onStartClick([&]() {
        auto gameState = std::make_shared<game::GameState>(
            game->getScreenSize(),
            game::themes::Earth{},
            std::make_unique<engine::sound::SDLSoundManager>(),
            game->getInputManager());

        gameState->onInput([&](engine::input::KeyMap keyMap, engine::events::Subscription<engine::input::KeyMap>&) {
            if (keyMap.hasKeyState(engine::input::Keys::ESCAPE, engine::input::KeyStates::PRESSED)) {
                auto pauseMenu = std::make_shared<game::PauseMenuState>(game->getInputManager());
                game->next(pauseMenu);
            }
        });
        game->next(gameState);
    });

    menuState->onQuitClick([&]() {
        game->stop();
    });

    game->next(menuState);
    game->init();
    game->run();

    return 0;
}
