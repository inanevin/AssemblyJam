
#pragma once
#include "Object.hpp"
#include <vector>
#include <string>

#ifndef Scene_HPP
#define Scene_HPP

namespace SM
{
    class Object;
    class Scene
    {
    public:
        Scene() = default;
        ~Scene(){};

        virtual void Start();
        virtual void Tick();
        virtual void Render();
        virtual void Load();
        virtual void Unload();
        virtual void OnKey(int key, int action);
        virtual void OnMouse(int button, int action);

        virtual void                 AddObject(Object& obj);
        virtual void                 RemoveObject(const Object& obj);
        virtual void                 RemoveObjectByName(const std::string& name);
        virtual Object*              FindObjectByName(const std::string& name);
        virtual std::vector<Object*> FindObjectsByTag(const std::string& tag);

    protected:
        std::vector<Object> m_objects;
    };
} // namespace SM
#endif
