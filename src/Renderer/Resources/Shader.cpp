#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    // 读取文件
    std::ifstream vertexFile(vertexPath);
    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    std::string vertexSource = vertexStream.str();
    const char* vertexSourceCode = vertexSource.c_str();

    std::ifstream fragmentFile(fragmentPath);
    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    std::string fragmentSource = fragmentStream.str();
    const char* fragmentSourceCode = fragmentSource.c_str();

    // 建立着色器并附加编译检测
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSourceCode, nullptr);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Vertex Shader Compilation Error:\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSourceCode, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Fragment Shader Compilation Error:\n" << infoLog << std::endl;
    }

    // 建立程序
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertexShader);
    glAttachShader(m_RendererID, fragmentShader);
    glLinkProgram(m_RendererID);

    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_RendererID, 512, nullptr, infoLog);
        std::cout << "Shader Program Linking Error:\n" << infoLog << std::endl;

}


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() 
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}


void Shader::SetFloat(const std::string& name, float value){
    const char* _name = name.c_str();
    GLint FloatLocation = glGetUniformLocation(m_RendererID, _name);
    glUniform1f(FloatLocation, value);

    
}

void Shader::SetBool(const std::string& name, bool value) {
    const char* _name = name.c_str();
    GLint BoolLocation = glGetUniformLocation(m_RendererID, _name);
    glUniform1i(BoolLocation, value);
}

void Shader::SetVec3(const std::string& name, glm::vec3 value) {
    const char* _name = name.c_str();
    GLint Vec3Location = glGetUniformLocation(m_RendererID, _name);
    glUniform3fv(Vec3Location, 1, glm::value_ptr(value));
}

void Shader::SetInt(const std::string& name, int value)
{
    const char* _name = name.c_str();
    GLint IntLocation = glGetUniformLocation(m_RendererID, _name);
    glUniform1i(IntLocation, value);
}

void Shader::SetVec2(const std::string& name, glm::vec2 value)
{
    const char* _name = name.c_str();
    GLint Vec2Location = glGetUniformLocation(m_RendererID, _name);
    glUniform2fv(Vec2Location, 1, glm::value_ptr(value));
}

void Shader::SetVec4(const std::string& name, glm::vec4 value)
{
    const char* _name = name.c_str();
    GLint Vec4Location = glGetUniformLocation(m_RendererID, _name);
    glUniform4fv(Vec4Location, 1, glm::value_ptr(value));
}

void Shader::SetMat3(const std::string& name, glm::mat3 value)
{
    const char* _name = name.c_str();
    GLint Mat3Location = glGetUniformLocation(m_RendererID, _name);
    glUniformMatrix3fv(Mat3Location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string& name, glm::mat4 value)
{
    const char* _name = name.c_str();
    GLint Mat4Location = glGetUniformLocation(m_RendererID, _name);
    glUniformMatrix4fv(Mat4Location, 1, GL_FALSE, glm::value_ptr(value));
}