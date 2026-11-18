#include "VertexArray.h"
#include "VertexBufferLayout.h"

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

void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout) 
{
    Bind();

    vertexBuffer.Bind();

    const std::vector<Element>& elements = vertexBufferLayout.GetElements();

    unsigned int offset = 0;
    unsigned int index = 0;

    for(const auto& element : elements)
    {
        glVertexAttribPointer(
            index,
            element.count,
            element.type,
            element.normalized,
            vertexBufferLayout.GetStride(),
            (void*) (offset)
        );
        glEnableVertexAttribArray(index);
        index++;
        offset += element.size;
    }
    
}