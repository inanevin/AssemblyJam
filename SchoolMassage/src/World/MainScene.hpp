
#pragma once
#include "Scene.hpp"
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
    };
} // namespace SM
#endif
