#pragma once

#include "Common/DataStructures.hpp"

#ifndef Utils_HPP
#define Utils_HPP

namespace SM
{
    void                 LOG(const char* message, ...);
    std::vector<uint8_t> ReadFile(const char* filename);

} // namespace SM

#endif
