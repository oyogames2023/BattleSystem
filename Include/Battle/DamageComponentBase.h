#pragma once

#include "ComponentBase.h"

namespace battle
{

    class BATTLE_API DamageComponentBase
        : public ComponentBase
    {
    public:

        DamageComponentBase(const uint64_t ownerId);

        virtual ~DamageComponentBase();

    public:

        static constexpr uint32_t ID = 1;

    public:

        uint32_t GetId() const override;

        bool Initialize() override;

        void Update(const uint64_t now) override;

        void Shutdown() override;

        void Attach() override;

        void Detach() override;
    };

} // namespace battle