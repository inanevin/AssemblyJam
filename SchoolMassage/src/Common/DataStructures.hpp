
#pragma once

#ifndef DataStructures_HPP
#define DataStructures_HPP

#include <glm/glm.hpp>
#include <vector>

namespace SM
{
    typedef glm::ivec2 Vec2i;
    typedef glm::vec2  Vec2;
    typedef glm::vec3  Vec3;
    typedef glm::vec4  Vec4;
    typedef uint32_t   BackendHandle;
    typedef uint32_t   Index;
    using std::vector;

    struct Vertex
    {
        Vec2 pos;
        Vec2 uv;
        Vec4 col;
    };

} // namespace SM

#endif
