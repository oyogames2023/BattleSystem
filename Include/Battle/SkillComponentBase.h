#pragma once

#include "ComponentBase.h"

namespace battle
{

    class BATTLE_API SkillComponentBase
        : public ComponentBase
    {
    public:

        SkillComponentBase(const uint64_t ownerId);

        virtual ~SkillComponentBase();

    public:

        static constexpr uint32_t ID = 2;

    public:

        uint32_t GetId() const override;

        bool Initialize() override;

        void Update(const uint64_t now) override;

        void Shutdown() override;

        void Attach() override;

        void Detach() override;
    };

} // namespace battle