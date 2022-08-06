#include "Graphics/Window.hpp"
#include "Common/Common.hpp"
#include "Common/Utils.hpp"
#include "GameManager.hpp"
#include "Common/InputEngine.hpp"
#include <linavg/LinaVG.hpp>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace SM
{
    Window* Window::_ptr = 0;

    static void GLFWErrorCallback(int error, const char* desc)
    {
        LOG("GLFW Error: %s", desc);
    }

    bool Window::Initialize()
    {
        _ptr        = this;
        const int w = g_config.windowWidth;
        const int h = g_config.windowHeight;

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_SAMPLES, g_config.msaaSamples);
        glfwWindowHint(GLFW_DECORATED, g_config.decoratedWindow);
        glfwWindowHint(GLFW_RESIZABLE, g_config.resizableWindow);

        auto*              primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode           = glfwGetVideoMode(primaryMonitor);

        const bool fullScreen = false;
        m_glfwWindow          = (glfwCreateWindow(w, h, g_config.windowTitle, fullScreen ? primaryMonitor : NULL, NULL));
        float yScale          = 0.0f;
        glfwGetMonitorContentScale(primaryMonitor, &g_config.framebufferScale, &yScale);

        if (!m_glfwWindow)
        {
            // Assert window creation.
            return false;
        }

        // Set error callback
        glfwSetErrorCallback(GLFWErrorCallback);

        // Set context.
        glfwMakeContextCurrent(m_glfwWindow);

        // Load glad
        bool loaded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!loaded)
        {
            std::cerr << "LinaVG: GLAD Loader failed!" << std::endl;
            return false;
        }

        // Update OpenGL about the window data.
        glViewport(0, 0, w, h);

        glfwSwapInterval(0);

        // set user pointer for callbacks.
        glfwSetWindowUserPointer(m_glfwWindow, this);
        m_userPtr = static_cast<void*>(m_glfwWindow);

        auto windowResizeFunc = [](GLFWwindow* w, int wi, int he) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
            window->SetSize(Vec2i(wi, he));
            LinaVG::Config.displayWidth  = wi;
            LinaVG::Config.displayHeight = he;
        };

        auto windowCloseFunc = [](GLFWwindow* w) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
            window->Close();
        };

        auto windowKeyFunc = [](GLFWwindow* w, int key, int scancode, int action, int modes) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
            GameManager::_ptr->OnKey(key, action);
        };

        auto windowButtonFunc = [](GLFWwindow* w, int button, int action, int modes) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
            GameManager::_ptr->OnMouse(button, action);
        };

        auto windowMouseScrollFunc = [](GLFWwindow* w, double xOff, double yOff) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
            InputEngine::_ptr->OnScroll(xOff, yOff);
        };

        auto windowCursorPosFunc = [](GLFWwindow* w, double xPos, double yPos) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
        };

        auto windowFocusFunc = [](GLFWwindow* w, int f) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
        };

        // Register window callbacks.
        glfwSetFramebufferSizeCallback(m_glfwWindow, windowResizeFunc);
        glfwSetWindowCloseCallback(m_glfwWindow, windowCloseFunc);
        glfwSetKeyCallback(m_glfwWindow, windowKeyFunc);
        glfwSetMouseButtonCallback(m_glfwWindow, windowButtonFunc);
        glfwSetScrollCallback(m_glfwWindow, windowMouseScrollFunc);
        glfwSetCursorPosCallback(m_glfwWindow, windowCursorPosFunc);
        glfwSetWindowFocusCallback(m_glfwWindow, windowFocusFunc);
        InputEngine::_ptr->OnWindowContextCreated(m_userPtr);

        return true;
    }

    void Window::Shutdown()
    {

        glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
    }

    void Window::Update()
    {
        glfwSwapBuffers(m_glfwWindow);
    }

    void Window::SetSize(const Vec2i& size)
    {
        glfwSetWindowSize(m_glfwWindow, size.x, size.y);
        m_size = size;
    }

    void Window::SetPos(const Vec2i& pos)
    {
        glfwSetWindowPos(m_glfwWindow, pos.x, pos.y);
        m_pos = pos;
    }

    void Window::SetPosCentered(const Vec2i& newPos)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        SetPos(Vec2i((int)((float)mode->width / 2.0f + (float)newPos.x), (int)((float)mode->height / 2.0f + (float)newPos.y)));
    }

    void Window::Close()
    {
    }

} // namespace SM
