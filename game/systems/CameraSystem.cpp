#include "CameraSystem.h"
#include <cmath>
#include <engine/common/Vector2D.h>
#include <engine/graphics/Color.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <game/components/DimensionComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PlayerNameComponent.h>
#include <game/components/PositionComponent.h>

namespace game::systems {
using namespace game::components;

const common::Vector2D<double> CameraSystem::PADDING = { 8, 6 };
const common::Vector2D<double> CameraSystem::CAMERA_SAFE_ZONE_MARGIN = { 4, 2 };

void CameraSystem::update(std::chrono::nanoseconds timeStep)
{
    double seconds = timeStep.count() / 1e9;
    setCameraMoveSpeed();

    auto boundaries = findTargetBoundaries();
    m_camera->setPosition(findNextPosition(boundaries, seconds));
    m_camera->setZoom(findSmoothZoom(boundaries, seconds));
}

void CameraSystem::render(engine::IRenderer& /* renderer */)
{
}

common::Vector2D<double> CameraSystem::getLevelDimensions() const
{
    common::Vector2D<double> boundaries{};
    m_ecsWorld->forEachEntityWith<LevelMetaComponent, DimensionComponent>([&](engine::ecs::Entity& entity) {
        boundaries += m_ecsWorld->getComponent<DimensionComponent>(entity).dimension;
    });
    return boundaries;
}

CameraSystem::Boundaries CameraSystem::findTargetBoundaries()
{
    common::Vector2D<double> acc;
    int count = 0;

    // calculate centroid
    m_ecsWorld->forEachEntityWith<PositionComponent,
        PlayerNameComponent,
        DimensionComponent>([&](engine::ecs::Entity& entity) {
        const auto& position = m_ecsWorld->getComponent<PositionComponent>(entity).position;
        const auto& dimension = m_ecsWorld->getComponent<DimensionComponent>(entity).dimension;
        auto center = position + (dimension / 2);

        if (isWithinLevel(position, dimension)) {
            acc += center;
            ++count;
        }
    });

    // get center of level if there are no players
    if (count == 0) {
        return { getLevelDimensions() / 2, getLevelDimensions() / 2 + CameraSystem::PADDING };
    }

    auto centroid = acc / count;
    double radius = -1;
    common::Vector2D<double> bounds;

    // find radius
    m_ecsWorld->forEachEntityWith<PositionComponent,
        PlayerInputComponent,
        DimensionComponent>([&](engine::ecs::Entity& entity) {
        const auto& position = m_ecsWorld->getComponent<PositionComponent>(entity).position;
        const auto& dimension = m_ecsWorld->getComponent<DimensionComponent>(entity).dimension;
        auto center = position + (dimension / 2);

        if (isWithinLevel(position, dimension)) {
            auto delta = (center - centroid).abs();
            double length = delta.magnitude();

            if (radius < 0 || length > radius) {
                radius = length;
                bounds = delta;
            }
        }
    });

    return { centroid, bounds + CameraSystem::PADDING };
}

bool CameraSystem::isWithinLevel(const common::Vector2D<double> point, const common::Vector2D<double> dimensions) const
{
    const int padding = 25;

    bool isXWithinBounds = (point.x + dimensions.x) > 0 - padding && point.x < getLevelDimensions().x + padding;
    bool isYWithinBounds = (point.y + dimensions.y) > 0 - padding && point.y < getLevelDimensions().y + padding;
    return isXWithinBounds && isYWithinBounds;
}

bool CameraSystem::isOutOfSafeCameraBounds(const common::Vector2D<double> point, const common::Vector2D<double> dimensions) const
{
    common::Vector2D<double> safeMargin = m_camera->getVisibleRegionSize() - (CameraSystem::CAMERA_SAFE_ZONE_MARGIN * 2);
    bool isXWithinBounds = (point.x + dimensions.x) > m_currentPosition.x - (safeMargin.x / 2) && point.x < m_currentPosition.x + (safeMargin.x / 2);
    bool isYWithinBounds = (point.y + dimensions.y) > m_currentPosition.y - (safeMargin.y / 2) && point.y < m_currentPosition.y + (safeMargin.y / 2);
    return (!isXWithinBounds || !isYWithinBounds) && isWithinLevel(point, dimensions);
}

double CameraSystem::findSmoothZoom(Boundaries boundaries, double seconds)
{
    auto targetZoom = m_camera->getFittedZoom(common::Vector2D<double>(boundaries.size.x * 2, boundaries.size.y * 2));
    auto currentZoom = m_camera->getZoom();
    return currentZoom + (-(currentZoom - targetZoom) * m_zoomSpeed * seconds);
}

common::Vector2D<double> CameraSystem::findNextPosition(CameraSystem::Boundaries boundaries, double seconds)
{
    // prevent camera shake
    m_lastCenter = boundaries.center;
    m_currentPosition += (boundaries.center - m_currentPosition) * m_moveSpeed * seconds;
    return m_currentPosition;
}

void CameraSystem::setCameraMoveSpeed()
{
    m_moveSpeed = CameraSystem::CAMERA_MOVEMENT_SPEED;
    m_zoomSpeed = CameraSystem::CAMERA_ZOOM_SPEED;

    for (auto it = m_ecsWorld->begin<components::PlayerInputComponent>(); it != m_ecsWorld->end<components::PlayerInputComponent>(); ++it) { // NOLINT
        auto& entity = m_ecsWorld->getEntity(it->first);
        auto& position = m_ecsWorld->getComponent<PositionComponent>(entity).position;
        auto& dimension = m_ecsWorld->getComponent<DimensionComponent>(entity).dimension;

        if (isOutOfSafeCameraBounds(position, dimension)) {
            m_moveSpeed = CameraSystem::CAMERA_MOVEMENT_SPEED_FAST;
            m_zoomSpeed = CameraSystem::CAMERA_ZOOM_SPEED_FAST;
            break;
        }
    }
}
}
