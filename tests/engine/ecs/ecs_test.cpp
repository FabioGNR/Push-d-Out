#include <Catch/catch2.hpp>

#include <engine/ecs/Component.h>
#include <engine/ecs/ComponentManager.h>
#include <engine/ecs/Entity.h>
#include <engine/ecs/EntityManager.h>
#include <engine/ecs/World.h>

#include <set>

using namespace engine;

TEST_CASE("Entity manager can create entities", "[ecs]")
{
    SECTION("Entity manager creates unique entities", "[ecs]")
    {
        std::set<ecs::EntityId> entitySet;
        ecs::EntityManager entityManager;

        const std::size_t uniqueEntities = 1000;
        for (std::size_t i = 0; i < uniqueEntities; ++i) {
            entitySet.insert(entityManager.create().id());
        }

        REQUIRE(entitySet.size() == uniqueEntities);
    }

    SECTION("Entity manager can create and destroy entities", "[ecs]")
    {
        ecs::EntityManager entityManager;
        REQUIRE(entityManager.count() == 0);
        auto& entity = entityManager.create();
        REQUIRE(entityManager.count() == 1);
        entityManager.destroy(entity);
        REQUIRE(entityManager.count() == 0);
    }
}

TEST_CASE("Components have unique id's", "[ecs]")
{
    struct TestComponentOne : public ecs::BaseComponent<TestComponentOne> {
    };
    struct TestComponentTwo : public ecs::BaseComponent<TestComponentTwo> {
    };

    REQUIRE(TestComponentOne::familyId() == TestComponentOne::familyId());
    REQUIRE(TestComponentOne::familyId() != TestComponentTwo::familyId());
}

TEST_CASE("Entities can have a component attached to them", "[ecs]")
{
    struct TestComponent : public ecs::BaseComponent<TestComponent> {
    };

    ecs::World world;
    auto& entity = world.createEntity();

    SECTION("The entity does not have the component yet")
    {
        REQUIRE_FALSE(entity.hasComponent<TestComponent>());
    }
    SECTION("When adding a component, the entity will register it")
    {
        world.addComponent<TestComponent>(entity, TestComponent{});
        REQUIRE(entity.hasComponent<TestComponent>());
    }
    SECTION("When adding multiple different components, the entity will register it")
    {
        struct OtherComponent : public ecs::BaseComponent<OtherComponent> {
        };

        REQUIRE_FALSE(entity.hasComponent<TestComponent>());
        REQUIRE_FALSE(entity.hasComponent<OtherComponent>());

        world.addComponent<TestComponent>(entity, TestComponent{});
        world.addComponent<OtherComponent>(entity, OtherComponent{});

        REQUIRE(entity.hasComponent<TestComponent>());
        REQUIRE(entity.hasComponent<OtherComponent>());
    }
}

TEST_CASE("ECS World can iterate over entities", "[ecs]")
{
    ecs::World world;
    SECTION("ECS world iterates over all entities with a given component")
    {
        struct TestComponent : public ecs::BaseComponent<TestComponent> {
        };

        const std::size_t entityCount = 1000;
        for (std::size_t i = 0; i < entityCount; ++i) {
            auto& entity = world.createEntity();
            world.addComponent<TestComponent>(entity, TestComponent{});
        }

        std::size_t iteratedEntities = 0;
        world.forEachEntityWith<TestComponent>([&](const auto& /*entity*/) {
            iteratedEntities++;
        });

        REQUIRE(entityCount == iteratedEntities);
    }
}