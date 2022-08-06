#include "GameManager.hpp"
#include "World/Scene.hpp"

namespace SM
{
    GameManager* GameManager::_ptr = 0;

    void GameManager::OnStart()
    {
        _ptr = this;
    }

    void GameManager::OnTick()
    {
        if(!m_currentScene) return;
        m_currentScene->Tick();
    }

    void GameManager::OnRender()
    {
        if (!m_currentScene) return;

        m_currentScene->Render();
    }

    void GameManager::OnEnd()
    {
    }

} // namespace SM
