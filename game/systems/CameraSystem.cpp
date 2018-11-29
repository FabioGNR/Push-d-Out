#include "CameraSystem.h"
#include <cmath>
#include <engine/common/Vector2D.h>
#include <game/components/DimensionComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>

namespace game {
namespace systems {
    using namespace game::components;
    void CameraSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        common::Vector2D<double> upper{}, lower{}, cameraPosition{};
        bool foundPlayers = findPlayerCenterOfMass(cameraPosition, lower, upper);
        if (!foundPlayers) {
            centerOnLevel();
            return;
        }
        // determine zoom based on distance
        const auto maxDistance = upper - lower;
        const auto minimumVisibleRegion = common::Vector2D<double>::max(maxDistance + common::Vector2D<double>(5, 5),
            common::Vector2D<double>(48, 27));
        const double idealZoom = m_camera->getFittedZoom(minimumVisibleRegion);
        m_camera->setZoom(idealZoom);
        m_camera->setPosition(clampCameraPosition(cameraPosition));
    }

    void CameraSystem::render(engine::IRenderer& /*renderer*/)
    {
    }

    bool CameraSystem::findPlayerCenterOfMass(common::Vector2D<double>& center, common::Vector2D<double>& lower,
        common::Vector2D<double>& upper)
    {
        const auto& levelDimensions = getLevelDimensions();
        bool lowerBoundSet = false, upperBoundSet = false;
        common::Vector2D<double> sumCenterPoints = common::Vector2D<double>(0, 0);
        int amountOfCenterPoints = 0;
        // Iterate through the characters to find the center point
        m_ecsWorld->forEachEntityWith<PositionComponent,
            PlayerInputComponent, DimensionComponent>([&](engine::ecs::Entity& entity) {
            // only use positions that have not fallen out of the world
            if (!isEntityWithinRegion(entity, levelDimensions)) {
                return;
            }
            const auto& position = m_ecsWorld->getComponent<PositionComponent>(entity).position;
            const auto& dimension = m_ecsWorld->getComponent<DimensionComponent>(entity).dimension;
            const auto centerOfEntity = position + (dimension / 2.0);
            sumCenterPoints += centerOfEntity;
            amountOfCenterPoints++;
            if (!lowerBoundSet) {
                lowerBoundSet = true;
                lower = position;
            } else {
                lower = common::Vector2D<double>::min(lower, position);
            }
            if (!upperBoundSet) {
                upperBoundSet = true;
                upper = position + dimension;
            } else {
                upper = common::Vector2D<double>::max(upper, position + dimension);
            }
        });
        center = sumCenterPoints / amountOfCenterPoints;
        return amountOfCenterPoints > 0;
    }

    void CameraSystem::centerOnLevel()
    {
        const auto levelDimensions = getLevelDimensions();
        const auto fittedZoom = m_camera->getFittedZoom(levelDimensions);
        m_camera->setZoom(fittedZoom);
        const auto cameraPosition = levelDimensions / 2;
        m_camera->setPosition(clampCameraPosition(cameraPosition));
    }

    common::Vector2D<double> CameraSystem::getLevelDimensions() const
    {
        common::Vector2D<double> levelBounds{};
        m_ecsWorld->forEachEntityWith<LevelMetaComponent, DimensionComponent>([&](engine::ecs::Entity& entity) {
            levelBounds = m_ecsWorld->getComponent<DimensionComponent>(entity).dimension;
        });
        return levelBounds;
    }

    common::Vector2D<double> CameraSystem::clampCameraPosition(common::Vector2D<double> pos) const
    {
        const auto levelDimensions = getLevelDimensions();
        const auto visibleRegion = m_camera->getVisibleRegionSize();
        // clamp camera position so camera does not show anything outside level
        pos.y = std::min(levelDimensions.y - (visibleRegion.y / 2),
            std::max(pos.y, visibleRegion.y / 2));
        pos.x = std::min(levelDimensions.x - (visibleRegion.x / 2),
            std::max(pos.x, visibleRegion.x / 2));
        return pos;
    }

    bool CameraSystem::isEntityWithinRegion(const engine::ecs::Entity& entity,
        const common::Vector2D<double>& region) const
    {
        const auto& position = m_ecsWorld->getComponent<PositionComponent>(entity).position;
        const auto& dimension = m_ecsWorld->getComponent<DimensionComponent>(entity).dimension;
        bool isXWithinBounds = position.x > 0 && (position.x + dimension.x) < region.x;
        bool isYWithinBounds = position.y > 0 && (position.y + dimension.y) < region.y;
        return isXWithinBounds && isYWithinBounds;
    }
}
}