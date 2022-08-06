#include "Camera.hpp"
#include "Common/Common.hpp"
#include "World/Player.hpp"
#include "Common/Utils.hpp"
#include "Application.hpp"
#include "linavg/LinaVG.hpp"

namespace SM
{
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
    }
} // namespace SM