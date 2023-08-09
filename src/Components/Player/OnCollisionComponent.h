#ifndef VIGILANTE_ONCOLLISIONCOMPONENT_H
#define VIGILANTE_ONCOLLISIONCOMPONENT_H

#include "Events/EventCollision.h"

class OnCollisionComponentPlayer {
    void (*OnCollision)(const EventCollision &event);
};

#endif //VIGILANTE_ONCOLLISIONCOMPONENT_H
