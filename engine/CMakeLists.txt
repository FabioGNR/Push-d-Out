set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(SDL2_BUILDING_LIBRARY)
find_package(SDL2 REQUIRED)
find_package(Box2D REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE_DIR})

set(ECS_SRC
        ecs/Entity.h ecs/Entity.cpp
        ecs/EntityManager.h ecs/EntityManager.cpp
        ecs/Component.h ecs/Component.cpp
        ecs/ComponentManager.h ecs/ComponentManager.cpp
        ecs/World.h
        )

set(GRAPHICS_SRC
        )

set(PHYSICS_SRC
        physics/PhysicsManager.h
        physics/PhysicsManager.cpp
        )

set(INPUT_SRC
        input/InputManager.cpp
        input/InputManager.h
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

# more engine stuff
add_library(engine ${ECS_SRC} ${GRAPHICS_SRC} ${PHYSICS_SRC} ${WINDOW_SRC} ${EVENTS_SRC} ${INPUT_SRC})
target_link_libraries(engine ${SDL2_LIBRARY} ${BOX2D_LIBRARY})