/*
This file is a part of: LinaVG
https://github.com/inanevin/LinaVG

Author: Inan Evin
http://www.inanevin.com

Copyright (c) [2022-] [Inan Evin]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
Class: GLBackend



Timestamp: 3/24/2022 11:33:52 PM
*/

#pragma once
#include "Common/DataStructures.hpp"
#include <string>
#include <unordered_map>

#ifndef Backend_HPP
#define Backend_HPP

namespace SM::Backend
{

    class ShaderData
    {
    public:
        BackendHandle                                  m_handle = 0;
        std::unordered_map<std::string, BackendHandle> m_uniformMap;
    };

    struct BackendData
    {
        BackendHandle m_vbo = 0;
        BackendHandle m_vao = 0;
        BackendHandle m_ebo = 0;
        ShaderData    m_defaultShaderData;
        ShaderData    m_gradientShaderData;
        ShaderData    m_texturedShaderData;
        ShaderData    m_sdfTextShaderData;
        ShaderData    m_simpleTextShaderData;
        float         m_proj[4][4]                = {0};
        const char*   m_defaultVtxShader          = nullptr;
        const char*   m_defaultFragShader         = nullptr;
        const char*   m_roundedGradientFragShader = nullptr;
        const char*   m_texturedFragShader        = nullptr;
        const char*   m_sdfTextFragShader         = nullptr;
        const char*   m_simpleTextFragShader      = nullptr;
        bool          m_skipDraw                  = false;
    };

    extern BackendData g_backendData;

    bool Initialize();
    void Terminate();
    void StartFrame();
    void Render();

    void          EndFrame();
    void          BufferFontTextureAtlas(int width, int height, int offsetX, int offsetY, unsigned char* data);
    void          BindFontTexture(BackendHandle texture);
    BackendHandle CreateFontTexture(int width, int height);

    // Private functionality.
    void AddShaderUniforms(ShaderData& data);
    void CreateShader(ShaderData& data, const char* vert, const char* frag);
} // namespace SM

#endif
