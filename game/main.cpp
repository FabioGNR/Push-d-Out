#include "engine/EventHandling/EventManager.h"
#include "engine/window/SDLWindow.h"
#include "physics/PhysicsManager.h"
#include <iostream>
#include <memory>

int main(int, char**)
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

    bool runGame = true;
    EventManager em;

    while (runGame) {
        runGame = em.getEvents();
        //runGame = evtManager->processEvents();
    }
    return 0;
}