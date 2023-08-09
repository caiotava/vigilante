#ifndef VIGILANTE_CAMERAMOVEMENTSYSTEM_H
#define VIGILANTE_CAMERAMOVEMENTSYSTEM_H

#include "System.h"

class CameraMovementSystem : public System {
public:
    void Update(entt::registry &registry, float deltaTime) override;
};


#endif //VIGILANTE_CAMERAMOVEMENTSYSTEM_H
