#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../third_party/stb/stb_image.h"
#include <iostream>

Texture::Texture(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    //width     → 图片宽度
    //height    → 图片高度
    //channels  → 每个像素有几个颜色通道
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if(!data) {
        std::cout << "Failed to load the texture!" << std::endl;
        return;
    }

    glGenTextures(1, &m_RendererID);
    Bind_2D();
    /*
    target       → GL_TEXTURE_2D
    level        → 0
    internalFormat → GPU 内部存储格式
    width        → width
    height       → height
    border       → 0
    format       → CPU 数据格式
    type         → GL_UNSIGNED_BYTE
    data         → data
    */
    GLenum format;
    
    if(channels == 3) {
        format = GL_RGB;
    } else if (channels == 4) {
        format = GL_RGBA;
    } else {
        std::cout << "Unsupported texture format" << std::endl;
        stbi_image_free(data);
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}
void Texture::Bind_2D(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0+ slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}
    
void Texture::Unbind_2D() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}