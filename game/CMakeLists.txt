set(GAME_SRC
    main.cpp
)

add_executable(PushdOut ${GAME_SRC})

target_link_libraries(PushdOut engine)