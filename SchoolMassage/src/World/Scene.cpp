#include "Scene.hpp"
#include "Common/Utils.hpp"
#include "linavg/LinaVG.hpp"

namespace SM
{
    uint32_t OBJ_ID_COUNTER = 0;

    void Scene::Start()
    {
      //  m_tilemapWorld.Start();

        for (auto o : m_objects)
            o->Start();
    }

    void Scene::Tick()
    {
        m_tilemapWorld.Tick();

        for (auto o : m_objects)
            o->Tick();
    }

    void Scene::Render()
    {
        // m_tilemapWorld.Render();

        for (auto o : m_objects)
        {
            if (o->m_visible)
            {
                o->Render();

                if (o->m_renderDebug)
                {
                    LinaVG::StyleOptions opts;
                    opts.isFilled  = false;
                    opts.thickness = 1.5f;
                    opts.color = LinaVG::Vec4(1,0,0,1);
                    const Vec2 tl  = o->m_pos - o->m_size / 2.0f;
                    const Vec2 br  = o->m_pos + o->m_size / 2.0f;
                    LinaVG::DrawRect(tl, br, opts);
                }
            }
        }
    }

    void Scene::Unload()
    {
        LOG("Scene unloaded!");

        for (auto o : m_objects)
            o->Unload();

        m_tilemapWorld.Unload();
        m_objects.clear();
    }

    void Scene::OnKey(int key, int action)
    {
        for (auto& o : m_objects)
            o->OnKey(key, action);
    }

    void Scene::OnMouse(int button, int action)
    {
        for (auto o : m_objects)
            o->OnMouse(button, action);
    }

    void Scene::OnWindowResized(int oldW, int oldH, int newW, int newH)
    {
        for (auto o : m_objects)
            o->OnWindowResized(oldW, oldH, newW, newH);
    }

    void Scene::AddObject(Object* obj)
    {
        m_objects.push_back(obj);
        obj->m_id = OBJ_ID_COUNTER++;
    }

    void Scene::RemoveObject(const Object* obj)
    {
        std::vector<Object*>::iterator it = m_objects.begin();
        for (; it < m_objects.end(); it++)
        {
            if (*it == obj)
            {
                m_objects.erase(it);
                break;
            }
        }
    }

    void Scene::RemoveObjectByName(const std::string& name)
    {
        std::vector<Object*>::iterator it = m_objects.begin();
        for (; it < m_objects.end(); it++)
        {
            if ((*it)->m_name.compare(name) == 0)
            {
                m_objects.erase(it);
                break;
            }
        }
    }

    Object* Scene::FindObjectByName(const std::string& name)
    {
        for (auto& obj : m_objects)
        {
            if (obj->m_name.compare(name) == 0)
            {
                return obj;
            }
        }

        return nullptr;
    }

    std::vector<Object*> Scene::FindObjectsByTag(const std::string& tag)
    {
        std::vector<Object*> objs;

        for (auto& obj : m_objects)
        {
            if (obj->m_tag.compare(tag) == 0)
            {
                objs.push_back(obj);
            }
        }
        return objs;
    }

} // namespace SM