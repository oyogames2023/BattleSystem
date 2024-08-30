#include "BattleComponentBase.h"
#include "ComponentBase.h"
#include "SkillComponentBase.h"
#include "DamageComponentBase.h"
#include "StateComponentBase.h"

namespace zeus::battle
{

    BattleComponentBase::BattleComponentBase(const uint64_t ownerId)
        : ownerId_(ownerId)
    {
    }

    BattleComponentBase::~BattleComponentBase()
    {
    }

    bool BattleComponentBase::Initialize()
    {
        RegisterCommponents();

        return true;
    }

    bool BattleComponentBase::AttachComponent(const uint32_t id, ComponentBasePtr comp)
    {
        auto it = components_.find(id);
        if (components_.end() != it) {
            return false;
        }
        comp->Attach();
        components_.insert(std::make_pair(id, comp));
        return true;
    }

    bool BattleComponentBase::DetachComponent(const uint32_t id)
    {
        auto it = components_.find(id);
        if (components_.end() == it)
        {
            return false;
        }
        it->second->Detach();
        components_.erase(it);
        return true;
    }

    void BattleComponentBase::RegisterCommponents()
    {
        AttachComponent(SkillComponentBase::ID, std::make_shared<SkillComponentBase>(ownerId_));
        AttachComponent(DamageComponentBase::ID, std::make_shared<DamageComponentBase>(ownerId_));
        AttachComponent(StateComponentBase::ID, std::make_shared<StateComponentBase>(ownerId_));
    }

} // namespace zeus::battle