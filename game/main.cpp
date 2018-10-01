#include <events/EventManager.h>
#include <events/SDLEventManager.h>
#include <game/themes/Earth.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <chrono>

#include <engine/graphics/IRenderer.h>
#include <engine/graphics/SDL/SDLRenderVisitor.h>
#include <engine/graphics/SDL/SDLRenderer.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/physics/Body.h>
#include <engine/window/SDLWindow.h>
#include <engine/window/Window.h>
#include <engine/window/WindowProperties.h>
#include <game/themes/Moon.h>

using namespace std::chrono_literals;

static const int UNIT_MULTIPLIER = 2;

int main()
{
    // we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
    std::chrono::nanoseconds timestep(16ms);

    engine::WindowProperties windowProperties{};
    windowProperties.title = "Push'd Out!";
    windowProperties.maximized = false;
    windowProperties.centered = true;
    windowProperties.width = 800;
    windowProperties.height = 480;

    std::unique_ptr<engine::Window> window{ new engine::SDLWindow(windowProperties) };
    std::unique_ptr<engine::EventManager> evtManager{ new engine::SDLEventManager() };
    auto renderer{ new engine::SDLRenderer(*(engine::SDLWindow*)window.get()) };

    using clock = std::chrono::high_resolution_clock;

    std::chrono::nanoseconds lag(0ns);
    auto timeStart = clock::now();
    bool loop = true;

    engine::physics::PhysicsManager pm(/* size of one unit */ 16 * UNIT_MULTIPLIER);

    game::themes::Theme theme = game::themes::Earth{};
    engine::physics::World* world = pm.createWorld(theme.getGravity(), theme.getFriction());

    // falls out of the sky
    world->createDynamicBody(5, 200, 1, 2);
    world->createDynamicBody(6, 200, 1, 2);
    world->createDynamicBody(8, 100, 1, 2);
    world->createDynamicBody(5, 50, 1, 2);
    world->createDynamicBody(15, 30, 2, 2);

    // ground
    world->createStaticBody(0, 1, 100, 1);

    while (loop) {
        auto deltaTime = clock::now() - timeStart;
        timeStart = clock::now();
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);

        loop = evtManager->processEvents();

        // update game logic as lag permits
        while (lag >= timestep) {
            lag -= timestep;

            world->update(); // update at a fixed rate each time
        }

        renderer->clear();

        for (auto body : world->getBodies()) {
            body->applyForce(common::Vector2D(0.1, 0.0), body->getCenterPoint());

            common::Vector2D pos = body->getPosition();
            common::Vector2D size = body->getDimensions();

            engine::RectangleShape shape(pos.x, pos.y, size.x, size.y, engine::Color {255, 255, 255, 100} );
            renderer->draw(shape);
        }

        renderer->show();
    }

    return 0;
}
