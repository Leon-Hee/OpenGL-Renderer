#pragma once
#include <GLFW/glfw3.h>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size); // 传入任意类型数据，以及其长度
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_RendererID;
};