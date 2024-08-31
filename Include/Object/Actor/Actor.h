#pragma once

#include "SceneObject.h"

namespace zeus
{

    class BATTLE_API Actor
        : public SceneObject
    {
    public:

        Actor(const uint16_t majorType, const uint16_t subType, const uint32_t id);

        virtual ~Actor();
        
    };

} // namespace zeus