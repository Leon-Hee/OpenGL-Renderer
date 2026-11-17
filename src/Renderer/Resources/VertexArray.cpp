#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);

}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer) 
{
    Bind();

    vertexBuffer.Bind();

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(

        0,

        2,

        GL_FLOAT,

        GL_FALSE,

        4 * sizeof(float),

        (void*)0

    );

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(

        1,

        2,

        GL_FLOAT,

        GL_FALSE,

        4 * sizeof(float),

        (void*)(2 * sizeof(float))

    );
}