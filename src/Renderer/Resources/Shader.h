#include <GLFW/glfw3.h>
#include <string>

class Shader
{
private:
    GLuint m_RendererID;

public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind();
    void Unbind();
};


