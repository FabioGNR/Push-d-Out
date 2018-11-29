set(GAME_SRC
        main.cpp
        Game.cpp
        Game.h
        states/GameState.cpp
        states/GameState.h
        states/MainMenuState.cpp
        states/MainMenuState.h
        sprite/reader/SpriteReader.cpp
        sprite/reader/SpriteReader.h
        states/PauseMenuState.cpp
        states/PauseMenuState.h
        states/BaseMenuState.cpp
        states/BaseMenuState.h
        exceptions/NoPlayersFoundException.h
        exceptions/MissingCharacterSpawnException.h
        listeners/JumpContactListener.cpp
        listeners/JumpContactListener.h
        )

set(COMPONENT_SRC
        components/MoveComponent.h
        components/JumpComponent.h
        components/PlayerInputComponent.h
        components/PositionComponent.h
        components/BodyComponent.h
        components/DimensionComponent.h
        components/SpriteComponent.h
        components/EquipmentComponent.h
        components/WeaponComponent.h
        components/InventoryComponent.h
        components/EquipableComponent.h
        components/ProjectileComponent.h
        components/EquipmentSpawnerComponent.h
        components/ItemComponent.h
        components/items/ReverseGravityComponent.h
        components/LifeComponent.h
        components/DestructibleComponent.h)

set(SYSTEM_SRC
        systems/MovementSystem.cpp
        systems/MovementSystem.h
        systems/PlayerInputSystem.cpp
        systems/PlayerInputSystem.h
        systems/PositionSystem.cpp
        systems/PositionSystem.h
        systems/SpriteSystem.cpp
        systems/SpriteSystem.h
        systems/AnimationSystem.cpp
        systems/AnimationSystem.h
        systems/WeaponSystem.cpp
        systems/WeaponSystem.h
        systems/InventorySystem.cpp
        systems/InventorySystem.h
        systems/CameraSystem.cpp
        systems/CameraSystem.h
        systems/EquipmentSpawnSystem.cpp
        systems/EquipmentSpawnSystem.h
        systems/ItemSystem.cpp
        systems/ItemSystem.h
        systems/items/ReverseGravitySystem.cpp
        systems/items/ReverseGravitySystem.h
        systems/GarbageCollectorSystem.cpp
        systems/GarbageCollectorSystem.h
        systems/LifeSystem.cpp
        systems/LifeSystem.h 
        systems/BackgroundSystem.cpp 
        systems/BackgroundSystem.h
        systems/JumpSystem.cpp 
        systems/JumpSystem.h
        systems/ProjectileDestroyerSystem.cpp
        systems/ProjectileDestroyerSystem.h
        )

set(DEFINITION_SRC
        definitions/Action.h
        definitions/WeaponType.h
        definitions/ItemType.h
        )

set(LEVEL_SRC
        level/Theme.h
        level/reader/LevelReader.h
        level/reader/LevelReader.cpp
        level/LevelDomain.cpp
        level/LevelDomain.h
        level/reader/ThemeReader.cpp
        level/reader/ThemeReader.h
        level/reader/Reader.h
        level/reader/Reader.cpp
        level/Theme.cpp
        )

set(EQUIPMENT_SRC
        equipment/InventorySlot.h
        equipment/EquipmentFactory.cpp
        equipment/EquipmentFactory.h
        )

set(HUD_SRC
        hud/HUD.cpp
        hud/HUD.h
        exceptions/PlayerAmountOutOfBoundsException.h
        hud/FpsCounter.cpp
        hud/FpsCounter.h
        )

#more engine stuff
set(BUILDER_SRC
        builders/IBuilder.h
        builders/CharacterBuilder.cpp
        builders/CharacterBuilder.h
        builders/CharacterSpawnGenerator.h
        builders/CharacterSpawnGenerator.cpp
        sprite/SpriteDomain.cpp
        sprite/SpriteDomain.h
        builders/SpriteBuilder.cpp
        builders/SpriteBuilder.h
        )

target_include_directories(
        engine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_executable(PushdOut
        ${GAME_SRC}
        ${COMPONENT_SRC}
        ${SYSTEM_SRC}
        ${DEFINITION_SRC}
        ${LEVEL_SRC}
        ${BUILDER_SRC}
        ${HUD_SRC}
        ${EQUIPMENT_SRC}
        )
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

    foreach (file_i ${THIRD_PARTY_DLLS})
        add_custom_command(
        TARGET PushdOut
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy ${file_i} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )
    endforeach (file_i)
endif ()
