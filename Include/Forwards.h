#pragma once

#include "Commom.h"

namespace battle
{

    class ComponentBase;
    using ComponentBasePtr = std::shared_ptr<ComponentBase>;

    class SkillComponentBase;
    using SkillComponentBasePtr = std::shared_ptr<SkillComponentBase>;

    class DamageComponentBase;
    using DamageComponentBasePtr = std::shared_ptr<DamageComponentBase>;

    class StateComponentBase;
    using StateComponentBasePtr = std::shared_ptr<StateComponentBase>;

    class BattleComponentBase;
    using BattleComponentBasePtr = std::shared_ptr<BattleComponentBase>;

} // namespace battle