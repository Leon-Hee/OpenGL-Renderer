#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
private:
    glm::vec3 m_Rotation;
    glm::vec3 m_Position;
    glm::vec3 m_Scale;

public:
    Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale);
    const glm::vec3& GetPosition() const;
    const glm::vec3& GetRotation() const;
    const glm::vec3& GetScale() const;
    glm::mat4 GetMatrix() const;
};


