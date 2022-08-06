#include "GameManager.hpp"
#include "World/Scene.hpp"
#include "Common/InputEngine.hpp"
#include "Common/Utils.hpp"

namespace SM
{
    GameManager* GameManager::_ptr = 0;
    Scene test;

    void GameManager::OnStart()
    {
        _ptr = this;
        m_currentScene = &test;
    }

    void GameManager::OnTick()
    {
        if (!m_currentScene)
            return;
        m_currentScene->Tick();
    }

    void GameManager::OnRender()
    {
        if (!m_currentScene)
            return;

        m_currentScene->Render();
    }

    void GameManager::OnEnd()
    {
    }

    void GameManager::SwitchScene(Scene* toLoad)
    {
        if (m_currentScene)
            m_currentScene->Unload();
        m_currentScene = toLoad;
        m_currentScene->Load();
    }

    void GameManager::OnKey(int key, int action)
    {
        if (!m_currentScene)
            return;



        m_currentScene->OnKey(key, action);
    }

    void GameManager::OnMouse(int button, int action)
    {
        if (!m_currentScene)
            return;
        m_currentScene->OnMouse(button, action);
    }

} // namespace SM
