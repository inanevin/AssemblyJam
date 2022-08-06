#include "GameRenderer.hpp"
#include "Common/Common.hpp"
#include "Common/Utils.hpp"
#include "linavg/LinaVG.hpp"
#include <glad/glad.h>

#include "World/Scene.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace SM
{
    GraphicsHandle testTexture;
    GameRenderer*  GameRenderer::_ptr = 0;

    void GameRenderer::Initialize()
    {
        _ptr = this;

        // Lina VG config shaiba.
        LinaVG::Config.displayPosX   = 0;
        LinaVG::Config.displayPosY   = 0;
        LinaVG::Config.displayWidth  = g_config.windowWidth;
        LinaVG::Config.displayHeight = g_config.windowHeight;
        LinaVG::Config.clipPosX = LinaVG::Config.clipPosY = 0;
        LinaVG::Config.clipSizeX                          = 0;
        LinaVG::Config.clipSizeY                          = 0;
        LinaVG::Config.flipTextureUVs                     = false;
        LinaVG::Config.framebufferScale.x = LinaVG::Config.framebufferScale.y = g_config.framebufferScale;
        LinaVG::Config.aaMultiplier                                           = 1.5f;

        LinaVG::Config.errorCallback = [](const std::string& err) {
            LOG(err.c_str());
        };

        LinaVG::Config.logCallback = [](const std::string& log) {
            LOG(log.c_str());
        };

        LinaVG::Initialize();

        // Loading textures
        testTexture = CreateTexture("Resources/test.png");
    }
    
    void GameRenderer::Clear()
    {
        // Clear
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor((GLfloat)0.8f, (GLfloat)0.8f, (GLfloat)0.8f, (GLfloat)1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GameRenderer::Terminate()
    {
        LinaVG::Terminate();
    }

    GraphicsHandle GameRenderer::CreateTexture(const char* file, int* w, int* h, int* nrChn)
    {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int            width, height, nrChannels;
        unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 4);

        if (w != 0)
            *w = width;

        if (h != 0)
            *h = height;

        if (nrChn != 0)
            *nrChn = nrChannels;

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            LOG("Failed to load texture!");
        }
        stbi_image_free(data);
        return texture;
    }
} // namespace SM