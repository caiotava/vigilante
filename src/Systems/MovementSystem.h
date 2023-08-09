#ifndef VIGILANTE_MOVEMENTSYSTEM_H
#define VIGILANTE_MOVEMENTSYSTEM_H

#include "System.h"

class MovementSystem : public System {
public:
    void Update(entt::registry &registry, const float deltaTime) override;
};

#endif //VIGILANTE_MOVEMENTSYSTEM_H
