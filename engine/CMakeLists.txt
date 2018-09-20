set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/engine/external/Box2D")

find_package(SDL2 REQUIRED)
find_package(BOX2D REQUIRED)

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

# more engine stuff

add_library(engine ${ECS_SRC} ${GRAPHICS_SRC} ${PHYSICS_SRC})
target_link_libraries(engine ${SDL2_LIBRARY} ${BOX2D_LIBRARY})