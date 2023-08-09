#ifndef VIGILANTE_ANIMATIONPLAYERCOMPONENT_H
#define VIGILANTE_ANIMATIONPLAYERCOMPONENT_H

#include "AnimationComponent.h"

#include <map>

class AnimationPlayerComponent {
public:
    bool Active = {false};

    AnimationPlayerComponent() = default;

    AnimationPlayerComponent(const AnimationPlayerComponent &) = default;

    AnimationPlayerComponent(const std::string& current, bool active): currentAnimationName(current), Active(active) {
    };

    AnimationPlayerComponent &AddAnimation(const AnimationComponent &anim) {
        animations[anim.Name] = anim;

        return *this;
    }

    AnimationPlayerComponent SetCurrentAnimation(const std::string &name) {
        auto animation = CurrentAnimation();

        if (animation->Name == name) {
            return *this;
        }

        if (!animation->PlayAllFrames || animation->CurrentFrame >= animation->TotalFrames) {
            currentAnimationName = name;
            animation->LastTickCount = SDL_GetTicks();
            animation->CurrentFrame = 0;
        }

        return *this;
    }

    AnimationPlayerComponent &Clear() {
        animations.clear();

        return *this;
    }

    AnimationComponent* CurrentAnimation() {
        return &animations[currentAnimationName];
    }

    bool HasCurrentAnimation() {
        return !currentAnimationName.empty();
    }

private:
    std::string currentAnimationName;
    std::map<std::string, AnimationComponent> animations;
};

#endif //VIGILANTE_ANIMATIONPLAYERCOMPONENT_H
