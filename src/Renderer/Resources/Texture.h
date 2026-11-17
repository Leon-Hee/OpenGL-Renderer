#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Texture
{
private:
    unsigned int m_RendererID = 0;
    
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind_2D(unsigned int slot = 0) const;
    void Unbind_2D() const;
};


