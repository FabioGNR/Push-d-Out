set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(ECS_SRC
        )

set(GRAPHICS_SRC
        )

# more engine stuff

add_library(engine ${ECS_SRC} ${GRAPHICS_SRC})
target_link_libraries(engine ${SDL2_LIBRARY})