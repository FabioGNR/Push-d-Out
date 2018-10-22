set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(SDL2_BUILDING_LIBRARY ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(Box2D REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
include_directories(${BOX2D_INCLUDE_DIR})

set(ENGINE_GAME_SRC
        game/IGame.h
        game/IGame.cpp
        game/State.h
        )

set(COMMON_SRC
        common/Vector2D.h
        common/ResourceCache.h
        )

set(ECS_SRC
        ecs/Entity.h
        ecs/Entity.cpp
        ecs/EntityManager.h
        ecs/EntityManager.cpp
        ecs/Component.h
        ecs/Component.cpp
        ecs/ComponentManager.h
        ecs/ComponentManager.cpp
        ecs/World.h
        ecs/World.cpp
        ecs/System.h
        ecs/SystemManager.cpp
        ecs/SystemManager.h
        )

set(GRAPHICS_SRC
        graphics/IRenderer.h
        graphics/IRenderVisitor.h
        graphics/IGraphicsElement.h
        graphics/SDL/SDLRenderVisitor.cpp
        graphics/SDL/SDLRenderVisitor.h
        graphics/SDL/SDLRenderer.cpp
        graphics/SDL/SDLRenderer.h
        graphics/drawable/RectangleShape.cpp
        graphics/drawable/RectangleShape.h
        graphics/drawable/LineShape.cpp
        graphics/drawable/LineShape.h
        graphics/drawable/Font.cpp
        graphics/drawable/Font.h
        graphics/drawable/Sprite.cpp
        graphics/drawable/Sprite.h
        graphics/Color.h
        graphics/Camera.h
        graphics/Camera.cpp
        )

set(PHYSICS_SRC
        physics/PhysicsManager.h
        physics/PhysicsManager.cpp
        physics/World.h
        physics/World.cpp
        physics/Body.h
        physics/DynamicBody.cpp
        physics/DynamicBody.h
        physics/StaticBody.h
        physics/StaticBody.cpp
        physics/Body.cpp
        physics/Collision.cpp physics/Collision.h)

set(INPUT_SRC
        input/InputManager.h
        input/InputManager.cpp
        input/Keys.h
        input/SDLKeys.cpp
        input/SDLKeys.h
        input/KeyMap.cpp
        input/KeyMap.h
        input/KeyStates.h)

set(EVENTS_SRC
        events/IEventHandler.h
        events/SDLEventHandler.cpp
        events/SDLEventHandler.h
        events/EventManager.cpp
        events/EventManager.h
        events/models/IEvent.h
        events/models/IControlEvent.h
        events/models/KeyUpEvent.h
        events/models/KeyDownEvent.h
        events/models/QuitEvent.h
        events/models/Subscription.h
        events/models/ControllerEvent.h)

set(WINDOW_SRC
        window/SDLWindow.h
        window/SDLWindow.cpp
        window/Window.h
        window/WindowProperties.h
        )

set(SOUND_SRC
        sound/Sound.cpp
        sound/Sound.h
        sound/ISoundManager.h
        sound/SDL/SDLSoundManager.cpp
        sound/SDL/SDLSoundManager.h
        sound/Music.cpp
        sound/Music.h
        sound/SoundEffect.cpp
        sound/SoundEffect.h
        )

set(DEFINITION_SRC
        definitions/SystemPriority.h
        )

set(EXCEPTION_SRC
        exceptions/SDLMixerException.h
        exceptions/ResourceNotFoundException.h
        )

set(UI_SRC
        ui/Frame.cpp
        ui/Frame.h
        ui/UISystem.cpp
        ui/UISystem.h
        ui/components/Component.h
        ui/DrawContext.h
        ui/components/Button.cpp
        ui/components/Button.h
        ui/components/IAction.h
        ui/components/OpenFrameAction.cpp
        ui/components/OpenFrameAction.h
        ui/components/Label.cpp
        ui/components/Label.h
        ui/components/FlowDirection.h
        ui/components/LayoutAnchor.h
        ui/components/WrappedComponent.h
        ui/components/ComponentSize.h
        ui/components/ComponentSizeType.h
        ui/components/StackPanel.cpp
        ui/components/StackPanel.h
        ui/components/LayoutPanel.cpp
        ui/components/LayoutPanel.h
        ui/components/ComponentSize.cpp
        ui/components/TextComponent.h
        ui/components/TextComponent.cpp
        ui/components/ComponentPanel.h
        )

# more engine stuff
add_library(engine
        ${ENGINE_GAME_SRC}
        ${ECS_SRC}
        ${INPUT_SRC}
        ${GRAPHICS_SRC}
        ${COMMON_SRC}
        ${PHYSICS_SRC}
        ${WINDOW_SRC}
        ${SOUND_SRC}
        ${EVENTS_SRC}
        ${EXCEPTION_SRC}
        ${DEFINITION_SRC}
        ${UI_SRC}
        )

target_link_libraries(engine
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${BOX2D_LIBRARY}
        )

target_link_libraries(engine ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${BOX2D_LIBRARY})
