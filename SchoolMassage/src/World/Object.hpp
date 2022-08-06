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
        ~Object(){};

        virtual void Start(){};
        virtual void Tick(){};
        virtual void Render(){};
        virtual void OnKey(int key, int action) {};
        virtual void OnMouse(int button, int action){};

        inline bool  GetVisible()
        {
            return m_isVisible;
        }
        inline std::string& GetName()
        {
            return m_name;
        }
        inline Vec2 GetPos()
        {
            return m_pos;
        }

        inline std::string& GetTag()
        {
            return m_tag;
        }

        uint32_t ID = 0;

    protected:
        std::string m_name      = "";
        std::string m_tag       = "";
        bool        m_isVisible = false;
        Vec2        m_pos       = Vec2(0, 0);
    };
} // namespace SM
#endif
