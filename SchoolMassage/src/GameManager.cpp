#include "GameManager.hpp"
#include "World/Scene.hpp"
#include "Common/InputEngine.hpp"
#include "Common/Utils.hpp"
#include "linavg/LinaVG.hpp"
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

        LinaVG::StartFrame();

        LinaVG::StyleOptions opts;
        opts.isFilled = true;
        opts.color = LinaVG::Vec4(1,0,0,1);
        static float wtf = 0.0f;
        wtf += 1.0f;
        LinaVG::DrawRect(LinaVG::Vec2(0,wtf), LinaVG::Vec2(200, 200), opts);
        LinaVG::Render();
        LinaVG::EndFrame();

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

} // namespace SM
