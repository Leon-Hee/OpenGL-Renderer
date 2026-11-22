#include "Mesh.h"

Mesh::Mesh(
    const void* vertices,
    unsigned int size,
    Material& material,
    const VertexBufferLayout& vertexBufferLayout,
    const unsigned int* indices,
    unsigned int indexCount
)
    : m_Material(material),
      m_VertexArray(),
      m_VertexBuffer(vertices, size),
      m_vertexBufferLayout(vertexBufferLayout),
      m_IndexBuffer(indices, indexCount)
{
    m_VertexArray.AddVertexBuffer(m_VertexBuffer, m_vertexBufferLayout);
}

Mesh::~Mesh()
{
}

void Mesh::Draw()
{
    m_VertexArray.Bind();
    m_IndexBuffer.Bind();

    glDrawElements(GL_TRIANGLES, m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}

Material& Mesh::GetMaterial()
{
    return m_Material;
}