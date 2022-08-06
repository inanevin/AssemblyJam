
#pragma once
#include "Scene.hpp"
#include "Camera.hpp"
#include <vector>
#include <string>

#ifndef MainScene_HPP
#define MainScene_HPP

namespace SM
{
    class MainScene : public Scene
    {
    public:
        MainScene() = default;
        virtual ~MainScene(){};

        virtual void Start() override;
        virtual void Tick() override;
        virtual void Render() override;

    private:
        Camera m_cam;
    };
} // namespace SM
#endif
