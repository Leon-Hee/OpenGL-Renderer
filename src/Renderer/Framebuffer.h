#pragma once
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl.h>



class Framebuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_ColorAttachment;
    unsigned int m_DepthAttachment;

    int m_Width;
    int m_Height;
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    void Bind();
    void Unbind();

    void Resize(int width, int height);

    unsigned int GetColorAttachment() const;

    int GetWidth() const;
    int GetHeight() const;
};

