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
        virtual void Unload(){};

        inline Vec2& GetPos()
        {
            return m_pos;
        }

        uint32_t    ID        = 0;
        std::string Name      = "";
        std::string Tag       = "";
        bool        IsVisible = true;

    protected:
        Vec2 m_pos = Vec2(0, 0);
    };
} // namespace SM
#endif
