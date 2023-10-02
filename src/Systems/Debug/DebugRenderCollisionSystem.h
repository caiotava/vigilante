#ifndef VIGILANTE_DEBUGRENDERCOLLISIONSYSTEM_H
#define VIGILANTE_DEBUGRENDERCOLLISIONSYSTEM_H

#include "Systems/System.h"
#include "Events/EventCollision.h"

#include <SDL.h>


class DebugRenderCollisionSystem : public System {
public:
    virtual void Update(entt::registry &registry, float deltaTime) override;
};

#endif //VIGILANTE_DEBUGRENDERCOLLISIONSYSTEM_H
