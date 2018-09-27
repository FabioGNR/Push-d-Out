#include "engine/events/SDLEventManager.h"
#include "engine/window/SDLWindow.h"
#include "physics/PhysicsManager.h"
#include "level/levelReader/levelReader.h"
#include <iostream>
#include <memory>

int main()
{
    engine::WindowProperties windowProperties{};
    windowProperties.title = "Push'd out!";
    windowProperties.maximized = true;
    windowProperties.centered = true;
    windowProperties.width = 640;
    windowProperties.height = 480;
    std::unique_ptr<engine::Window> window{ new engine::SDLWindow(windowProperties) };
    PhysicsManager pm{};
    pm.doPhysics();
    std::unique_ptr<engine::EventManager> evtManager{ new engine::SDLEventManager() };

    json j = levelReader::readJSON("D:\\Users\\Joris\\Documents\\HBO-ICT\\Jaar 4\\Minor\\Project\\Push_d_out\\assets\\levels\\base_level.JSON");
    std::cout << "JSON: " << j << std::endl;
    level l = levelReader::getLevel(j);
    std::cout << "level: " << l.name << std::endl;

    bool runGame = true;
    while (runGame) {
        runGame = evtManager->processEvents();
    }
    return 0;
}