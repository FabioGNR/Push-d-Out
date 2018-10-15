#include "engine/events/EventManager.h"
#include "engine/window/SDLWindow.h"
#include "physics/PhysicsManager.h"
#include "InputObserver.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
int main(int, char**)
{
    engine::WindowProperties windowProperties {};
    windowProperties.title = "Push'd out!";
    windowProperties.maximized = true;
    windowProperties.centered = true;
    windowProperties.width = 640;
    windowProperties.height = 480;
    std::unique_ptr<engine::Window> window { new engine::SDLWindow(windowProperties) };
    //PhysicsManager pm {};
    //pm.doPhysics();

    bool runGame = true;
    engine::events::EventManager em;
    auto* im = em.getInput();
    auto* io = new InputObserver();
    im->subscribe(io);

    while (runGame) {
        runGame = em.getEvents();
        im->notify();
    }
    return 0;
}