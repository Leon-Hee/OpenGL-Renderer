#pragma once
#include "Material.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


class Mesh // 把“几何数据 + 几何布局 + 材质”组织成一个可以被绘制的 Renderable Object。
{
private:
    Material m_Material; // 材质
    VertexArray m_VertexArray; 
    VertexBuffer m_VertexBuffer;
    VertexBufferLayout m_vertexBufferLayout;
    IndexBuffer m_IndexBuffer;
public:
    Mesh(const void* vertices, unsigned int size, Material& material, const VertexBufferLayout& vertexBufferLayout, const unsigned int* indices, unsigned int indexCount); // 顶点数据，数据总大小，材质，顶点解释器，顶点索引数据，索引数量
    ~Mesh();
    void Draw();
    Material& GetMaterial();
};


