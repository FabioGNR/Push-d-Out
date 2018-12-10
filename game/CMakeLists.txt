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
        states/LevelEditorState.cpp
        states/LevelEditorState.h
        states/LevelEditorMenuState.cpp
        states/LevelEditorMenuState.h
        exceptions/NoPlayersFoundException.h
        exceptions/MissingCharacterSpawnException.h
        exceptions/PlayerAmountOutOfBoundsException.h
        listeners/JumpContactListener.cpp
        listeners/JumpContactListener.h
        states/OptionMenuState.cpp
        states/OptionMenuState.h
        states/LevelSelectorState.cpp
        states/LevelSelectorState.h
        listeners/ProjectileContactListener.cpp 
        listeners/ProjectileContactListener.h
        listeners/PortalContactListener.cpp 
        listeners/PortalContactListener.h
        listeners/ProjectilePortalContactListener.h
        listeners/ProjectilePortalContactListener.cpp
        states/ScoreState.cpp
        states/ScoreState.h
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
        components/PortalComponent.h
        components/WeaponComponent.h
        components/InventoryComponent.h
        components/EquipableComponent.h
        components/ProjectileComponent.h
        components/EquipmentSpawnerComponent.h
        components/ItemComponent.h
        components/items/ReverseGravityComponent.h
        components/LifeComponent.h
        components/DestructibleComponent.h
        components/TeleportComponent.h
        components/DirectionComponent.h
        components/PunchComponent.h
        )

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
        systems/CooldownSystem.cpp
        systems/CooldownSystem.h
        systems/TeleportSystem.cpp
        systems/TeleportSystem.h
        systems/ScoreSystem.cpp
        systems/ScoreSystem.h
        systems/PunchingSystem.cpp
        systems/PunchingSystem.h
        )

set(DEFINITION_SRC
        definitions/Action.h
        definitions/WeaponType.h
        definitions/ProjectileType.h
        definitions/ItemType.h
        )

set(LEVEL_SRC
        level/LevelDomain.cpp
        level/LevelDomain.h
        level/Theme.cpp
        level/Theme.h
        level/editor/Editor.cpp
        level/editor/Editor.h
        level/editor/TileType.h
        level/editor/ui/Cursor.cpp
        level/editor/ui/Cursor.h
        level/editor/ui/ITile.h
        level/editor/ui/KeyboardScreen.cpp
        level/editor/ui/KeyboardScreen.h
        level/editor/ui/PlatformTile.cpp
        level/editor/ui/PlatformTile.h
        level/editor/ui/SpawnTile.cpp
        level/editor/ui/SpawnTile.h
        level/editor/ui/TileSet.cpp
        level/editor/ui/TileSet.h
        level/editor/ui/TileSpriteSelectionScrollbar.cpp
        level/editor/ui/TileSpriteSelectionScrollbar.h
        level/reader/LevelReader.cpp
        level/reader/LevelReader.h
        level/reader/Reader.cpp
        level/reader/Reader.h
        level/reader/ThemeReader.cpp
        level/reader/ThemeReader.h
        )

set(EQUIPMENT_SRC
        equipment/InventorySlot.h
        equipment/EquipmentFactory.cpp
        equipment/EquipmentFactory.h
        )

set(HUD_SRC
        hud/HUD.cpp
        hud/HUD.h
        hud/FpsCounter.cpp
        hud/FpsCounter.h
        hud/ui/ItemBubble.cpp 
        hud/ui/ItemBubble.h 
        hud/ui/PlayerInfo.cpp 
        hud/ui/PlayerInfo.h 
        hud/ui/LifeBar.cpp 
        hud/ui/LifeBar.h
        )

set(CONFIG_SRC
        config/ConfigurationRepository.h
        config/ConfigurationRepository.cpp
        exceptions/CanNotSaveConfigException.h
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

find_package(Boost COMPONENTS
        filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

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
        ${CONFIG_SRC}
        )

target_link_libraries(PushdOut engine ${Boost_LIBRARIES})

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
