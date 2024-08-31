#pragma once

#include "Forwards.h"

namespace zeus
{

    class SceneBase
    {
    public:

        SceneBase();

        virtual ~SceneBase();

    public:

    private:

        std::unordered_map<uint64_t, ActorPtr> actors_;
    };

} // namespace zeus