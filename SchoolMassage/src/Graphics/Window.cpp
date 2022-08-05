#include "Graphics/Window.hpp"
#include <GLFW/glfw3.h>

namespace SM
{
    Window* Window::s_instance = nullptr;

    static void GLFWErrorCallback(int error, const char* desc)
    {
    }

    bool Window::Initialize(int w, int h)
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // glfwWindowHint(GLFW_DECORATED, appInfo.windowProperties.decorated);
        // glfwWindowHint(GLFW_RESIZABLE, appInfo.windowProperties.resizable);

        auto*              primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode           = glfwGetVideoMode(primaryMonitor);

        const bool fullScreen = false;
        m_glfwWindow          = (glfwCreateWindow(w, h, "School Massage", fullScreen ? primaryMonitor : NULL, NULL));
        // glfwGetMonitorContentScale(primaryMonitor, &(appInfo.windowProperties.contentScaleWidth), &(appInfo.windowProperties.contentScaleHeight));

        if (!m_glfwWindow)
        {
            // Assert window creation.
            return false;
        }

        m_userPtr = static_cast<void*>(m_glfwWindow);

        // Set error callback
        glfwSetErrorCallback(GLFWErrorCallback);

        glfwSetWindowUserPointer(m_glfwWindow, this);

        auto windowResizeFunc = [](GLFWwindow* w, int wi, int he) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
            window->SetSize(Vector2i(wi, he));
        };

        auto windowCloseFunc = [](GLFWwindow* w) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
            window->Close();
        };

        auto windowKeyFunc = [](GLFWwindow* w, int key, int scancode, int action, int modes) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
        };

        auto windowButtonFunc = [](GLFWwindow* w, int button, int action, int modes) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
        };

        auto windowMouseScrollFunc = [](GLFWwindow* w, double xOff, double yOff) {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
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

        return true;
    }

    void Window::Shutdown()
    {

        glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
    }

    void Window::SetSize(const Vector2i& size)
    {
        glfwSetWindowSize(m_glfwWindow, size.x, size.y);
        m_size = size;
    }

    void Window::SetPos(const Vector2i& pos)
    {
        glfwSetWindowPos(m_glfwWindow, pos.x, pos.y);
        m_pos = pos;
    }

    void Window::SetPosCentered(const Vector2i& newPos)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        SetPos(Vector2i((int)((float)mode->width / 2.0f + (float)newPos.x), (int)((float)mode->height / 2.0f + (float)newPos.y)));
    }

    void Window::Close()
    {
    }

} // namespace SM
