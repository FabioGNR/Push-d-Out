set(TEST_SRC
        test_main.cpp
        engine/common/Vector2D_test.cpp
        engine/input/KeyMap_test.cpp
        engine/ecs/ecs_test.cpp)

target_include_directories(
        engine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_executable(tests ${TEST_SRC})
target_link_libraries(tests engine)