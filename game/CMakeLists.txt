set(GAME_SRC
    main.cpp
)

set(COMPONENT_SRC
    components/MoveComponent.h
    components/PlayerInputComponent.h
    components/JumpComponent.h
    components/PositionComponent.h
    components/BodyComponent.h
    components/DimensionComponent.h
    components/SpriteComponent.h
)

set(SYSTEM_SRC
    systems/MoveSystem.cpp
    systems/MoveSystem.h
    systems/PlayerInputSystem.cpp
    systems/PlayerInputSystem.h
    systems/JumpSystem.cpp
    systems/JumpSystem.h
    systems/PositionSystem.cpp
    systems/PositionSystem.h
    systems/BodySystem.cpp
    systems/BodySystem.h
    systems/DimensionSystem.cpp
    systems/DimensionSystem.h
    systems/SpriteSystem.cpp
    systems/SpriteSystem.h
)

set(DEFINITION_SRC
    definitions/Action.h
    definitions/Body.h
)

set(THEMES_SRC
    themes/Earth.h
    themes/Moon.h
    themes/Theme.h
    themes/Theme.cpp
)

#more engine stuff
add_executable(PushdOut ${GAME_SRC} ${COMPONENT_SRC} ${SYSTEM_SRC} ${DEFINITION_SRC} ${THEMES_SRC})

target_link_libraries(PushdOut engine)

#Copy asset folder to bin folder
add_custom_command(
    TARGET PushdOut
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

#If needed, copy some DLLs over to bin folder
if (MSYS OR MINGW)
    get_filename_component(COMPILER_BIN_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)

    set(THIRD_PARTY_DLLS
        ${COMPILER_BIN_PATH}/libBox2D.dll
        ${COMPILER_BIN_PATH}/SDL2.dll
        ${COMPILER_BIN_PATH}/libstdc++-6.dll
        ${COMPILER_BIN_PATH}/libgcc_s_seh-1.dll
        ${COMPILER_BIN_PATH}/libwinpthread-1.dll
    )

    foreach(file_i ${THIRD_PARTY_DLLS})
        add_custom_command(
            TARGET PushdOut
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${file_i} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        )
    endforeach(file_i)
endif()
