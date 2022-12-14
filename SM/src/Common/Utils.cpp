#include "Common/Utils.hpp"
#include "Common/Common.hpp"
#include "World/Object.hpp"

#include <fstream>  // readfile shit
#include <stdio.h>  // vprintf, printf
#include <stdarg.h> // varargs
#include <stdlib.h> // varargs

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
        std::ifstream        instream(filename, std::ios::in | std::ios::binary);
        std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
        return data;
    }

    bool IsWithinScreenBorder(const Vec2& pos, const Vec2& size)
    {
        const float left   = pos.x - size.x / 2.0f;
        const float right  = pos.x + size.x / 2.0f;
        const float bottom = pos.y + size.y / 2.0f;
        const float top    = pos.y - size.y / 2.0f;

        if (left <= 0.0f || right >= g_config.windowWidth)
            return false;
        if (top <= 0.0f || bottom >= g_config.windowHeight)
            return false;

        return true;
    }

    bool TestAABB(Object* obj1, Object* obj2)
    {
        const Vec2 hs1 = obj1->m_size / 2.0f;
        const Vec2 hs2 = obj2->m_size / 2.0f;
        const Vec2 p1  = obj1->m_pos;
        const Vec2 p2  = obj2->m_pos;

        if (std::fabs(p1.x - p2.x) > (hs1.x + hs2.x))
            return false;
        if (std::fabs(p1.y - p2.y) > (hs1.y + hs2.y))
            return false;

        // We have an overlap
        return true;
    }

    int GetRandom(int low, int high)
    {
        if (high <= 0) {
            LOG("OMG GETRANDOM() ERROOORR low %d, high %d", low, high);
            // todo assert
            return low;
        }
        return low + (rand() % (high + 1));
    }

    bool GetRandomBool(float chance)
    {
        return GetRandom(0, 1000) > int(1000.0f * chance); // lol wat
    }
} // namespace SM
