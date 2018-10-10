#include "engine/EventHandling/EventManager.h"
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
    EventManager em;
    InputManager* im = em.getInput();
    InputObserver* io = new InputObserver();
    im->subscribe(io);

    while (runGame) {
        runGame = em.getEvents();
        ///std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        im->notify();
        //runGame = evtManager->processEvents();
    }
    return 0;
}