
#pragma once
#include "Object.hpp"
#include <vector>
#include <string>

#include "World/Tilemap.hpp"

#ifndef Scene_HPP
#define Scene_HPP

namespace SM
{
    class Object;
    class Scene
    {
    public:
        Scene() = default;
        virtual ~Scene(){};

        virtual void Start();
        virtual void Tick();
        virtual void Render();
        virtual void Unload();
        virtual void OnKey(int key, int action);
        virtual void OnMouse(int button, int action);
        virtual void OnWindowResized(int oldW, int oldH, int newW, int newH);

        virtual void                 AddObject(Object* obj);
        virtual void                 RemoveObject(const Object* obj);
        virtual void                 RemoveObjectByName(const std::string& name);
        virtual Object*              FindObjectByName(const std::string& name);
        virtual std::vector<Object*> FindObjectsByTag(const std::string& tag);

    protected:
        std::vector<Object*> m_objects;
        Tilemap m_tilemap;
    };
} // namespace SM
#endif
