#ifndef VIGILANTE_COLLISIONCOMPONENT_H
#define VIGILANTE_COLLISIONCOMPONENT_H

#include <SDL.h>

class CollisionComponent {
public:
    SDL_FRect Rect{};

    CollisionComponent() = default;
    CollisionComponent(const CollisionComponent&) = default;
    explicit CollisionComponent(const SDL_FRect& rect) : Rect(rect) {}
};

#endif //VIGILANTE_COLLISIONCOMPONENT_H
