#pragma once

#include "ComponentBase.h"

namespace zeus::battle
{

    class BATTLE_API StateComponentBase
        : public ComponentBase
    {
    public:

        StateComponentBase(const uint64_t ownerId);

        virtual ~StateComponentBase();

    public:

        static constexpr uint32_t ID = 3;

    public:

        uint32_t GetId() const override;

        bool Initialize() override;

        void Update(const uint64_t now) override;

        void Shutdown() override;

        void Attach() override;

        void Detach() override;

    public:

        bool AddForbiddenState(const uint32_t state);

        bool RemoveForbiddenState(const uint32_t state);

        bool HasForbiddenState(const uint32_t state) const;

        bool IsControlled() const;

    private:

        std::set<uint32_t> forbiddenStates_;
    };

} // namespace zeus::battle
