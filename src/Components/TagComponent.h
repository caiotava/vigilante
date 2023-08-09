#ifndef VIGILANTE_TAGCOMPONENT_H
#define VIGILANTE_TAGCOMPONENT_H

#include <string>

class TagComponent {
public:
    std::string Name;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& name) : Name(name) {}
};

#endif //VIGILANTE_TAGCOMPONENT_H
