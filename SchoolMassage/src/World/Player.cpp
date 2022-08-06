#include "Player.hpp"
#include "Common/DataStructures.hpp"
#include "Graphics/GameRenderer.hpp"
#include <linavg/LinaVG.hpp>

namespace SM
{
    Vec2 playerTileSize = Vec2(64, 64);

    void Player::Start()
    {
        m_idleTexture     = GameRenderer::_ptr->CreateTexture("Resources/Player/Idle.png");
        m_walkTextures[0] = GameRenderer::_ptr->CreateTexture("Resources/Player/Walk1.png");
        m_walkTextures[1] = GameRenderer::_ptr->CreateTexture("Resources/Player/Walk2.png");
    }

    void Player::Tick()
    {
    }

    void Player::Render()
    {
        LinaVG::StyleOptions opts;

        LinaVG::DrawRect(glm::vec2(), glm::vec2(), opts);
    }

} // namespace SM