

#pragma once
#include "Common/Common.hpp"
#include "Object.hpp"

#include <vector>
#include <string>

#ifndef Player_HPP
#define Player_HPP

namespace SM
{
    class Player : public Object
    {
    public:
        Player() = default;
        ~Player(){};

        virtual void Start() override;
        virtual void Tick() override;
        virtual void Render() override;
        virtual void Unload() override;

        void Fire();

        static Player* _ptr;

    private:
        void Animate();

    private:
        GraphicsHandle m_currentTexture;
        GraphicsHandle m_idleTexture;
        GraphicsHandle m_walkTextures[2];
        Vec2           m_dir = Vec2(0, 0);
    };
} // namespace SM
#endif
