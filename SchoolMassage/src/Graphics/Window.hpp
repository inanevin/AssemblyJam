

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


        Window() = default;
        ~Window() = default;

        bool Initialize();
        void Shutdown();
        void Close();
        void Update();

        GLFWwindow* GetGLFWWindow()
        {
            return m_glfwWindow;
        }

        void SetSize(const Vector2i& newSize);
        void SetPos(const Vector2i& newPos);
        void SetPosCentered(const Vector2i& newPos);

        inline const Vector2i& GetSize()
        {
            return m_size;
        }
        inline const Vector2i& GetPos()
        {
            return m_pos;
        }

        static Window* Get()
        {
            return s_instance;
        }

    private:


        Vector2i       m_size = Vector2i(0, 0);
        Vector2i       m_pos = Vector2i(0, 0);
        static Window* s_instance;
        GLFWwindow* m_glfwWindow = nullptr;
        void* m_userPtr = nullptr;
    }; 
}

#endif
