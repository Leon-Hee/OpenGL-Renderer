#pragma once
#include "Shader.h"
#include "Texture.h"
#include "../RenderType.h"
#include <string>


class Material // 物体该用什么shader和纹理
{
private:
    Shader* m_Shader; // Material 不应该有shader和texture的生命周期
    Texture* m_DiffuseTexture;
    Texture* m_NormalTexture;
    RenderType m_RenderType;
public:
    Material(Shader& shader, Texture& diffuseTexture, Texture& normalTexture);
    void Bind() const;
    void SetFloat(const std::string& name, float value);
    void SetInt(const std::string& name, int value);
    void SetVec2(const std::string& name, glm::vec2 value);
    void SetVec3(const std::string& name, glm::vec3 value);
    void SetVec4(const std::string& name, glm::vec4 value);
    void SetMat3(const std::string& name, glm::mat3 value);
    void SetMat4(const std::string& name, glm::mat4 value);
    void SetDiffuseTexture2D(int value);
    void SetNormalTexture2D(int value);
    void SetRenderType(RenderType renderType = RenderType::Opaque);
    RenderType GetRenderType() const;
    void SetDiffuseTexture(Texture& diffuseTexture);
    void SetNormalTexture(Texture& normalTexture);

};


