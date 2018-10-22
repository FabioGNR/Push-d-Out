set(TEST_SRC
        test_main.cpp
        engine/common/Vector2D_test.cpp
        engine/input/KeyMap_test.cpp
        )

add_executable(tests ${TEST_SRC})
target_link_libraries(tests engine)