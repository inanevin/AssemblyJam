#include "Common/Utils.hpp"
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
} // namespace SM
