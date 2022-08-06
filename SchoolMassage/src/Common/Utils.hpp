#pragma once

#include "Common/DataStructures.hpp"
#include <glm/gtx/vector_angle.hpp>
#ifndef Utils_HPP
#define Utils_HPP

namespace SM
{
    class Object;

    void                 LOG(const char* message, ...);
    std::vector<uint8_t> ReadFile(const char* filename);
    int                  GetRandom(int low, int high);

    template <typename T>
    static T Remap(const T& val, const T& fromLow, const T& fromHigh, const T& toLow, const T& toHigh)
    {
        return toLow + (val - fromLow) * (toHigh - toLow) / (fromHigh - fromLow);
    }

    template <typename T, typename U>
    static T Lerp(const T& val1, const T& val2, const U& amt)
    {
        return (T)(val1 * ((U)(1) - amt) + val2 * amt);
    }

    static int32_t Rand()
    {
        return ::rand();
    }
    static void SeedRand(int32_t seed)
    {
        srand((uint32_t)seed);
    }
    static float RandF()
    {
        return ::rand() / (float)RAND_MAX;
    }
    static float RandF(float Min, float Max)
    {
        return Lerp(Min, Max, RandF());
    }

    // Returns in deg.
    static float AngleBetween(const Vec2& v1, const Vec2& v2)
    {
        const float dot = v1.x * v2.x + v1.y * v2.y;
        const float det = v1.x * v2.y - v1.y * v2.x;
        return atan2(det, dot) * 57.2958f;

      //  return glm::angle(v1, v2) * 57.2958f;
    }

    bool IsWithinScreenBorder(const Vec2& pos, const Vec2& size);

    bool TestAABB(Object* obj1, Object* obj2);

} // namespace SM

#endif
