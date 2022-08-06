
#pragma once
#include "Common/DataStructures.hpp"

#ifndef Camera_HPP
#define Camera_HPP

namespace SM
{
    class Camera
    {
    public:
        Camera()  = default;
        ~Camera() = default;

        void Tick();

        float Zoom = 1.0f;
        Vec2  Pos  = Vec2(0, 0);
    };
} // namespace SM
#endif
