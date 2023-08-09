#ifndef VIGILANTE_RIGIDBODYCOMPONENT_H
#define VIGILANTE_RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>

class RigidBodyComponent {
public:
    glm::vec2 Velocity;
    bool IsStatic;
    bool IsTriggered;
    bool IsCollideWithStatic;

    RigidBodyComponent() = default;

    RigidBodyComponent(const RigidBodyComponent &) = default;

    RigidBodyComponent(const glm::vec2 velocity, bool isStatic = false, bool isTriggered = false,
                       bool collideWithStatic = false) :
            Velocity(velocity),
            IsStatic(isStatic),
            IsTriggered(isTriggered),
            IsCollideWithStatic(collideWithStatic) {}


    [[nodiscard]] bool NeedCollisionFix(const RigidBodyComponent &rigidBodyB) const noexcept {
        // If neither rigid bodies are triggered, the collision must be fixed.
        if (!IsTriggered && !rigidBodyB.IsTriggered) {
            return true;
        }

        auto fixCollisionRigidBodyA = (IsTriggered && IsCollideWithStatic && rigidBodyB.IsStatic);
        auto fixCollisionRigidBodyB = (rigidBodyB.IsTriggered && rigidBodyB.IsCollideWithStatic && IsStatic);

        return fixCollisionRigidBodyA || fixCollisionRigidBodyB;
    }
};

#endif //VIGILANTE_RIGIDBODYCOMPONENT_H
