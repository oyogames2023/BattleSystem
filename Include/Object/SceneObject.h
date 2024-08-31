#pragma once

#include "Object.h"
#include "Vector3.h"

namespace zeus
{

    class BATTLE_API SceneObject
        : public Object
    {
    public:

        SceneObject(const uint16_t majorType, const uint16_t subType, const uint32_t id);

        virtual ~SceneObject();

    public:

        bool Initialize() override;

    public:

        virtual void EnterScene(SceneBasePtr scene, const math::Vector3& pos);

    private:

        SceneBasePtr scene_ = nullptr;

        math::Vector3 location_;

        math::Vector3 rotation_;

        math::Vector3 scale_;

        double orientation_;
    };

} // namespace zeus