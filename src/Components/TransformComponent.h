#ifndef VIGILANTE_TRANSFORMCOMPONENT_H
#define VIGILANTE_TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

class TransformComponent {
public:
    glm::vec2 Transform;

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::vec2 &transform): Transform(transform) {}
};

#endif //VIGILANTE_TRANSFORMCOMPONENT_H
