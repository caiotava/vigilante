#include "JumpSystem.h"

#include "Components/Components.h"

void JumpSystem::Update(entt::registry &registry, float deltaTime) {
    auto view = registry.view<JumpComponent,TransformComponent>();

    for (auto e : view) {
        auto &jump = view.get<JumpComponent>(e);
        auto &transform = view.get<TransformComponent>(e);

        if (!jump.IsJumping) {
            continue;
        }

        // adding jump force
        if (!jump.IsFalling) {
            if (jump.Acceleration == 0.0f) {
                jump.Acceleration = jump.JumpForce;
            }

            transform.Transform.y -= jump.Acceleration * deltaTime;
            jump.CurrentJumpForce += jump.Acceleration * deltaTime;

            jump.Acceleration -= (jump.GravityForce * deltaTime);
            jump.IsFalling = jump.Acceleration <= 0.0f;

            continue;
        }

        // falling logic
        transform.Transform.y -= jump.Acceleration * deltaTime;
        jump.CurrentJumpForce += jump.Acceleration * deltaTime;
        jump.Acceleration -= (jump.GravityForce * deltaTime);

        if (jump.CurrentJumpForce <= 0.0f) {
            jump.IsFalling = false;
            jump.IsJumping = false;
            jump.Acceleration = 0.0f;
            jump.CurrentJumpForce = 0.0f;
        }
    }
}
