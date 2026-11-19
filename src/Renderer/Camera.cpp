#include "Camera.h"

Camera::Camera(float width, float height, float FOV, float Znear, float Zfar)
    : m_Width(width),
      m_FOV(FOV),
      m_Height(height),
      m_Znear(Znear),
      m_Zfar(Zfar)

{
    m_View = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_Projection = glm::perspective(glm::radians(m_FOV), m_Width / m_Height, m_Znear, m_Zfar);
}

Camera::~Camera()
{
}

const glm::mat4& Camera::GetViewMatrix() const
{
    return m_View;
}
const glm::mat4& Camera::GetProjectionMatrix() const
{
    return m_Projection;
}