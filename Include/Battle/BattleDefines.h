#pragma once

#include "Common.h"
#include "BattleConfig.h"

namespace zeus::battle
{

	enum class EForbiddenState : uint32_t
	{
		Stunned,							// 眩晕状态：无法移动、攻击和施法
		Frozen,								// 冰冻状态：类似眩晕，通常由冰冻效果造成
		Feared,								// 恐惧状态：失去控制，随机移动（乱跑）
		Charmed,							// 魅惑状态：被其他单位控制
		Silenced,							// 沉默状态：无法施法
	};

	struct BATTLE_API StateInfo
	{
		uint32_t CfgId = 0; // 配置表唯一id
		uint32_t StackCount = 0; // 层数
	};

	struct BATTLE_API BattleContext
	{

	};

	struct BATTLE_API SkillContext
	{
		uint64_t OwnerId = 0;

		std::vector<uint64_t> TargetIds;
	};

} // namespace zeus::battle