
#pragma once

#ifndef Common_HPP
#define Common_HPP

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <stdio.h>
#include <iostream>

#define LOG(...) SM::LogMessage(__VA_ARGS__);

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
    };

    template <typename... Args>
    static void LogMessage(const Args&... args)
    {
      // auto a = fmt::format(args...).c_str();
        //std::cout <<  << std::endl;
    }

    extern Config g_config;

} // namespace SM

#endif
