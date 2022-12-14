#include "Application.hpp"
#include "Common/Utils.hpp"
#include "Common/Common.hpp"
#include "linavg/LinaVG.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

namespace SM
{
    Application* Application::_ptr = 0;

    void Application::Run()
    {
        _ptr = this;

        if (!m_window.Initialize())
        {
            LOG("Window init failure :(");
            return;
        }

        // note(nicolas): just to test that working dir is correct
        auto v = ReadFile("Resources/map.txt");
        LOG("DEBUG map text file size: %u", v.size());

        m_inputEngine.Initialize();
        m_renderer.Initialize();

        double lastTime    = glfwGetTime();
        double lastFPSTime = lastTime;
        int    totalFrames = 0;

        m_gameManager.OnStart();

        while (true)
        {
            const double time = glfwGetTime();
            m_delta           = time - lastTime;
            lastTime          = time;

            if (time - lastFPSTime >= 1.0f)
            {
                lastFPSTime += 1.0f;
                totalFrames = 0;
            }

            m_inputEngine.Tick();

            // Update game
            m_gameManager.OnTick();

            // Clear renderer & call game render.
            m_renderer.Clear();

            LinaVG::StartFrame();
            m_gameManager.OnRender();
            LinaVG::Render();
            LinaVG::EndFrame();

            // Swap
            m_window.Update();

            totalFrames++;
        }

        m_gameManager.OnEnd();
        m_renderer.Terminate();
        m_inputEngine.Terminate();
    }
    double Application::GetElapsedTime()
    {
        return glfwGetTime();
    }
} // namespace SM
