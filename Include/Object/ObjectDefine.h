#pragma once

#include "Forwards.h"

enum class EObjectMajorType : uint32_t
{
    None = 0,
    Entity = 1 << 0, // 生物实体（如玩家、NPC、怪物等）
    Item = 1 << 1, // 道具（如护甲、武器等）
    Vehicle = 1 << 2, // 载具（如摩托车、汽车等）
    Interactable = 1 << 3, // 交互物（如机关等）
    Max,
};

enum class EEntityType : uint32_t
{
    None = 0,
    Player = 1 << 0, // 玩家控制的角色
    NPC = 1 << 2, // 非玩家控制角色
    Monster = 1 << 3, // 玩家的敌对生物
    Companion = 1 << 4, // 如宠物、伙伴等
    Max,
};

enum class EItemType : uint32_t
{
    None = 0,
    Weapon = 1 << 0, // 用于战斗等物品（如剑、刀等）
    Armor = 1 << 1, // 用于提供防御等装备
    Consumable = 1 << 2, // 使用后消耗的道具，如药剂
    Resource = 1 << 3, // 资源物品，如用于装备升级、锻造的道具
    Max,
};

enum class EVehicleType : uint32_t
{
    None = 0,
    Ground = 1 << 0, // 陆地上的载具，如汽车、坦克
    Air = 1 << 1, // 空中的载具，如飞机
    Water = 1 << 2, // 水中的载具，如船
    Max,
};

enum class InteractableType
{
    None = 0,
    QuestItem = 1 << 0, // 任务相关的道具
    Environmental = 1 << 1, // 如门、陷阱、机关
    Max,
};