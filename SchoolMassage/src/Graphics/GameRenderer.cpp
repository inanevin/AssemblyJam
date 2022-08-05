#include "GameRenderer.hpp"
#include "Common/Common.hpp"
#include "Common/Utils.hpp"
#include "linavg/LinaVG.hpp"

namespace SM
{
    void GameRenderer::Initialize()
    {
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
    }

    void GameRenderer::Render()
    {
        LinaVG::StartFrame();

        LinaVG::StyleOptions style;
        style.color = LinaVG::Vec4(1, 0, 0, 1);
        LinaVG::DrawRect(LinaVG::Vec2(0, 0), LinaVG::Vec2(100, 100), style);

        LinaVG::Render();
        LinaVG::EndFrame();
    }

    void GameRenderer::Terminate()
    {
        LinaVG::Terminate();
    }
} // namespace SM