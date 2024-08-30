#include "SkillComponentBase.h"

namespace zeus::battle
{

    SkillComponentBase::SkillComponentBase(const uint64_t ownerId)
        : ComponentBase(ownerId)
    {
    }

    SkillComponentBase::~SkillComponentBase()
    {
    }

    uint32_t SkillComponentBase::GetId() const
    {
        return SkillComponentBase::ID;
    }

    bool SkillComponentBase::Initialize()
    {
        return true;
    }

    void SkillComponentBase::Update(const uint64_t now)
    {

    }

    void SkillComponentBase::Shutdown()
    {
    }

    void SkillComponentBase::Attach()
    {

    }

    void SkillComponentBase::Detach()
    {
    }

} // namespace zeus::battle