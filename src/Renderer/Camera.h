#pragma once 
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
private:
    glm::mat4 m_View;
    glm::mat4 m_Projection;
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    float m_FOV;
    float m_Znear;
    float m_Zfar;
    float m_Width;
    float m_Height;
public:
    Camera(float width, float height, float FOV, float Znear, float Zfar);
    ~Camera();
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;
    const glm::vec3& GetPosition() const;
};


