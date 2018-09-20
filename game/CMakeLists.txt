set(GAME_SRC
        main.cpp
        )

add_executable(SDL_Game ${GAME_SRC})
target_link_libraries(SDL_Game engine)