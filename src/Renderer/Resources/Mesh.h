#pragma once
#include "Material.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


class Mesh // 把“几何数据 + 几何布局 + 材质”组织成一个可以被绘制的 Renderable Object。
{
private:
    Material m_Material;
    VertexArray m_VertexArray;
    VertexBuffer m_VertexBuffer;
    unsigned int m_VertexCount;
    VertexBufferLayout m_vertexBufferLayout;
public:
    Mesh(const void* vertices, unsigned int size, unsigned int vertexCount, Material& material, const VertexBufferLayout& vertexBufferLayout);
    ~Mesh();
    void Draw();
};


