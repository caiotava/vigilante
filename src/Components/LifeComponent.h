#ifndef VIGILANTE_LIFECOMPONENT_H
#define VIGILANTE_LIFECOMPONENT_H

#include <cstdint>

class LifeComponent {
public:
    std::uint8_t Value;

    LifeComponent() = default;
    LifeComponent(const LifeComponent&) = default;
    LifeComponent(const std::uint8_t value) : Value(value) {}
};

#endif //VIGILANTE_LIFECOMPONENT_H
