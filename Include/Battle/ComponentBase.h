#pragma once

#include "Commom.h"

namespace battle
{

    class BATTLE_API ComponentBase
    {
    public:

        ComponentBase(const uint64_t ownerId)
            : ownerId_(ownerId)
        {
        }

        virtual ~ComponentBase() = default;

    public:

        virtual uint32_t GetId() const = 0;

        virtual bool Initialize() = 0;

        virtual void Update(const uint64_t now) = 0;

        virtual void Shutdown() = 0;

        virtual void Attach() = 0;

        virtual void Detach() = 0;

    private:

        uint64_t ownerId_ = 0;
    };

} // namespace battle