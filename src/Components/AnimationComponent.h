#ifndef VIGILANTE_ANIMATIONCOMPONENT_H
#define VIGILANTE_ANIMATIONCOMPONENT_H

#include <cstdint>
#include <string>
#include <utility>

#include <SDL.h>

class AnimationComponent {
public:
    std::string Name;
    std::string NextAnimationName;
    int32_t OffsetX{};
    int32_t OffsetY{};
    int32_t CurrentFrame{};
    int32_t TotalFrames{};
    int32_t FrameSpeedRate{};
    uint32_t LastTickCount{};
    bool PlayAllFrames = {false};

    AnimationComponent() = default;

    AnimationComponent(const AnimationComponent &) = default;

    AnimationComponent(std::string name, int32_t offsetX, int32_t offsetY, int32_t total, int32_t speed, std::string nextAnimation = "",
                       bool playAllFrames = false) :
            Name(std::move(name)),
            NextAnimationName(std::move(nextAnimation)),
            OffsetX(offsetX),
            OffsetY(offsetY),
            TotalFrames(total),
            FrameSpeedRate(speed),
            CurrentFrame(0),
            LastTickCount(SDL_GetTicks()),
            PlayAllFrames(playAllFrames) {}
};

#endif //VIGILANTE_ANIMATIONCOMPONENT_H
