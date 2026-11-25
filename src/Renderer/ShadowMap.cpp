#include "ShadowMap.h"
#include <iostream>

ShadowMap::ShadowMap(int width, int height) : m_Width(width), m_Height(height)
{
    glGenFramebuffers(1, &m_Framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glGenTextures(1, &m_DepthTexture);
    glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr); // 创建一个 width × height 的深度纹理，用来保存深度数据

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture, 0);
    glDrawBuffer(GL_NONE); // 这一遍渲染只需要深度，不需要 Color Buffer
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ShadowMap Framebuffer is not complete!" << std::endl;
    }
    else
    {
        std::cout << "ShadowMap Framebuffer is complete!" << std::endl;
    }
}

ShadowMap::~ShadowMap()
{
    glDeleteFramebuffers(1, &m_Framebuffer);
    glDeleteTextures(1, &m_DepthTexture);
}

void ShadowMap::Bind() 
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
}

void ShadowMap::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int ShadowMap::GetDepthTexture() const
{
    return m_DepthTexture;
}

int ShadowMap::GetHeight() const
{
    return m_Height;
}

int ShadowMap::GetWidth() const
{
    return m_Width;
}