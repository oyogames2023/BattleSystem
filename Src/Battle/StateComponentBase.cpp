#include "StateComponentBase.h"

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

} // namespace zeus::battle