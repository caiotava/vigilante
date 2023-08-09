#include "AnimationSystem.h"

void AnimationSystem::Update(entt::registry &registry, float deltaTime) {
    auto view = registry.view<SpriteComponent, AnimationPlayerComponent>();

    for (auto entity : view) {
        auto[sprite, animationPlayer] = view.get<SpriteComponent, AnimationPlayerComponent>(entity);

        if (!animationPlayer.HasCurrentAnimation()) {
            continue;
        }

        auto animation = animationPlayer.CurrentAnimation();
        if (!animationPlayer.Active && !animation->PlayAllFrames) {
            continue;
        }

        if ((SDL_GetTicks() - animation->LastTickCount) < animation->FrameSpeedRate) {
            continue;
        }

        if  (animation->CurrentFrame >= animation->TotalFrames) {
            if (!animation->NextAnimationName.empty()) {
                animationPlayer.SetCurrentAnimation(animation->NextAnimationName);
                animation->CurrentFrame = 0;
                animation = animationPlayer.CurrentAnimation();
            }

            animation->CurrentFrame = 0;
        }

        sprite.RectSource.x = (animation->OffsetX + animation->CurrentFrame) * sprite.RectSource.w;
        sprite.RectSource.y = (animation->OffsetY) * sprite.RectSource.h;
        animation->LastTickCount = SDL_GetTicks();
        animation->CurrentFrame++;
    }
}