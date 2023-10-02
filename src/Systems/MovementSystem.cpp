#include "MovementSystem.h"

#include "Components/Components.h"

void MovementSystem::Update(entt::registry &registry, const float deltaTime) {
    auto view = registry.view<TransformComponent, RigidBodyComponent>();

    for (auto entity : view) {
        auto &transform = view.get<TransformComponent>(entity);
        auto &rigidBody = view.get<RigidBodyComponent>(entity);

        if (rigidBody.Velocity.x != 0) {
            transform.Transform.x += rigidBody.Velocity.x * deltaTime;
        }

        if (rigidBody.Velocity.y != 0) {
            transform.Transform.y += rigidBody.Velocity.y * deltaTime;
        }
    }
}