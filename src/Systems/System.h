#ifndef VIGILANTE_SYSTEM_H
#define VIGILANTE_SYSTEM_H

#include <entt/entt.hpp>

class System {
public:
    virtual ~System() = default;

    virtual void Update(entt::registry &registry, float deltaTime) = 0;
};

#endif //VIGILANTE_SYSTEM_H
