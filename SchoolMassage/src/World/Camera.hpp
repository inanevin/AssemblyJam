
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

        void Shake(float pwr, float dur, float speed);
        void Tick();

        float Zoom = 1.0f;
        Vec2  Pos  = Vec2(0, 0);

    private:
        float m_shakeDurCtr   = 0.0f;
        float m_shakeDuration = 0.0f;
        bool  m_shake         = false;
        float m_shakePower    = 0.0f;
        float m_shakeSpeed    = 0.0f;
        Vec2  m_shakeRandom   = Vec2(0.0f, 0.0f);
    };
} // namespace SM
#endif
