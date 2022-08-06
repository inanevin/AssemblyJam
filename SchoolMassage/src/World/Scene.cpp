#include "Scene.hpp"
#include "Common/Utils.hpp"

namespace SM
{
    uint32_t OBJ_ID_COUNTER = 0;

    void Scene::Start()
    {
        for (auto& o : m_objects)
            o.Start();
    }

    void Scene::Tick()
    {
        for (auto& o : m_objects)
            o.Tick();
    }

    void Scene::Render()
    {
        for (auto& o : m_objects)
        {
            if (o.GetVisible())
                o.Render();
        }
    }

    void Scene::Unload()
    {
        LOG("Scene unloaded!");

        m_objects.clear();
    }

    void Scene::OnKey(int key, int action)
    {
        for (auto& o : m_objects)
            o.OnKey(key, action);
    }

    void Scene::OnMouse(int button, int action)
    {
        for (auto& o : m_objects)
            o.OnMouse(button, action);
    }

    void Scene::AddObject(Object& obj)
    {
        m_objects.push_back(obj);
        obj.ID = OBJ_ID_COUNTER++;
    }

    void Scene::RemoveObject(const Object& obj)
    {
        std::vector<Object>::iterator it = m_objects.begin();
        for (; it < m_objects.end(); it++)
        {
            if (it->ID == obj.ID)
            {
                m_objects.erase(it);
                break;
            }
        }
    }

    void Scene::RemoveObjectByName(const std::string& name)
    {
        std::vector<Object>::iterator it = m_objects.begin();
        for (; it < m_objects.end(); it++)
        {
            if (it->GetName().compare(name) == 0)
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
            if (obj.GetName().compare(name) == 0)
            {
                return &obj;
            }
        }

        return nullptr;
    }

    std::vector<Object*> Scene::FindObjectsByTag(const std::string& tag)
    {
        std::vector<Object*> objs;

        for (auto& obj : m_objects)
        {
            if (obj.GetTag().compare(tag) == 0)
            {
                objs.push_back(&obj);
            }
        }
        return objs;
    }

} // namespace SM