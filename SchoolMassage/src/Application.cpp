#include "Application.hpp"
#include "Common/Utils.hpp"
#include "Common/Common.hpp"
#include "Graphics/Window.hpp"
#include "Graphics/GameRenderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace SM
{
    void Application::Run()
    {
        Window w;

        if (!w.Initialize())
        {
            LOG("Window init failure :(");
            return;
        }

        auto v = ReadFile("Resources/map.txt");
        LOG("DEBUG map text file size: %u", v.size());

        GameRenderer renderer;
        renderer.Initialize();

        double lastTime = glfwGetTime();
        double lastFPSTime = lastTime;
        int    totalFrames = 0;

        while (true)
        {
            const double time = glfwGetTime();
            const double delta = lastTime - time;
            lastTime = time;

            if (time - lastFPSTime >= 1.0f)
            {
                lastFPSTime += 1.0f;
                totalFrames = 0;
            }

            w.Update();
            renderer.Render();
            totalFrames++;
        }

        renderer.Terminate();
    }
}
