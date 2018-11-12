#include "CameraSystem.h"
#include <cmath>
#include <engine/common/Vector2D.h>
#include <game/components/DimensionComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>

namespace game {
namespace systems {
    using namespace game::components;
    void CameraSystem::update(std::chrono::nanoseconds /*timeStep*/)
    {
        bool lowerBoundSet = false, upperBoundSet = false;
        common::Vector2D<double> lowerBound = common::Vector2D<double>(0, 0);
        common::Vector2D<double> upperBound = common::Vector2D<double>(0, 0);
        common::Vector2D<double> sumCenterPoints = common::Vector2D<double>(0, 0);
        int amountOfCenterPoints = 0;
        // Iterate through the characters to find the center point
        m_ecsWorld.forEachEntityWith<PositionComponent,
            PlayerInputComponent, DimensionComponent>([&](engine::ecs::Entity& entity) {
            auto& positionComponent = m_ecsWorld.getComponent<PositionComponent>(entity);
            auto& dimensionComponent = m_ecsWorld.getComponent<DimensionComponent>(entity);
            // only use positions that have not fallen out of the world
            // TODO: use dimensions from level bounds
            if (positionComponent.position.y + dimensionComponent.dimension.y > -2) {
                const auto center = positionComponent.position + (dimensionComponent.dimension / 2.0);
                sumCenterPoints += center;
                amountOfCenterPoints++;
                if (!lowerBoundSet) {
                    lowerBoundSet = true;
                    lowerBound = positionComponent.position;
                } else {
                    lowerBound = common::Vector2D<double>::min(lowerBound, positionComponent.position);
                }
                if (!upperBoundSet) {
                    upperBoundSet = true;
                    upperBound = positionComponent.position + dimensionComponent.dimension;
                } else {
                    upperBound = common::Vector2D<double>::max(upperBound, positionComponent.position + dimensionComponent.dimension);
                }
            }
        });
        auto cameraPosition = sumCenterPoints / amountOfCenterPoints;
        // determine zoom based on distance
        const auto maxDistance = upperBound - lowerBound;
        const auto visibleDistance = maxDistance + common::Vector2D<double>(20, 20);
        double idealZoom = std::min(2.0, m_camera->getFittedZoom(visibleDistance));
        cameraPosition.y = std::max(cameraPosition.y, (visibleDistance.y / 2) - 1);
        m_camera->setZoom(idealZoom);
        m_camera->setPosition(cameraPosition);
        //TODO: instead of setting position and zoom directly ease towards desired value
    }

    void CameraSystem::render(engine::IRenderer& /*renderer*/)
    {
    }
}
}