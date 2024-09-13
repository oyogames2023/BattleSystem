#include "StateComponentBase.h"
#include "BattleDefines.h"

namespace zeus::battle
{

    StateComponentBase::StateComponentBase(const uint64_t ownerId)
        : ComponentBase(ownerId)
    {
    }

    StateComponentBase::~StateComponentBase()
    {
    }

    uint32_t StateComponentBase::GetId() const
    {
        return StateComponentBase::ID;
    }

    bool StateComponentBase::Initialize()
    {
        return true;
    }

    void StateComponentBase::Update(const uint64_t now)
    {

    }

    void StateComponentBase::Shutdown()
    {
    }

    void StateComponentBase::Attach()
    {

    }

    void StateComponentBase::Detach()
    {
    }

	bool StateComponentBase::AddForbiddenState(const uint32_t state)
	{
        if (HasForbiddenState(state))
        {
            return false;
        }
        forbiddenStates_.insert(state);
        return true;
	}

	bool StateComponentBase::RemoveForbiddenState(const uint32_t state)
	{
        if (!HasForbiddenState(state))
        {
            return false;
        }
        forbiddenStates_.erase(state);
        return true;
	}

    bool StateComponentBase::HasForbiddenState(const uint32_t state) const
    {
        auto it = forbiddenStates_.find(state);
        return forbiddenStates_.end() != it;
    }

    bool StateComponentBase::IsControlled() const
    {
        static const std::set<uint32_t> forbiddenStates =
        {
            static_cast<uint32_t>(EForbiddenState::Stunned),
            static_cast<uint32_t>(EForbiddenState::Frozen),
            static_cast<uint32_t>(EForbiddenState::Feared),
            static_cast<uint32_t>(EForbiddenState::Charmed),
            static_cast<uint32_t>(EForbiddenState::Silenced),
        };

        for (const auto& state : forbiddenStates)
        {
            if (HasForbiddenState(state))
            {
                return true;
            }
        }

        return false;
    }

} // namespace zeus::battle
