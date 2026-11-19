#pragma once
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>


class VertexArray
{
private:
    GLuint m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void UnBind() const;

    void AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout);

};

