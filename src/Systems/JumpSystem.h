#ifndef VIGILANTE_JUMPSYSTEM_H
#define VIGILANTE_JUMPSYSTEM_H

#include "System.h"

class JumpSystem : public System {
public:
    void Update(entt::registry &registry, float deltaTime) override;
};


#endif //VIGILANTE_JUMPSYSTEM_H
