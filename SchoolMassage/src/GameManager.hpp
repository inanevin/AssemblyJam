
#pragma once

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

        static GameManager* _ptr;

    private:

        Scene* m_currentScene = 0;
    };
} // namespace SM
#endif
