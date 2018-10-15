#include "Game.h"
#include "game/level/levelReader/LevelReader.h"
#include "physics/PhysicsManager.h"
#include <engine/graphics/SDL/SDLRenderVisitor.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/physics/Body.h>
#include <engine/ui/UISystem.h>
#include <game/states/GameState.h>
#include <game/states/MainMenuState.h>
#include <game/themes/Earth.h>
#include <game/themes/Moon.h>
#include <sstream>
#include <thread>

int main()
{
    engine::WindowProperties windowProperties{};
    windowProperties.title = "Push'd Out!";
    windowProperties.maximized = false;
    windowProperties.centered = true;
    windowProperties.width = 1280;
    windowProperties.height = 768;

    auto game = std::make_unique<game::Game>(windowProperties);
    //    auto menuState = std::make_shared<game::MainMenuState>(*game);
    auto gameState = std::make_shared<game::GameState>(*game);

    //    game->next(menuState);
    game->next(gameState);
    game->init();
    game->run();

    return 0;
}
