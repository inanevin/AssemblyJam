

#pragma once

#ifndef Window_HPP
#define Window_HPP

struct GLFWwindow;

#include "Common/DataStructures.hpp"
namespace SM
{
    class Window
    {
    public:
        Window()  = default;
        ~Window() = default;

        bool Initialize();
        void Shutdown();
        void Close();
        void Update();

        GLFWwindow* GetGLFWWindow()
        {
            return m_glfwWindow;
        }

        void SetSize(const Vec2i& newSize);
        void SetPos(const Vec2i& newPos);
        void SetPosCentered(const Vec2i& newPos);

        inline const Vec2i& GetSize()
        {
            return m_size;
        }
        inline const Vec2i& GetPos()
        {
            return m_pos;
        }
      
        static Window* _ptr;

    private:
        Vec2i       m_size       = Vec2i(0, 0);
        Vec2i       m_pos        = Vec2i(0, 0);
        GLFWwindow* m_glfwWindow = nullptr;
        void*       m_userPtr    = nullptr;
    };
} // namespace SM

#endif
