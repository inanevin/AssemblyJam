#include "MainScene.hpp"
#include "Player.hpp"
#include "Common/InputEngine.hpp"

namespace SM
{
    Player player;

    void MainScene::Start()
    {
        player.Name = "Player";
        AddObject(&player);

        Scene::Start();
        //srand(0);
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
} // namespace SM