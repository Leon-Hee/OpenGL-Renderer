#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
    GLuint m_RendererID;

public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind();
    void Unbind();

    void SetFloat(const std::string& name, float value);
    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetVec2(const std::string& name, glm::vec2 value);
    void SetVec3(const std::string& name, glm::vec3 value);
    void SetVec4(const std::string& name, glm::vec4 value);
    void SetMat3(const std::string& name, glm::mat3 value);
    void SetMat4(const std::string& name, glm::mat4 value);

};


