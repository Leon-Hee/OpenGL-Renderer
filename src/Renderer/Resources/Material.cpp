#include "Material.h"

Material::Material(Shader& shader, Texture& texture)
{
    m_Shader = &shader;
    m_Texture = &texture;

}

void Material::Bind() const // 把这个 Material 所需要的渲染资源全部绑定到 OpenGL 当前状态。
{
    m_Shader -> Bind();

    m_Texture -> Bind_2D(0);
}

void Material::SetFloat(const std::string& name, float value)
{
    m_Shader->SetFloat(name, value);
}

void Material::SetInt(const std::string& name, int value)
{
    m_Shader->SetInt(name, value);
}

void Material::SetVec2(const std::string& name, glm::vec2 value)
{
    m_Shader->SetVec2(name, value);
}

void Material::SetVec3(const std::string& name, glm::vec3 value)
{
    m_Shader->SetVec3(name, value);
}

void Material::SetVec4(const std::string& name, glm::vec4 value)
{
    m_Shader->SetVec4(name, value);
}

void Material::SetMat3(const std::string& name, glm::mat3 value)
{
    m_Shader->SetMat3(name, value);
}

void Material::SetMat4(const std::string& name, glm::mat4 value)
{
    m_Shader->SetMat4(name, value);
}

void Material::SetTexture2D(int value)
{
    m_Texture->Bind_2D(value);
}