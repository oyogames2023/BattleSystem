#include "SceneObject.h"

namespace zeus
{

    SceneObject::SceneObject(const uint16_t majorType, const uint16_t subType, const uint32_t id)
        : Object(majorType, subType, id)
    {
    }

    SceneObject::~SceneObject()
    {
    }

    bool SceneObject::Initialize()
    {
        return true;
    }

    void SceneObject::EnterScene(SceneBasePtr scene, const math::Vector3& pos)
    {

    }

} // namespace zeus