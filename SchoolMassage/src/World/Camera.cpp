#include "Camera.hpp"
#include "Common/Common.hpp"
#include "World/Player.hpp"
#include "Common/Utils.hpp"
#include "Application.hpp"
#include "linavg/LinaVG.hpp"

namespace SM
{
    void Camera::Shake(float pwr, float dur, float speed)
    {
        m_shakePower    = pwr;
        m_shakeDurCtr   = 0.0f;
        m_shakeDuration = dur;
        m_shakeSpeed    = speed;
        m_shake         = true;
        m_shakeRandom.x = RandF(0.5f, 2.0f);
        m_shakeRandom.y = RandF(0.5f, 2.0f);
    }

    void Camera::Tick()
    {
        if (Player::_ptr != 0)
        {
            const Vec2  pPos  = Player::_ptr->GetPos();
            const float delta = Application::_ptr->GetDelta();
            Pos.x             = Lerp(Pos.x, pPos.x, delta * 5);
            Pos.y             = Lerp(Pos.y, pPos.y, delta * 5);
        }

        const Vec2 center                       = Vec2(g_config.windowWidth, g_config.windowHeight) / 2.0f;
        const Vec2 finalPos                     = Pos - center;
        LinaVG::Config.debugOrthoProjectionZoom = 0.0f;
        LinaVG::Config.debugOrthoOffset.x       = finalPos.x;
        LinaVG::Config.debugOrthoOffset.y       = finalPos.y;

        if (m_shake)
        {
            if (m_shakeDurCtr < m_shakeDuration)
            {
                const float delta = Application::_ptr->GetDelta();
                m_shakeDurCtr += delta;
                Pos.x += std::sin(Application::_ptr->GetElapsedTime() * m_shakeRandom.x * m_shakeSpeed) * m_shakePower * delta;
                Pos.y += std::sin(Application::_ptr->GetElapsedTime() * m_shakeRandom.y * m_shakeSpeed) * m_shakePower * delta;
            }
            else
            {
                LinaVG::Config.debugRotateDegrees = 0.0f;
                m_shake                           = false;
            }
        }
    }
} // namespace SM