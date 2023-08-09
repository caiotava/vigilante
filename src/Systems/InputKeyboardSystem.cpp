#include "InputKeyboardSystem.h"

#include "Components/Components.h"

#include <SDL.h>

void InputKeyboardSystem::Update(entt::registry &registry, const float deltaTime) {
    auto view = registry.view<InputKeyboardComponent, JumpComponent, SpriteComponent, RigidBodyComponent>();
    const auto keyState = SDL_GetKeyboardState(nullptr);

    for (auto &entity: view) {
        auto &rigidBody = view.get<RigidBodyComponent>(entity);
        auto &sprite = view.get<SpriteComponent>(entity);
        auto &animationPlayer = registry.get<AnimationPlayerComponent>(entity);
        auto &jump = registry.get<JumpComponent>(entity);

        animationPlayer.Active = false;
        rigidBody.Velocity.x = 0;


        if (keyState[SDL_SCANCODE_DOWN] && !jump.IsJumping) {
            if (keyState[SDL_SCANCODE_Z]) {
                animationPlayer.SetCurrentAnimation("crouch-punch");
                animationPlayer.Active = true;
            } else if (keyState[SDL_SCANCODE_X]) {
                animationPlayer.SetCurrentAnimation("crouch-kick");
                animationPlayer.Active = true;
            } else if (!animationPlayer.CurrentAnimation()->Name.starts_with("crouch-")) {
                animationPlayer.SetCurrentAnimation("crouch");
                animationPlayer.Active = true;
            }
        } else if (animationPlayer.CurrentAnimation()->Name == "crouch") {
            animationPlayer.SetCurrentAnimation("idle");
            animationPlayer.Active = true;
        }

        if (keyState[SDL_SCANCODE_LEFT]) {
            rigidBody.Velocity.x = -45.0f;
            sprite.Flip = true;

            if (!jump.IsJumping) {
                animationPlayer.SetCurrentAnimation("walk");
                animationPlayer.Active = true;
            }
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            rigidBody.Velocity.x = 45.0f;
            sprite.Flip = false;

            if (!jump.IsJumping) {
                animationPlayer.SetCurrentAnimation("walk");
                animationPlayer.Active = true;
            }
        }

        if (keyState[SDL_SCANCODE_Z] && !animationPlayer.CurrentAnimation()->Name.starts_with("crouch")) {
            animationPlayer.SetCurrentAnimation("punch");
            animationPlayer.Active = true;
        }
        if (keyState[SDL_SCANCODE_X] && !animationPlayer.CurrentAnimation()->Name.starts_with("crouch")) {
            animationPlayer.SetCurrentAnimation("kick");
            animationPlayer.Active = true;
        }

        if (keyState[SDL_SCANCODE_UP] && !jump.IsJumping) {
            jump.IsJumping = true;
            animationPlayer.Active = false;
            animationPlayer.CurrentAnimation()->CurrentFrame = 0;
            animationPlayer.SetCurrentAnimation("jump");
            animationPlayer.Active = true;
        }
    }
}