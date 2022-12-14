
#pragma once

#ifndef Renderer_HPP
#define Renderer_HPP

#include "Common/DataStructures.hpp"

namespace SM
{
    class Scene;

    class GameRenderer
    {
    public:
        GameRenderer()  = default;
        ~GameRenderer() = default;

        void Initialize();
        void Clear();
        void Terminate();

        /// <summary>
        /// w-h-nrChannels optional, will be set if non 0
        /// </summary>
        /// <param name="file"></param>
        /// <param name="w"></param>
        /// <param name="h"></param>
        /// <param name="nrChannels"></param>
        /// <returns></returns>
        GraphicsHandle CreateTexture(const char* file, int* w = 0, int* h = 0, int* nrChn = 0);

        static GameRenderer* _ptr;

    private:
    };
} // namespace SM
#endif
