#pragma once

#include "Common/DataStructures.hpp"
#include <string>

#ifndef Object_HPP
#define Object_HPP

namespace SM
{
    class Object
    {
    public:
        Object() = default;
        virtual ~Object(){};

        virtual void Start(){};
        virtual void Tick(){};
        virtual void Render(){};
        virtual void OnKey(int key, int action){};
        virtual void OnMouse(int button, int action){};
        virtual void OnWindowResized(int oldW, int oldH, int newW, int newH)
        {
            const Vec2 perc = Vec2(m_pos.x / oldW, m_pos.y / oldH);
            m_pos.x         = perc.x * newW;
            m_pos.y         = perc.y * newH;
        }

        virtual void Unload(){};

        inline Vec2& GetPos()
        {
            return m_pos;
        }

        inline Vec2& GetSize()
        {
            return m_size;
        }

        uint32_t    ID        = 0;
        std::string Name      = "";
        std::string Tag       = "";
        bool        IsVisible = true;

    protected:

        Vec2  m_pos      = Vec2(0, 0);
        Vec2  m_size     = Vec2(128, 128);
        float m_rotation = 0.0f;
    };
} // namespace SM
#endif
