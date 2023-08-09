#ifndef VIGILANTE_JUMPCOMPONENT_H
#define VIGILANTE_JUMPCOMPONENT_H

class JumpComponent {
public:
    float JumpForce{};
    float GravityForce{};
    float Acceleration{};
    bool IsJumping{};
    bool IsFalling{};
    float CurrentJumpForce{};

    JumpComponent() = default;
    JumpComponent(const JumpComponent&) = default;
    JumpComponent(float force, float gravity): JumpForce{force}, GravityForce{gravity} {
        IsJumping = {false};
        IsFalling = {false};
        CurrentJumpForce = {0.0f};
        Acceleration = {0.0f};
    }
};

#endif //VIGILANTE_JUMPCOMPONENT_H
