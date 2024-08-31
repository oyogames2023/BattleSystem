#include "Player.h"
#include "ObjectDefine.h"

namespace zeus
{

    Player::Player(const uint32_t id)
        : Actor(static_cast<uint16_t>(EObjectMajorType::Entity)
            , static_cast<uint16_t>(EEntityType::Player), id)
    {
    }

    Player::~Player()
    {
    }

} // namespace zeus