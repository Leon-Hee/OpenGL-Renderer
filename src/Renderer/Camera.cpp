#include "Camera.h"

Camera::Camera(
    float width, 
    float height, 
    float FOV, 
    float Znear, 
    float Zfar,
    glm::vec3 position,
    glm::vec3 front,
    glm::vec3 up
    )
    : m_Width(width),
      m_FOV(FOV),
      m_Height(height),
      m_Znear(Znear),
      m_Zfar(Zfar),
      m_Position(position),
      m_Front(front),
      m_Up(up),
      m_Yaw(-90.0f),
      m_Pitch(0.0f),
        m_Sensitivity(0.1f),
        m_LastMouseX(0.0f),
        m_LastMouseY(0.0f),
        m_FirstMouse(true)

{
    m_Right = glm::normalize(glm::cross(m_Front, m_Up));
    UpdateMatrix();
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

const glm::vec3& Camera::GetPosition() const
{
    return m_Position;
}

void Camera::MoveForward(float distance)
{
    m_Position += m_Front * distance;
    UpdateMatrix();
}

void Camera::MoveRight(float distance)
{
    m_Position += m_Right * distance;
    UpdateMatrix();
}

void Camera::UpdateMatrix()
{
    m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::ProcessMouseMovement(float xPos, float yPos)
{
    if (m_FirstMouse)
    {
        m_LastMouseX = xPos;
        m_LastMouseY = yPos;
        m_FirstMouse = false;
        return;
    }

    float xOffset = xPos - m_LastMouseX;
    float yOffset = m_LastMouseY - yPos;

    m_LastMouseX = xPos;
    m_LastMouseY = yPos;

    xOffset *= m_Sensitivity;
    yOffset *= m_Sensitivity;

    m_Yaw += xOffset;
    m_Pitch += yOffset;

    m_Pitch = glm::clamp(
        m_Pitch,
        -89.0f,
        89.0f
    );

    glm::vec3 direction;

    direction.x =
        glm::cos(glm::radians(m_Yaw)) *
        glm::cos(glm::radians(m_Pitch));

    direction.y =
        glm::sin(glm::radians(m_Pitch));

    direction.z =
        glm::sin(glm::radians(m_Yaw)) *
        glm::cos(glm::radians(m_Pitch));

    m_Front = glm::normalize(direction);

    m_Right =
        glm::normalize(
            glm::cross(m_Front, m_Up)
        );

    UpdateMatrix();
}
