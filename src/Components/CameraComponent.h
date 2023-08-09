#ifndef VIGILANTE_CAMERACOMPONENT_H
#define VIGILANTE_CAMERACOMPONENT_H

#include <entt/entity/entity.hpp>
#include <glm/glm.hpp>
#include <SDL.h>

class CameraComponent {
public:
    SDL_FRect Rect;
    glm::vec2 Bounds;

    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;
    explicit CameraComponent(const SDL_FRect &rect, const glm::vec2 &bounds): Rect(rect), Bounds(bounds) {}
};

#endif //VIGILANTE_CAMERACOMPONENT_H
