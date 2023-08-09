#ifndef VIGILANTE_INPUTKEYBOARDSYSTEM_H
#define VIGILANTE_INPUTKEYBOARDSYSTEM_H

#include "Components/Components.h"
#include "System.h"

#include <SDL.h>

class InputKeyboardSystem : public System {
public:
    void Update(entt::registry &registry, float deltaTime) override;
};

#endif //VIGILANTE_INPUTKEYBOARDSYSTEM_H
