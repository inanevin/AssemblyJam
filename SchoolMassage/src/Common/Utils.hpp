#pragma once

#include "Common/DataStructures.hpp"

#ifndef Utils_HPP
#define Utils_HPP

namespace SM
{
    void                 LOG(const char* message, ...);
    std::vector<uint8_t> ReadFile(const char* filename);

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

    bool IsWithinScreenBorder(const Vec2& pos, const Vec2& size);

} // namespace SM

#endif
