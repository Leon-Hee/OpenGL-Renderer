#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>

class VertexArray
{
private:
    GLuint m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void UnBind() const;
};

