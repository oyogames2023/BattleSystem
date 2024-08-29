#pragma once

#include "Forwards.h"

namespace battle
{

    class BATTLE_API BattleComponentBase
    {
    public:

        BattleComponentBase(const uint64_t ownerId);

        virtual ~BattleComponentBase();

    public:

        virtual bool Initialize();

    public:

        bool AttachComponent(const uint32_t id, ComponentBasePtr comp);

        bool DetachComponent(const uint32_t id);

    private:

        virtual void RegisterCommponents();

    private:

        uint64_t ownerId_ = 0;

        std::map<uint32_t, ComponentBasePtr> components_;
    };

} // namespace battle