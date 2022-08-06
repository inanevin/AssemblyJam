
#pragma once

#include "Common/DataStructures.hpp"

#ifndef GameManager_HPP
#define GameManager_HPP

namespace SM
{
    class Scene;

    class GameManager
    {
    public:
        GameManager()  = default;
        ~GameManager() = default;

        void OnStart();
        void OnTick();
        void OnRender();
        void OnEnd();
        void SwitchScene(Scene* toLoad);
        void OnKey(int key, int action);
        void OnMouse(int button, int action);


        static GameManager* _ptr;

    private:
        Vec2   m_scrollOffset;
        Scene* m_currentScene = 0;
    };
} // namespace SM
#endif
