#include "GameManager.hpp"
#include "World/Scene.hpp"
#include "Common/InputEngine.hpp"
#include "Common/Utils.hpp"
#include "Graphics/GameRenderer.hpp"
#include "Common/Common.hpp"
#include "World/MainScene.hpp"

namespace SM
{
    GameManager* GameManager::_ptr = 0;
    MainScene    mainScene;

    void GameManager::OnStart()
    {
        _ptr = this;
        SwitchScene(&mainScene);
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
        m_currentScene->Start();
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

    void GameManager::OnWindowResized(int oldW, int oldH, int newW, int newH)
    {
        if (!m_currentScene)
            return;
        m_currentScene->OnWindowResized(oldW, oldH, newW, newH);
    }

} // namespace SM
