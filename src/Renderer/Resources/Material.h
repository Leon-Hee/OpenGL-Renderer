#pragma once
#include "Shader.h"
#include "Texture.h"
#include <string>


class Material // 物体该用什么shader和纹理
{
private:
    Shader* m_Shader; // Material 不应该有shader和texture的生命周期
    Texture* m_Texture; // 只实现了引用
public:
    Material(Shader& shader, Texture& texture);
    void Bind() const;
    void SetFloat(const std::string& name, float value);
    void SetInt(const std::string& name, int value);
    void SetVec2(const std::string& name, glm::vec2 value);
    void SetVec3(const std::string& name, glm::vec3 value);
    void SetVec4(const std::string& name, glm::vec4 value);
    void SetMat3(const std::string& name, glm::mat3 value);
    void SetMat4(const std::string& name, glm::mat4 value);
    void SetTexture(int value);
    
};


