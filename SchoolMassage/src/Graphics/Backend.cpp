/*
This file is a part of: Lina Engine
https://github.com/inanevin/LinaEngine

Author: Inan Evin
http://www.inanevin.com

Copyright (c) [2018-] [Inan Evin]

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

#include "glad/glad.h"
#include "Graphics/Backend.hpp"
#include "Common/Common.hpp"
#include "Common/Utils.hpp"

#include <iostream>
#include <stdio.h>

namespace SM::Backend
{
    BackendData g_backendData;

    bool Initialize()
    {
        g_backendData.m_defaultVtxShader = "#version 330 core\n"
                                           "layout (location = 0) in vec2 pos;\n"
                                           "layout (location = 1) in vec2 uv;\n"
                                           "layout (location = 2) in vec4 col;\n"
                                           "uniform mat4 proj; \n"
                                           "out vec4 fCol;\n"
                                           "out vec2 fUV;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   fCol = col;\n"
                                           "   fUV = uv;\n"
                                           "   gl_Position = proj * vec4(pos.x, pos.y, 0.0f, 1.0);\n"
                                           "}\0";

        g_backendData.m_defaultFragShader = "#version 330 core\n"
                                            "out vec4 fragColor;\n"
                                            "in vec4 fCol;\n"
                                            "void main()\n"
                                            "{\n"
                                            "   fragColor = fCol;\n"
                                            "}\0";

        g_backendData.m_texturedFragShader = "#version 330 core\n"
                                             "out vec4 fragColor;\n"
                                             "in vec2 fUV;\n"
                                             "in vec4 fCol;\n"
                                             "uniform sampler2D diffuse;\n"
                                             "uniform vec2 tiling;\n"
                                             "uniform vec2 offset;\n"
                                             "uniform int isAABuffer;\n"
                                             "void main()\n"
                                             "{\n"
                                             "   vec4 col = texture(diffuse, fUV * tiling + offset);\n"
                                             "   fragColor = vec4(col.rgb, isAABuffer == 1 ? fCol.a : col.a); \n"
                                             "}\0";

        g_backendData.m_simpleTextFragShader = "#version 330 core\n"
                                               "out vec4 fragColor;\n"
                                               "in vec2 fUV;\n"
                                               "in vec4 fCol;\n"
                                               "uniform sampler2D diffuse;\n"
                                               "void main()\n"
                                               "{\n"
                                               "float a = texture(diffuse, fUV).r; \n"
                                               "fragColor = vec4(fCol.rgb, a * fCol.a); \n"
                                               "}\0";

        g_backendData.m_sdfTextFragShader = "#version 330 core\n"
                                            "out vec4 fragColor;\n"
                                            "in vec2 fUV;\n"
                                            "in vec4 fCol;\n"
                                            "uniform sampler2D diffuse;\n"
                                            "uniform float softness; \n"
                                            "uniform float thickness; \n"
                                            "uniform int outlineEnabled; \n"
                                            "uniform int useOutlineOffset; \n"
                                            "uniform vec2 outlineOffset; \n"
                                            "uniform float outlineThickness; \n"
                                            "uniform vec4 outlineColor; \n"
                                            "uniform int flipAlpha; \n"
                                            "void main()\n"
                                            "{\n"
                                            "float distance = texture(diffuse, fUV).r;\n"
                                            "float alpha = smoothstep(thickness - softness, thickness + softness, distance);\n"
                                            "vec3 baseColor = fCol.rgb;\n"
                                            "if(outlineEnabled == 1){\n"
                                            " float border = smoothstep(thickness + outlineThickness - softness, thickness + outlineThickness + softness, distance);\n"
                                            " baseColor = mix(outlineColor, fCol, border).rgb;\n"
                                            "} \n"
                                            "fragColor = vec4(baseColor, flipAlpha == 1 ? 1.0f - alpha : alpha);\n"
                                            "}\0";

        g_backendData.m_roundedGradientFragShader = "#version 330 core\n"
                                                    "out vec4 fragColor;\n"
                                                    "in vec2 fUV;\n"
                                                    "in vec4 fCol;\n"
                                                    "uniform vec4 startColor;\n"
                                                    "uniform vec4 endColor;\n"
                                                    "uniform int  gradientType;\n"
                                                    "uniform float radialSize;\n"
                                                    "uniform int isAABuffer;\n"
                                                    "void main()\n"
                                                    "{\n"
                                                    "   if(gradientType == 0) {\n"
                                                    "     vec4 col = mix(startColor, endColor, fUV.x);\n"
                                                    "     fragColor = vec4(col.rgb, isAABuffer == 1 ? fCol.a : col.a); \n"
                                                    "}\n"
                                                    "   else if(gradientType == 1){\n"
                                                    "     vec4 col = mix(startColor, endColor, fUV.y);\n"
                                                    "     fragColor = vec4(col.rgb, isAABuffer == 1 ? fCol.a : col.a); \n"
                                                    "}\n"
                                                    "   else if(gradientType == 2) \n"
                                                    "   {\n"
                                                    "       vec2 uv = fUV - vec2(0.5, 0.5);\n"
                                                    "       float dist = length(uv * radialSize);\n"
                                                    "       vec4 col = mix(startColor, endColor, dist);\n"
                                                    "       fragColor = vec4(col.rgb, isAABuffer == 1 ? fCol.a : col.a); \n"
                                                    "    }\n"
                                                    "   else if(gradientType == 3) \n"
                                                    "   {\n"
                                                    "       float dist = length(fUV * radialSize);\n"
                                                    "       vec4 col = mix(startColor, endColor, dist);\n"
                                                    "       fragColor = vec4(col.rgb, isAABuffer == 1 ? fCol.a : col.a); \n"
                                                    "    }\n"
                                                    "}\n\0";

        try
        {
            CreateShader(g_backendData.m_defaultShaderData, g_backendData.m_defaultVtxShader, g_backendData.m_defaultFragShader);
            CreateShader(g_backendData.m_gradientShaderData, g_backendData.m_defaultVtxShader, g_backendData.m_roundedGradientFragShader);
            CreateShader(g_backendData.m_texturedShaderData, g_backendData.m_defaultVtxShader, g_backendData.m_texturedFragShader);
            CreateShader(g_backendData.m_simpleTextShaderData, g_backendData.m_defaultVtxShader, g_backendData.m_simpleTextFragShader);
            CreateShader(g_backendData.m_sdfTextShaderData, g_backendData.m_defaultVtxShader, g_backendData.m_sdfTextFragShader);
        }
        catch (const std::runtime_error& err)
        {
            LOG("Error: Backend shader creation failed! %s", err.what());
            return false;
        }

        glGenVertexArrays(1, &g_backendData.m_vao);
        glGenBuffers(1, &g_backendData.m_vbo);
        glGenBuffers(1, &g_backendData.m_ebo);

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(g_backendData.m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, g_backendData.m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_backendData.m_ebo);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glGenVertexArrays(1, &g_backendData.m_vao);
        glGenBuffers(1, &g_backendData.m_vbo);
        glGenBuffers(1, &g_backendData.m_ebo);

        glBindVertexArray(g_backendData.m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, g_backendData.m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_backendData.m_ebo);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);

        return true;
    }

    void StartFrame()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor((GLfloat)0.8f, (GLfloat)0.8f, (GLfloat)0.8f, (GLfloat)1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);
        glEnable(GL_SCISSOR_TEST);

        if (g_config.debugWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glViewport(0, 0, (GLsizei)g_config.windowWidth, (GLsizei)g_config.windowHeight);

        // Ortho projection matrix.
        int fb_width  = (int)(g_config.windowWidth * g_config.framebufferScale);
        int fb_height = (int)(g_config.windowHeight * g_config.framebufferScale);
        if (fb_width <= 0 || fb_height <= 0)
        {
            g_backendData.m_skipDraw = true;
            return;
        }

        g_backendData.m_skipDraw = false;

        float       L    = static_cast<float>(0);
        float       R    = static_cast<float>(0 + g_config.windowWidth);
        float       T    = static_cast<float>(0);
        float       B    = static_cast<float>(0 + g_config.windowHeight);
        const float zoom = 1.0f;

        L *= zoom;
        R *= zoom;
        T *= zoom;
        B *= zoom;

        // L += Config.debugOrthoOffset.x;
        // R += Config.debugOrthoOffset.x;
        // T += Config.debugOrthoOffset.y;
        // B += Config.debugOrthoOffset.y;

        g_backendData.m_proj[0][0] = 2.0f / (R - L);
        g_backendData.m_proj[0][1] = 0.0f;
        g_backendData.m_proj[0][2] = 0.0f;
        g_backendData.m_proj[0][3] = 0.0f;

        g_backendData.m_proj[1][0] = 0.0f;
        g_backendData.m_proj[1][1] = 2.0f / (T - B);
        g_backendData.m_proj[1][2] = 0.0f;
        g_backendData.m_proj[1][3] = 0.0f;

        g_backendData.m_proj[2][0] = 0.0f;
        g_backendData.m_proj[2][1] = 0.0f;
        g_backendData.m_proj[2][2] = -1.0f;
        g_backendData.m_proj[2][3] = 0.0f;

        g_backendData.m_proj[3][0] = (R + L) / (L - R);
        g_backendData.m_proj[3][1] = (T + B) / (B - T);
        g_backendData.m_proj[3][2] = 0.0f;
        g_backendData.m_proj[3][3] = 1.0f;

        glBindVertexArray(g_backendData.m_vao);
    }

    void Render()
    {
       
        ShaderData& data = g_backendData.m_defaultShaderData;
        glUseProgram(data.m_handle);
        glUniformMatrix4fv(data.m_uniformMap["proj"], 1, GL_FALSE, &g_backendData.m_proj[0][0]);

        vector<Vertex> v;
        vector<Index>  i;

        Vertex v1;
        Vertex v2;
        Vertex v3;
        v1.pos = Vec2(100, 100);
        v2.pos = Vec2(200, 100);
        v3.pos = Vec2(200, 500);
        v1.col = Vec4(1, 0, 0, 1);
        v2.col = Vec4(1,1,1,1);
        v3.col = Vec4(1,1,1,1);

        v.push_back(v1);
        v.push_back(v2);
        v.push_back(v3);

        i.push_back(0);
        i.push_back(2);
        i.push_back(1);

        glBindBuffer(GL_ARRAY_BUFFER, g_backendData.m_vbo);
        glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(Vertex), (const GLvoid*)v.data(), GL_STREAM_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_backendData.m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * sizeof(Index), (const GLvoid*)i.data(), GL_STREAM_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawElements(GL_TRIANGLES, (GLsizei)i.size(), sizeof(Index) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, 0);
    }

    void EndFrame()
    {
        // Restore state.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Terminate()
    {
    }

    void CreateShader(ShaderData& data, const char* vert, const char* frag)
    {
        unsigned int vertex, fragment;
        int          success;
        char         infoLog[512];

        // VTX
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vert, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            LOG("Error: Backend Shader vertex compilation failed!");
            throw std::runtime_error("");
        }

        // FRAG
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &frag, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);

            LOG("Backend Error -> Shader fragment compilation failed!");

            throw std::runtime_error("");
        }

        GLuint handle = glCreateProgram();
        glAttachShader(handle, vertex);
        glAttachShader(handle, fragment);
        glLinkProgram(handle);

        glGetProgramiv(handle, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(handle, 512, NULL, infoLog);
            LOG("Backend Error->Could not link shader program!");
            throw std::runtime_error("");
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        data.m_handle = (BackendHandle)handle;
        AddShaderUniforms(data);
    }

    void AddShaderUniforms(ShaderData& data)
    {
        // Load uniforms.
        GLint numUniforms = 0;
        glGetProgramiv(data.m_handle, GL_ACTIVE_UNIFORMS, &numUniforms);

        // Iterate through uniforms.
        GLchar chars[256];
        for (GLint uniform = 0; uniform < numUniforms; ++uniform)
        {
            GLint   arraySize    = 0;
            GLenum  type         = 0;
            GLsizei actualLength = 0;

            // Get sampler uniform data & store it on our sampler map.
            glGetActiveUniform(data.m_handle, uniform, (GLsizei)256, &actualLength, &arraySize, &type, &chars[0]);

            GLint loc                    = glGetUniformLocation(data.m_handle, (char*)&chars[0]);
            data.m_uniformMap[&chars[0]] = loc;
        }
    }

    BackendHandle CreateFontTexture(int width, int height)
    {
        GLuint tex;
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return tex;
    }

    void BufferFontTextureAtlas(int width, int height, int offsetX, int offsetY, unsigned char* data)
    {
        glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, width, height, GL_RED, GL_UNSIGNED_BYTE, data);
    }

    void BindFontTexture(BackendHandle texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }

} // namespace SM::Backend