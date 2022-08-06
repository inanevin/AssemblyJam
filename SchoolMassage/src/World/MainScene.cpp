#include "MainScene.hpp"
#include "Player.hpp"
#include "Common/InputEngine.hpp"
#include "linavg/LinaVG.hpp"
#include "Graphics/GameRenderer.hpp"

namespace SM
{
    Player         player;
    GraphicsHandle hypahypa;

    void MainScene::Start()
    {
        player.m_name = "Player";
        AddObject(&player);

        Scene::Start();

        //srand(0);

        hypahypa = GameRenderer::_ptr->CreateTexture("Resources/hypahypa.jpg");
    }

    void MainScene::Tick()
    {
        Scene::Tick();
        m_cam.Tick();

        if (InputEngine::_ptr->GetKeyDown(KEY_SPACE))
        {
            m_cam.Shake(120.0f, 0.4f, 25);
        }
    }

    void MainScene::Render()
    {
        Scene::Render();
        const Vec2 pos = Vec2(g_config.windowWidth / 2.0f, g_config.windowHeight / 2.0f);
        LinaVG::DrawImage(hypahypa, pos, Vec2(300, 300));
    }
} // namespace SM