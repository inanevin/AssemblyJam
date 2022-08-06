#include "Player.hpp"
#include "Common/DataStructures.hpp"
#include "Graphics/GameRenderer.hpp"
#include "Common/InputEngine.hpp"
#include "Application.hpp"
#include "Common/Utils.hpp"
#include "glm/gtx/norm.hpp"
#include "Bullet.hpp"
#include "Scene.hpp"
#include <linavg/LinaVG.hpp>

namespace SM
{
    Player* Player::_ptr = nullptr;

    int   walkAnimCounter    = 0;
    float walkAnimSwitchTime = 0.1f;
    float walkAnimLastSwitch = 0.0f;
    float movementSpeed      = 500.0f;

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
        _ptr              = this;

        // Movement properties
        m_pos.x = g_config.windowWidth / 2.0f;
        m_pos.y = g_config.windowHeight / 2.0f;

        m_size        = Vec2(128, 128);
        m_renderDebug = true;
    }

    void Player::Tick()
    {
        const float delta = Application::_ptr->GetDelta();

        Vec2 currentPos = m_pos;
        Vec2 input      = Vec2(InputEngine::_ptr->GetHorizontalAxis(), -InputEngine::_ptr->GetVerticalAxis());

        if (glm::length2(input) > 0.1f)
            playerState = PlayerState::Walk;
        else
            playerState = PlayerState::Idle;

        m_pos += input * delta * movementSpeed;

        const Vec2 mousePos  = InputEngine::_ptr->GetMousePosition();
        const Vec2 mousePerc = Vec2(mousePos.x / g_config.windowWidth, mousePos.y / g_config.windowHeight);
        const Vec2 toMouse   = mousePerc - Vec2(0.5f, 0.5f);
        float      angle     = AngleBetween(Vec2(0.0f, -1.0f), glm::normalize(toMouse));
        m_dir                = toMouse;

        if (angle < 0.0f)
            angle = 360.0f + angle;

        m_rotation = angle;

        Animate();

        if (InputEngine::_ptr->GetMouseButtonDown(0))
        {
            Fire();
        }
    }

    void Player::Render()
    {
        LinaVG::StyleOptions opts;
        opts.color = LinaVG::Vec4(1, 0, 0, 1);

        LinaVG::DrawRect(Vec2(0, 0), Vec2(100, 100), opts);

        opts.color = LinaVG::Vec4(1, 1, 0, 1);
        LinaVG::DrawRect(Vec2(g_config.windowWidth - 100, 0), Vec2(g_config.windowWidth, 100), opts);

        opts.color = LinaVG::Vec4(1, 1, 1, 1);
        LinaVG::DrawRect(Vec2(g_config.windowWidth - 100, g_config.windowHeight - 100), Vec2(g_config.windowWidth, g_config.windowHeight), opts);

        opts.color = LinaVG::Vec4(0, 1, 1, 1);
        LinaVG::DrawRect(Vec2(0, g_config.windowHeight - 100), Vec2(100, g_config.windowHeight), opts);

        opts.textureHandle = m_currentTexture;
        m_drawOrder        = 10;
        LinaVG::DrawImage(m_currentTexture, m_pos, m_size, m_rotation, m_drawOrder);
    }

    void Player::Unload()
    {
        _ptr = 0;
    }

    void Player::Fire()
    {
        Bullet* b = new Bullet();
        b->m_pos  = m_pos;
        b->SetDirection(m_dir);
        b->SetSpeed(4500);
        GameManager::_ptr->GetCurrentScene()->AddObject(b);

    }

    void Player::Animate()
    {
        if (playerState == PlayerState::Walk)
        {
            const float elapsed = Application::_ptr->GetElapsedTime();
            if (elapsed > walkAnimLastSwitch + walkAnimSwitchTime)
            {
                walkAnimLastSwitch = elapsed;
                m_currentTexture   = m_walkTextures[walkAnimCounter];
                walkAnimCounter++;

                if (walkAnimCounter > 1)
                    walkAnimCounter = 0;
            }
        }
        else
        {
            m_currentTexture = m_idleTexture;
        }
    }

} // namespace SM