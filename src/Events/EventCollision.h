#ifndef VIGILANTE_EVENTCOLLISION_H
#define VIGILANTE_EVENTCOLLISION_H

#include<entt/entt.hpp>

class EventCollision {
public:
    entt::registry *registry;
    entt::entity entityCollisionA;
    entt::entity entityCollisionB;
};

#endif //VIGILANTE_EVENTCOLLISION_H
