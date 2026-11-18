#include "VertexBufferLayout.h"


VertexBufferLayout::VertexBufferLayout(/* args */)
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}

void VertexBufferLayout::PushFloat(const int count)
{
    Element element;
    element.count = count;
    element.normalized = GL_FALSE;
    element.size = count * sizeof(float);
    element.type = GL_FLOAT;
    elements.push_back(element);
    stride += element.size;
}
    
const std::vector<Element>& VertexBufferLayout::GetElements() const
{
    return elements;
}
    

unsigned int VertexBufferLayout::GetStride() const
{
    return stride;
}