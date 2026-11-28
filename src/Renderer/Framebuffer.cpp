#include "Framebuffer.h"
#include <iostream>

Framebuffer::Framebuffer(int width, int height)
    : m_Width(width),
      m_Height(height)
{
    glGenFramebuffers(1, &m_RendererID);
    Bind();
    glGenTextures(1, &m_ColorAttachment);
    glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };
    glTexParameterfv(
        GL_TEXTURE_2D,
        GL_TEXTURE_BORDER_COLOR,
        borderColor
    );
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glGenTextures(1, &m_DepthAttachment);
    glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameterfv(
        GL_TEXTURE_2D,
        GL_TEXTURE_BORDER_COLOR,
        borderColor
    );
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer is not complete! Status: "
                << std::hex << status
                << std::dec << std::endl;
    }
    
}

Framebuffer::~Framebuffer()
{
}

void Framebuffer::Bind() 
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void Framebuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Framebuffer::GetColorAttachment() const
{
    return m_ColorAttachment;
}

void Framebuffer::Resize(int width, int height)
{
    if (width <= 0 || height <= 0)

        return;

    m_Width = width;

    m_Height = height;

    glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

    glTexImage2D(

        GL_TEXTURE_2D,

        0,

        GL_RGBA8,

        m_Width,

        m_Height,

        0,

        GL_RGBA,

        GL_UNSIGNED_BYTE,

        nullptr

    );

    glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);

    glTexImage2D(

        GL_TEXTURE_2D,

        0,

        GL_DEPTH_COMPONENT24,

        m_Width,

        m_Height,

        0,

        GL_DEPTH_COMPONENT,

        GL_FLOAT,

        nullptr

    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

int Framebuffer::GetWidth() const
{
    return m_Width;
}

int Framebuffer::GetHeight() const
{
    return m_Height;
}