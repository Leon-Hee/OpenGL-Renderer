#pragma once
#include <GLFW/glfw3.h>
#include <vector>
//void glVertexAttribPointer
//(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)

struct Element
    {
        GLenum type;
        GLint count;
        GLboolean normalized;
        GLint size;
    };

class VertexBufferLayout
{
private:
    std::vector<Element> elements;
    unsigned int stride = 0;
    
public:
    VertexBufferLayout();
    ~VertexBufferLayout();
    void PushFloat(const int count);
    const std::vector<Element>& GetElements() const;
    unsigned int GetStride() const;
};


