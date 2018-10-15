set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(SDL2_BUILDING_LIBRARY ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Box2D REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${BOX2D_INCLUDE_DIR})

set(ENGINE_GAME_SRC
        game/IGame.h
        game/IGame.cpp
        game/State.h
        )

set(COMMON_SRC
        common/Vector2D.h
        )

set(ECS_SRC
        ecs/Entity.h
        ecs/Entity.cpp
        ecs/EntityManager.h
        ecs/EntityManager.cpp
        ecs/Component.h
        ecs/Component.cpp
        ecs/ComponentManager.h
        ecs/ComponentManager.cpp
        ecs/World.h
        ecs/World.cpp
        ecs/System.h
        ecs/SystemManager.cpp
        ecs/SystemManager.h
        )

set(GRAPHICS_SRC
        graphics/IRenderer.h
        graphics/IRenderVisitor.h
        graphics/IGraphicsElement.h
        graphics/SDL/SDLRenderVisitor.cpp
        graphics/SDL/SDLRenderVisitor.h
        graphics/SDL/SDLRenderer.cpp
        graphics/SDL/SDLRenderer.h
        graphics/drawable/RectangleShape.cpp
        graphics/drawable/RectangleShape.h
        graphics/drawable/LineShape.cpp
        graphics/drawable/LineShape.h
        graphics/drawable/Font.cpp
        graphics/drawable/Font.h
        graphics/drawable/Sprite.cpp
        graphics/drawable/Sprite.h
        graphics/Color.h
        )

set(PHYSICS_SRC
        physics/PhysicsManager.h
        physics/PhysicsManager.cpp
        physics/World.h
        physics/World.cpp
        physics/Body.h
        physics/DynamicBody.cpp
        physics/DynamicBody.h
        physics/StaticBody.h
        physics/StaticBody.cpp
        physics/Body.cpp
        )

set(INPUT_SRC
        input/InputManager.h
        input/InputManager.cpp
        input/Keys.h
        input/IObserver.h
        input/SDLKeyMap.cpp
        input/SDLKeyMap.h
        )

set(EVENTS_SRC
        events/SDLEventAdapter.cpp
        events/SDLEventAdapter.h
        events/EventManager.cpp
        events/EventManager.h
        events/models/IControlEvent.h
        events/models/IOtherEvent.h
        events/models/QuitEvent.cpp
        events/models/QuitEvent.h
        events/models/UnknownEvent.cpp
        events/models/UnknownEvent.h
        events/models/IEvent.h
        events/models/KeyEvent.cpp
        events/models/KeyEvent.h
        )

set(WINDOW_SRC
        window/SDLWindow.h
        window/SDLWindow.cpp
        window/Window.h
        window/WindowProperties.h
        )

set(DEFINITION_SRC
        definitions/SystemPriority.h
        )

set(EXCEPTION_SRC
        )


set(UI_SRC
        ui/Frame.cpp
        ui/Frame.h
        ui/UISystem.cpp
        ui/UISystem.h
        ui/components/Component.h
        ui/DrawContext.h
        ui/components/Button.cpp
        ui/components/Button.h
        ui/components/IAction.h
        ui/components/OpenFrameAction.cpp
        ui/components/OpenFrameAction.h
        ui/components/Label.cpp
        ui/components/Label.h
        ui/components/FlowDirection.h
        ui/components/LayoutAnchor.h
        ui/components/WrappedComponent.h
        ui/components/ComponentSize.h
        ui/components/ComponentSizeType.h
        ui/components/StackPanel.cpp
        ui/components/StackPanel.h
        ui/components/LayoutPanel.cpp
        ui/components/LayoutPanel.h
        ui/components/ComponentSize.cpp
        ui/UIRenderer.h
        ui/components/TextComponent.h
        ui/components/TextComponent.cpp ui/components/ComponentPanel.h
        )

# more engine stuff
add_library(engine
        ${ENGINE_GAME_SRC}
        ${ECS_SRC}
        ${INPUT_SRC}
        ${GRAPHICS_SRC}
        ${COMMON_SRC}
        ${PHYSICS_SRC}
        ${WINDOW_SRC}
        ${EVENTS_SRC}
        ${EXCEPTION_SRC}
        ${UI_SRC}
        ${DEFINITION_SRC})
target_link_libraries(engine ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${BOX2D_LIBRARY})
