
#include "engine/events/SDLEventManager.h"
#include "engine/window/SDLWindow.h"
#include "game/level/levelReader/LevelReader.h"
#include "physics/PhysicsManager.h"
#include <events/EventManager.h>
#include <events/SDLEventManager.h>
#include <game/themes/Earth.h>
#include <iostream>
#include <memory>
#include <sstream>

#include "Game.h"
#include <engine/graphics/IRenderer.h>
#include <engine/graphics/SDL/SDLRenderVisitor.h>
#include <engine/graphics/SDL/SDLRenderer.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/physics/Body.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/ui/UISystem.h>
#include <engine/window/SDLWindow.h>
#include <engine/window/Window.h>
#include <engine/window/WindowProperties.h>
#include <game/states/GameState.h>
#include <game/states/MainMenuState.h>
#include <game/themes/Moon.h>

int main()
{
    engine::WindowProperties windowProperties{};
    windowProperties.title = "Push'd Out!";
    windowProperties.maximized = false;
    windowProperties.centered = true;
    windowProperties.width = 800;
    windowProperties.height = 480;

    auto game = std::make_unique<game::Game>(windowProperties);

    auto menuState = std::make_shared<game::MainMenuState>(*game);
    // auto gameState = std::make_shared<game::GameState>();

    game->next(menuState);
    // game->next(gameState);
    game->init();
    game->run();

    return 0;
}
