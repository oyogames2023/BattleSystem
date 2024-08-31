#include "Actor.h"

namespace zeus
{

    Actor::Actor(const uint16_t majorType, const uint16_t subType, const uint32_t id)
        : SceneObject(majorType, subType, id)
    {
    }

    Actor::~Actor()
    {
    }

} // namespace zeus