

#include "InputEngine.hpp"
#include "Common/Utils.hpp"

#include <glm/glm.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace SM
{
#define AXIS_SENSITIVITY  0.1f
#define MOUSE_SENSITIVITY 5.0f
    GLFWwindow*  glfwWindow        = nullptr;
    InputEngine* InputEngine::_ptr = 0;

    void InputEngine::Initialize()
    {
        _ptr = this;
    }

    void InputEngine::OnWindowContextCreated(void* window)
    {
        glfwWindow = static_cast<GLFWwindow*>(window);
    }

    bool InputEngine::GetKey(int keycode)
    {
        int state = glfwGetKey(glfwWindow, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool InputEngine::GetKeyDown(int keyCode)
    {
        int  newState                 = glfwGetKey(glfwWindow, keyCode);
        bool flag                     = (newState == GLFW_PRESS && m_keyStatesDown[keyCode] == GLFW_RELEASE) ? true : false;
        m_keyDownNewStateMap[keyCode] = newState;
        return flag;
    }
    bool InputEngine::GetKeyUp(int keyCode)
    {
        int  newState               = glfwGetKey(glfwWindow, keyCode);
        bool flag                   = (newState == GLFW_RELEASE && m_keyStatesUp[keyCode] == GLFW_PRESS) ? true : false;
        m_keyUpNewStateMap[keyCode] = newState;
        return flag;
    }
    bool InputEngine::GetMouseButton(int button)
    {
        int state = glfwGetMouseButton(glfwWindow, button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    bool InputEngine::GetMouseButtonDown(int button)
    {
        int  newState                  = glfwGetMouseButton(glfwWindow, button);
        bool flag                      = (newState == GLFW_PRESS && m_mouseStatesDown[button] == GLFW_RELEASE) ? true : false;
        m_mouseDownNewStateMap[button] = newState;
        return flag;
    }
    bool InputEngine::GetMouseButtonUp(int button)
    {
        int  newState                = glfwGetMouseButton(glfwWindow, button);
        bool flag                    = (newState == GLFW_RELEASE && m_mouseStatesUp[button] == GLFW_PRESS) ? true : false;
        m_mouseUpNewStateMap[button] = newState;
        return flag;
    }

    Vec2 InputEngine::GetRawMouseAxis()
    {
        // Get the cursor position.
        double posX, posY;
        glfwGetCursorPos(glfwWindow, &posX, &posY);

        // Get the delta mouse position.
        Vec2 currentMousePosition = Vec2((float)posX, (float)posY);
        Vec2 diff                 = currentMousePosition - m_axisMousePos;
        Vec2 raw                  = Vec2(0, 0);

        // Set raw axis values depending on the direction of the axis.
        if (diff.x > 0.0f)
            raw.x = 1.0f;
        else if (diff.x < 0.0f)
            raw.x = -1.0f;
        if (diff.y > 0)
            raw.y = 1.0f;
        else if (diff.y < 0)
            raw.y = -1.0f;

        // Set previous position.
        m_axisMousePos = currentMousePosition;

        // Return raw.
        return raw;
    }

    Vec2 InputEngine::GetMouseAxis()
    {
        double posX, posY;
        glfwGetCursorPos(glfwWindow, &posX, &posY);

        // Delta
        Vec2 diff = Vec2((float)(posX - m_axisMousePos.x), (float)(posY - m_axisMousePos.y));
        // Clamp and remap delta mouse position.
        diff.x = glm::clamp(diff.x, -MOUSE_SENSITIVITY, MOUSE_SENSITIVITY);
        diff.y = glm::clamp(diff.y, -MOUSE_SENSITIVITY, MOUSE_SENSITIVITY);
        diff.x = Remap(diff.x, -MOUSE_SENSITIVITY, MOUSE_SENSITIVITY, -1.0f, 1.0f);
        diff.y = Remap(diff.y, -MOUSE_SENSITIVITY, MOUSE_SENSITIVITY, -1.0f, 1.0f);

        // Set the previous position.
        m_axisMousePos = Vec2((float)posX, (float)posY);

        return diff;
    }

    Vec2 InputEngine::GetMousePosition()
    {
        double xpos, ypos;
        glfwGetCursorPos(glfwWindow, &xpos, &ypos);
        return Vec2((float)xpos, (float)ypos);
    }

    void InputEngine::SetCursorMode(CursorMode mode)
    {
        m_cursorMode = mode;

        switch (mode)
        {
        case CursorMode::Visible:
            glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;

        case CursorMode::Hidden:
            glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            break;

        case CursorMode::Disabled:
            glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        }
    }

    void InputEngine::SetMousePosition(const Vec2& v) const
    {
        glfwSetCursorPos(glfwWindow, v.x, v.y);
    }

    void InputEngine::Tick()
    {
        // Refresh the key states from previous frame.
        for (auto& pair : m_keyDownNewStateMap)
            m_keyStatesDown[pair.first] = m_keyDownNewStateMap[pair.first];

        for (auto& pair : m_keyUpNewStateMap)
            m_keyStatesUp[pair.first] = m_keyUpNewStateMap[pair.first];

        for (auto& pair : m_mouseDownNewStateMap)
            m_mouseStatesDown[pair.first] = m_mouseDownNewStateMap[pair.first];

        for (auto& pair : m_mouseUpNewStateMap)
            m_mouseStatesUp[pair.first] = m_mouseUpNewStateMap[pair.first];

        m_keyDownNewStateMap.clear();
        m_keyUpNewStateMap.clear();
        m_mouseDownNewStateMap.clear();
        m_mouseUpNewStateMap.clear();

        glfwPollEvents();
    }

    void InputEngine::Terminate()
    {
        m_keyDownNewStateMap.clear();
        m_keyUpNewStateMap.clear();
        m_mouseDownNewStateMap.clear();
        m_mouseUpNewStateMap.clear();
    }
} // namespace SM
