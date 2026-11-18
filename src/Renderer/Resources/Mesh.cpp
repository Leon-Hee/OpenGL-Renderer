#include "Mesh.h"

Mesh::Mesh(
    const void* vertices,
    unsigned int size,
    unsigned int vertexCount,
    Material& material,
    const VertexBufferLayout& vertexBufferLayout
)
    : m_Material(material),
      m_VertexArray(),
      m_VertexBuffer(vertices, size),
      m_VertexCount(vertexCount),
      m_vertexBufferLayout(vertexBufferLayout)
{
    m_VertexArray.AddVertexBuffer(m_VertexBuffer, m_vertexBufferLayout);
}

Mesh::~Mesh()
{
}

void Mesh::Draw()
{
    m_Material.Bind();
    m_VertexArray.Bind();

    glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
}