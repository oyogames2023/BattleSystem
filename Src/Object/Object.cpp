#include "Object.h"

namespace zeus
{

    Object::Object(const uint16_t majorType, const uint16_t subType
        , const uint32_t id)
        : guid_(majorType, subType, id)
    {
    }

    Object::Object(const uint64_t id)
        : guid_(id)
    {
    }

    void Object::SetInWorld(const bool isInWorld)
    {
        isInWorld_ = isInWorld;
    }

    bool Object::IsInWorld() const
    {
        return isInWorld_;
    }

    void Object::SetMajorType(const uint16_t majorType)
    {
        guid_.SetMajorType(majorType);
    }

    uint16_t Object::GetMajorType() const
    {
        return guid_.GetMajorType();
    }

    void Object::SetSubType(const uint16_t subType)
    {
        guid_.SetSubType(subType);
    }

    uint16_t Object::GetSubType() const
    {
        return guid_.GetSubType();
    }

    void Object::SetObjectId(const uint32_t id)
    {
        guid_.SetObjectId(id);
    }

    uint32_t Object::GetObjectId() const
    {
        return guid_.GetObjectId();
    }

    void Object::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string Object::GetName() const
    {
        return name_;
    }

} // namespace zeus