#pragma once

#include "Commom.h"

namespace zeus
{

    struct ObjectGuid;
    using ObjectGuidPtr = std::shared_ptr<ObjectGuid>;

    class Object;
    using ObjectPtr = std::shared_ptr<Object>;

    class Actor;
    using ActorPtr = std::shared_ptr<Actor>;

    class Player;
    using PlayerPtr = std::shared_ptr<Player>;

    class Npc;
    using NpcPtr = std::shared_ptr<Npc>;

    class Monster;
    using MonsterPtr = std::shared_ptr<Monster>;

    class SceneBase;
    using SceneBasePtr = std::shared_ptr<SceneBase>;

    struct Vector3;

    class DateTime;
    using DateTimePtr = std::shared_ptr<DateTime>;

    class ExcelParser;
    using ExcelParserPtr = std::shared_ptr<ExcelParser>;

    class GameConfigGenerator;
    using GameConfigGeneratorPtr = std::shared_ptr<GameConfigGenerator>;

} // namespace zeus

namespace zeus::battle
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

} // namespace zeus::battle

namespace zeus::network
{

    class EventLoop;
    using EventLoopPtr = std::shared_ptr<EventLoop>;

    class AcceptorBase;
    using AcceptorBasePtr = std::shared_ptr<AcceptorBase>;

    class ConnectorBase;
    using ConnectorBasePtr = std::shared_ptr<ConnectorBase>;

    class ClientBase;
    using ClientBasePtr = std::shared_ptr<ClientBase>;

    class TCPClient;
    using TCPClientPtr = std::shared_ptr<TCPClient>;

    class UDPClient;
    using UDPClientPtr = std::shared_ptr<UDPClient>;

} // namespace zeus::network
