#include "Common/Utils.hpp"
#include "Common/Common.hpp"

#include <fstream> // readfile shit
#include <stdio.h> // vprintf, printf
#include <stdarg.h> // varargs

namespace SM
{
    void LOG(const char* message, ...)
    {
        va_list args;
        va_start(args, message);
        vprintf(message, args);
        printf("\n");
        va_end(args);
    }

    std::vector<uint8_t> ReadFile(const char* filename)
    {
        std::ifstream instream(filename, std::ios::in | std::ios::binary);
        std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
        return data;
    }

    bool IsWithinScreenBorder(const Vec2& pos, const Vec2& size)
    {
        const float left = pos.x - size.x / 2.0f;
        const float right = pos.x + size.x / 2.0f;
        const float bottom = pos.y + size.y / 2.0f;
        const float top = pos.y - size.y / 2.0f;

        if (left <= 0.0f || right >= g_config.windowWidth)
            return false;
        if (top <= 0.0f || bottom >= g_config.windowHeight)
            return false;

        return true;
    }

} // namespace SM
