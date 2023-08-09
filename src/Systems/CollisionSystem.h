#ifndef VIGILANTE_COLLISIONSYSTEM_H
#define VIGILANTE_COLLISIONSYSTEM_H

#include "System.h"
#include "Events/EventCollision.h"

#include <SDL.h>

class CollisionSystem : public System {
public:
    void Update(entt::registry &registry, float deltaTime) override;
    static void OnCollision(const EventCollision &event);

private:
    static SDL_FRect fixCollisionPosition(const SDL_FRect &rectIntersection, const SDL_FRect pos);

};


#endif //VIGILANTE_COLLISIONSYSTEM_H
