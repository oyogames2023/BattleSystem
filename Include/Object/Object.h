#pragma once

#include "Forwards.h"
#include "ObjectGuid.h"

namespace zeus
{

    class BATTLE_API Object
        : public std::enable_shared_from_this<Object>
    {
    public:

        Object(const uint16_t majorType, const uint16_t subType, const uint32_t id);

        Object(const uint64_t id);

        virtual ~Object();

    public:

        virtual bool Initialize() = 0;

        virtual void SetInWorld(const bool isInWorld = true);

        virtual bool IsInWorld() const;

    public:

        void SetMajorType(const uint16_t majorType);

        uint16_t GetMajorType() const;

        void SetSubType(const uint16_t subType);

        uint16_t GetSubType() const;

        void SetObjectId(const uint32_t id);

        uint32_t GetObjectId() const;

        void SetName(const std::string& name);

        virtual const std::string GetName() const;

    protected:

        bool isInWorld_ = false;

    private:

        ObjectGuid guid_;

        std::string name_;
    };

} // namespace zeus