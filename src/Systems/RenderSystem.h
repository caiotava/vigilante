#ifndef VIGILANTE_RENDERSYSTEM_H
#define VIGILANTE_RENDERSYSTEM_H

#include "System.h"

class RenderSystem : public System {
public:
    void Update(entt::registry &registry, float deltaTime) override;
};

#endif //VIGILANTE_RENDERSYSTEM_H
