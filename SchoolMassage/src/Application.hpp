
#pragma once

#include "Graphics/Window.hpp"
#include "Graphics/GameRenderer.hpp"
#include "GameManager.hpp"

#ifndef App_HPP
#define App_HPP

namespace SM
{
    class Application
    {
    public:
        Application() = default;
        ~Application(){};

        void Run();

        inline double GetFPS()
        {
            return m_fps;
        }
        inline double GetDelta()
        {
            return m_delta;
        }

        static Application* _ptr;

    private:
        int          m_fps   = 0;
        double       m_delta = 0;
        Window       m_window;
        GameRenderer m_renderer;
        GameManager m_gameManager;
    };
} // namespace SM
#endif
