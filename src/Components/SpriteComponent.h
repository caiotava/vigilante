#ifndef VIGILANTE_SPRITECOMPONENT_H
#define VIGILANTE_SPRITECOMPONENT_H

#include <string>

#include <SDL.h>

class SpriteComponent {
public:
    std::string AssertID;
    SDL_Rect RectSource{};
    bool IsFixed{};
    bool Flip{};

    SpriteComponent() = default;
    SpriteComponent(const SpriteComponent&) = default;
    SpriteComponent(const std::string& assertID, SDL_Rect rectSrc, bool flip = false) :
        AssertID(assertID),
        RectSource(rectSrc),
        Flip(flip),
        IsFixed{false}{}
};

#endif //VIGILANTE_SPRITECOMPONENT_H
