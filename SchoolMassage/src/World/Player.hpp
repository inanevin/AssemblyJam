
#pragma once
#include "Common/Common.hpp"
#include "Object.hpp"
#include <vector>
#include <string>

#ifndef Scene_HPP
#define Scene_HPP

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

    private:
        
        GraphicsHandle m_idleTexture;
        GraphicsHandle m_walkTextures[2];
    };
} // namespace SM
#endif
