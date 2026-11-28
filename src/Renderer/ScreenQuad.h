#pragma once
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>


class ScreenQuad
{
private:
    unsigned int m_VAO;
    unsigned int m_VBO;
public:
    ScreenQuad(/* args */);
    ~ScreenQuad();

    void Draw();
};


