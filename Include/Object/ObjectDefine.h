#pragma once

#include "Forwards.h"

enum class EObjectMajorType : uint32_t
{
    None = 0,
    Entity = 1 << 0, // 鐢熺墿瀹炰綋锛堝鐜╁銆丯PC銆佹€墿绛夛級
    Item = 1 << 1, // 閬撳叿锛堝鎶ょ敳銆佹鍣ㄧ瓑锛?
    Vehicle = 1 << 2, // 杞藉叿锛堝鎽╂墭杞︺€佹苯杞︾瓑锛?
    Interactable = 1 << 3, // 浜や簰鐗╋紙濡傛満鍏崇瓑锛?
    Max,
};

enum class EEntityType : uint32_t
{
    None = 0,
    Player = 1 << 0, // 鐜╁鎺у埗鐨勮鑹?
    NPC = 1 << 2, // 闈炵帺瀹舵帶鍒惰鑹?
    Monster = 1 << 3, // 鐜╁鐨勬晫瀵圭敓鐗?
    Companion = 1 << 4, // 濡傚疇鐗┿€佷紮浼寸瓑
    Max,
};

enum class EItemType : uint32_t
{
    None = 0,
    Weapon = 1 << 0, // 鐢ㄤ簬鎴樻枟绛夌墿鍝侊紙濡傚墤銆佸垁绛夛級
    Armor = 1 << 1, // 鐢ㄤ簬鎻愪緵闃插尽绛夎澶?
    Consumable = 1 << 2, // 浣跨敤鍚庢秷鑰楃殑閬撳叿锛屽鑽墏
    Resource = 1 << 3, // 璧勬簮鐗╁搧锛屽鐢ㄤ簬瑁呭鍗囩骇銆侀敾閫犵殑閬撳叿
    Max,
};

enum class EVehicleType : uint32_t
{
    None = 0,
    Ground = 1 << 0, // 闄嗗湴涓婄殑杞藉叿锛屽姹借溅銆佸潶鍏?
    Air = 1 << 1, // 绌轰腑鐨勮浇鍏凤紝濡傞鏈?
    Water = 1 << 2, // 姘翠腑鐨勮浇鍏凤紝濡傝埞
    Max,
};

enum class InteractableType
{
    None = 0,
    QuestItem = 1 << 0, // 浠诲姟鐩稿叧鐨勯亾鍏?
    Environmental = 1 << 1, // 濡傞棬銆侀櫡闃便€佹満鍏?
    Max,
};
