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
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    float m_FOV;
    float m_Znear;
    float m_Zfar;
    float m_Width;
    float m_Height;

    float m_Yaw;
    float m_Pitch;
    float m_Sensitivity;

    float m_LastMouseX;
    float m_LastMouseY;

    float m_FirstMouse;
public:
    Camera(
        float width, 
        float height, 
        float FOV, 
        float Znear, 
        float Zfar, 
        glm::vec3 position, 
        glm::vec3 front, 
        glm::vec3 up
    );
    ~Camera();
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;
    const glm::vec3& GetPosition() const;
    const glm::vec3& GetFront() const;
    const glm::vec3& GetUp() const;

    void MoveForward(float distance);
    void MoveRight(float distance);
    void UpdateMatrix();
    void ProcessMouseMovement(float xPos, float yPos);
    void SetPosition(const glm::vec3& position);
    void SetFront(const glm::vec3& front);
    void SetViewportSize(float width, float height);
    
};


