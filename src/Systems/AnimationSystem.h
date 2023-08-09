#ifndef VIGILANTE_ANIMATIONSYSTEM_H
#define VIGILANTE_ANIMATIONSYSTEM_H

#include "Components/Components.h"
#include "System.h"

class AnimationSystem : public System {
public:
    void Update(entt::registry &registry, float deltaTime) override;
};

#endif //VIGILANTE_ANIMATIONSYSTEM_H
