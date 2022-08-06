
#pragma once

#include "Common/DataStructures.hpp"
#include <unordered_map>

#ifndef InputEngine_HPP
#define InputEngine_HPP

namespace SM
{
    enum class InputAction
    {
        Pressed  = 0,
        Released = 1,
        Repeated = 2
    };

    // Cursor Modes
    enum class CursorMode
    {
        Visible  = 1 << 0,
        Hidden   = 1 << 1,
        Disabled = 1 << 2
    };

    class InputEngine
    {

    public:

        bool GetKey(int keyCode);
        bool GetKeyDown(int keyCode);
        bool GetKeyUp(int keyCode);
        bool GetMouseButton(int index);
        bool GetMouseButtonDown(int index);
        bool GetMouseButtonUp(int index);
        void SetCursorMode(CursorMode mode);
        void SetMousePosition(const Vec2& v) const;
        void OnWindowContextCreated(void* window);

        inline void OnScroll(double x, double y)
        {
            m_currentMouseScroll.x = static_cast<float>(x);
            m_currentMouseScroll.y = static_cast<float>(y);
        }

        /// <summary>
        /// 0,0 top-left, screenSizeX, screenSizeY bottom-right
        /// </summary>
        /// <returns></returns>
        Vec2        GetMousePosition();
        Vec2        GetRawMouseAxis();
        Vec2        GetMouseAxis();
        inline Vec2 GetMouseScroll()
        {
            return m_currentMouseScroll;
        }
        inline CursorMode GetCursorMode()
        {
            return m_cursorMode;
        }
        inline void SetAxisMousePos(const Vec2& v)
        {
            m_axisMousePos = v;
        }

        static InputEngine* _ptr;

    private:
        friend class Application;
        InputEngine()  = default;
        ~InputEngine() = default;
        void Initialize();
        void Tick();
        void Terminate();

    private:
        friend class Engine;
        int                          m_keyStatesDown[NUM_KEY_STATES];
        int                          m_keyStatesUp[NUM_KEY_STATES]       = {0};
        int                          m_mouseStatesDown[NUM_MOUSE_STATES] = {0};
        int                          m_mouseStatesUp[NUM_MOUSE_STATES]   = {0};
        std::unordered_map<int, int> m_keyDownNewStateMap;
        std::unordered_map<int, int> m_keyUpNewStateMap;
        std::unordered_map<int, int> m_mouseDownNewStateMap;
        std::unordered_map<int, int> m_mouseUpNewStateMap;
        CursorMode                   m_cursorMode         = CursorMode::Visible;
        Vec2                         m_currentMouseScroll = Vec2(0, 0);
        Vec2                         m_axisMousePos       = Vec2(0, 0);
    };
} // namespace SM

#endif
