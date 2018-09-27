#include "engine/events/SDLEventManager.h"
#include "engine/window/SDLWindow.h"
#include "game/level/levelReader/LevelReader.h"
#include "physics/PhysicsManager.h"
#include <iostream>
#include <memory>

int main()
{
    engine::WindowProperties windowProperties {};
    windowProperties.title = "Push'd out!";
    windowProperties.maximized = true;
    windowProperties.centered = true;
    windowProperties.width = 640;
    windowProperties.height = 480;
    std::unique_ptr<engine::Window> window { new engine::SDLWindow(windowProperties) };
    PhysicsManager pm {};
    pm.doPhysics();
    std::unique_ptr<engine::EventManager> evtManager { new engine::SDLEventManager() };

    json j = levelReader::readJSON("assets\\levels\\base_level.JSON");
    std::cout << "JSON: " << j << std::endl;
    level l = levelReader::getLevel(j);
    std::cout << "level: " << l.name << std::endl;

    bool runGame = true;
    while (runGame) {
        runGame = evtManager->processEvents();
    }
    return 0;
}