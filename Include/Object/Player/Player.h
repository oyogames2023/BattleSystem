#pragma once

#include "Actor.h"

namespace zeus
{

    class BATTLE_API Player
        : public Actor
    {
    public:

        Player(const uint32_t id);
        
        virtual ~Player();
    };

} // namespace zeus