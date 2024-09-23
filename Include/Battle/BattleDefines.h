#pragma once

#include "Common.h"
#include "BattleConfig.h"

namespace zeus::battle
{

	enum class EForbiddenState : uint32_t
	{
		Stunned,							// ѣ��״̬���޷��ƶ���������ʩ��
		Frozen,								// ����״̬������ѣ�Σ�ͨ���ɱ���Ч�����
		Feared,								// �־�״̬��ʧȥ���ƣ�����ƶ������ܣ�
		Charmed,							// �Ȼ�״̬����������λ����
		Silenced,							// ��Ĭ״̬���޷�ʩ��
	};

	struct BATTLE_API StateInfo
	{
		uint32_t CfgId = 0; // ���ñ�Ψһid
		uint32_t StackCount = 0; // ����
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