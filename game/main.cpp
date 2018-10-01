#include <iostream>
#include <memory>
#include <thread>

#include <engine/events/SDLEventManager.h>
#include <engine/graphics/Color.h>
#include <engine/graphics/IRenderer.h>
#include <engine/graphics/SDL/SDLRenderer.h>
#include <engine/graphics/drawable/Font.h>
#include <engine/graphics/drawable/LineShape.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/graphics/drawable/Sprite.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/window/SDLWindow.h>

int main()
{
    engine::WindowProperties windowProperties{};
    windowProperties.title = "Push'd out!";
    windowProperties.maximized = false;
    windowProperties.centered = true;
    windowProperties.width = 640;
    windowProperties.height = 480;
    std::unique_ptr<engine::Window> window{ new engine::SDLWindow(windowProperties) };
    std::unique_ptr<engine::EventManager> evtManager{ new engine::SDLEventManager() };
    std::unique_ptr<engine::IRenderer> renderer{ new engine::SDLRenderer((engine::SDLWindow&)*window) };

    engine::RectangleShape shape(620 / 2, 480 / 2, 300, 300, Color{ 0, 0, 255, 0 });
    engine::LineShape line(30, 100, 30, 100);
    engine::Font font(
        "assets/fonts/Pixeled.ttf", "Hello, World!", 80,
        Color{ 0, 255, 0, 0 },
        50, 50);

    engine::Sprite sprite("assets/sprites/feelsgoodman.png", 50, 250, 0, 0, .2f);

    bool runGame = true;
    while (runGame) {
        runGame = evtManager->processEvents();
        renderer->clear();

        renderer->draw(shape);
        renderer->draw(line);
        renderer->draw(font);
        renderer->draw(sprite);

        renderer->show();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
