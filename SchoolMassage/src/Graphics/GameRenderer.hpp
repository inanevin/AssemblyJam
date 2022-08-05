
#pragma once

#ifndef Renderer_HPP
#define Renderer_HPP

namespace SM
{
    class GameRenderer
    {
    public:
        GameRenderer() = default;
        ~GameRenderer() = default;

        void Initialize();
        void Render();
        void Terminate();

    private:
    };
} // namespace SM
#endif
