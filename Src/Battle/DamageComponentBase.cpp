#include "DamageComponentBase.h"

namespace zeus::battle
{

    DamageComponentBase::DamageComponentBase(const uint64_t ownerId)
        : ComponentBase(ownerId)
    {
    }

    DamageComponentBase::~DamageComponentBase()
    {
    }

    uint32_t DamageComponentBase::GetId() const
    {
        return DamageComponentBase::ID;
    }

    bool DamageComponentBase::Initialize()
    {
        return true;
    }

    void DamageComponentBase::Update(const uint64_t now)
    {

    }

    void DamageComponentBase::Shutdown()
    {
    }

    void DamageComponentBase::Attach()
    {

    }

    void DamageComponentBase::Detach()
    {
    }

} // namespace zeus::battle