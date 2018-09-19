set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(ECS_SRC
        ecs/Entity.h ecs/Entity.cpp
        ecs/EntityManager.h ecs/EntityManager.cpp
        ecs/Component.h ecs/Component.cpp
        ecs/ComponentManager.h ecs/ComponentManager.cpp
        ecs/World.h
        )

add_library(engine ${ECS_SRC})
target_link_libraries(engine ${SDL2_LIBRARY})