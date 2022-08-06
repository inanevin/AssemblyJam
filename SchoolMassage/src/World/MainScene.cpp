#include "MainScene.hpp"
#include "Player.hpp"

namespace SM
{
	Player player;

	void MainScene::Start()
	{
		player.Name = "Player";
		AddObject(&player);

		Scene::Start();
	}
}