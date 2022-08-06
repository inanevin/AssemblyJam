
#pragma once
#include "Common/DataStructures.hpp"
#include "Object.hpp"

#ifndef Bullet_HPP
#define Bullet_HPP

namespace SM
{
    class Bullet : public Object
    {
    public:
        Bullet()  = default;
        ~Bullet() = default;

        virtual void Start() override;
        virtual void Render() override;
        virtual void Tick() override;

        inline void SetDirection(const Vec2& dir)
        {
            m_direction = dir;
        }

        inline void SetSpeed(float speed)
        {
            m_speed = speed;
        }

        inline void SetTexture(GraphicsHandle texture)
        {
            m_texture = texture;
        }

    private:
        GraphicsHandle m_texture;
        Vec2           m_direction;
        float          m_speed;
    };

} // namespace SM
#endif
