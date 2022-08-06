#include "Player.hpp"
#include "Common/DataStructures.hpp"
#include "Graphics/GameRenderer.hpp"
#include "Common/InputEngine.hpp"
#include "Application.hpp"
#include <linavg/LinaVG.hpp>

namespace SM
{
    Vec2 playerTileSize = Vec2(320, 320);
    Vec2 movementSpeed  = Vec2(300, 300);
    Vec2 velocity       = Vec2(0, 0);
    int walkAnimCounter = 0;
    float walkAnimSwitchTime = 0.0f;
    float walkAnimLastSwitch = 0.0f;

    enum class PlayerState
    {
        Idle,
        Walk,
        Run
    };

    PlayerState playerState;

    void Player::Start()
    {
        Object::Start();
        m_idleTexture     = GameRenderer::_ptr->CreateTexture("Resources/Player/Idle.png");
        m_walkTextures[0] = GameRenderer::_ptr->CreateTexture("Resources/Player/Walk1.png");
        m_walkTextures[1] = GameRenderer::_ptr->CreateTexture("Resources/Player/Walk2.png");
        m_currentTexture  = m_idleTexture;
        playerState       = PlayerState::Idle;
    }

    void Player::Tick()
    {
        const float delta = Application::_ptr->GetDelta();

        Vec2 currentPos = m_pos;

        if (InputEngine::_ptr->GetKey(KEY_W))
            currentPos.y += movementSpeed.y * delta;

        if (InputEngine::_ptr->GetKey(KEY_S))
            currentPos.y -= movementSpeed.x * delta;

        if (InputEngine::_ptr->GetKey(KEY_A))
            currentPos.x += movementSpeed.x * delta;

        if (InputEngine::_ptr->GetKey(KEY_D))
            currentPos.x -= movementSpeed.x * delta;

        // Check current pos against collisions & walls etc.
        // If can still move

       //const Vec2 delta = currentPos - m_pos;
       //
       //if (glm::length(delta) > 0.0f)
       //    playerState = PlayerState::Walk;

        m_pos = currentPos;
    }

    void Player::Render()
    {
        LinaVG::StyleOptions opts;
        opts.textureHandle = m_currentTexture;
        LinaVG::DrawImage(m_currentTexture, m_pos, playerTileSize);
    }

    void Player::Animate()
    {
        if (playerState == PlayerState::Walk)
        {
            const float elapsed = Application::_ptr->GetElapsedTime();
            if (elapsed > walkAnimLastSwitch + walkAnimSwitchTime)
            {
                walkAnimLastSwitch = elapsed;
            }
            
        }
    }

} // namespace SM