#include "Bullet.hpp"
#include "Common/Utils.hpp"
#include "Application.hpp"
#include "linavg/LinaVG.hpp"

namespace SM
{
    void Bullet::Start()
    {
        m_rotation = AngleBetween(m_direction, Vec2(0.0f, -1.0f));
    }

    void Bullet::Render()
    {
        LinaVG::StyleOptions opts;
        opts.textureHandle = m_texture;
        LinaVG::DrawImage(m_texture, m_pos, m_size, m_rotation);
    }

    void Bullet::Tick()
    {
        Object::Tick();
        m_pos += m_direction * m_speed * Application::_ptr->GetDelta();
    }
} // namespace SM