#pragma once

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
class ShadowMap
{
private:
    unsigned int m_Framebuffer;
    unsigned int m_DepthTexture;

    int m_Width;
    int m_Height;
public:
    ShadowMap(int width, int height);
    ~ShadowMap();

    void Bind();
    void Unbind();

    unsigned int GetDepthTexture() const;
    int GetWidth() const;
    int GetHeight() const;
};


