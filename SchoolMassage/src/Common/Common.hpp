
#pragma once

#ifndef Common_HPP
#define Common_HPP

#include <stdio.h>
#include <iostream>

namespace SM
{
    struct Config
    {
        bool        debugWireframe   = false;
        bool        fullscreenWindow = false;
        int         windowWidth      = 800;
        int         windowHeight     = 600;
        float       framebufferScale = 1.0f;
        const char* windowTitle      = "School Massage";
        bool        resizableWindow  = true;
        bool        decoratedWindow  = true;
        int         msaaSamples      = 4;
    };

    extern Config g_config;

} // namespace SM

#endif
