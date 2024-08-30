#pragma once

#include "Forwards.h"

namespace zeus
{

    struct ObjectGuid
    {
        ObjectGuid(const uint64_t id)
            : Id(id)
        {
        }

        ObjectGuid(const uint16_t majorType, const uint16_t subType
            , const uint32_t id)
            : parts { majorType, subType, id }
        {
        }

        void SetMajorType(const uint16_t majorType)
        {
            parts.MajorType = majorType;
        }

        uint16_t GetMajorType() const
        {
            return parts.MajorType;
        }

        void SetSubType(const uint16_t subType)
        {
            parts.SubType = subType;
        }

        uint16_t GetSubType() const
        {
            return parts.SubType;
        }

        void SetObjectId(const uint32_t id)
        {
            parts.ObjectId = id;
        }

        uint32_t GetObjectId() const
        {
            return parts.ObjectId;
        }

        void SetId(const uint64_t id)
        {
            Id = id;
        }

        uint64_t GetId() const
        {
            return Id;
        }

        ObjectGuid Clone() const
        {
            return ObjectGuid(Id);
        }

        union
        {
            struct
            {
                uint16_t MajorType;
                uint16_t SubType;
                uint32_t ObjectId;
            } parts;
            uint64_t Id;
        };
    };
    

} // namespace zeus