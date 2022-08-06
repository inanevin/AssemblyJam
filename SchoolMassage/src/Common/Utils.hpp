#pragma once

#include "Common/DataStructures.hpp"

#ifndef Utils_HPP
#define Utils_HPP

namespace SM
{
    void                 LOG(const char* message, ...);
    std::vector<uint8_t> ReadFile(const char* filename);

    template <typename T> static T Remap(const T& val, const T& fromLow, const T& fromHigh, const T& toLow, const T& toHigh)
    {
        return toLow + (val - fromLow) * (toHigh - toLow) / (fromHigh - fromLow);
    }

} // namespace SM

#endif
