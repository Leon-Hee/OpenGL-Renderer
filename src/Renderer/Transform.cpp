#include "Transform.h"

Transform::Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale) 
    : m_Position(Position),
      m_Rotation(Rotation),
      m_Scale(Scale)
{

}



const glm::vec3& Transform::GetPosition() const
{
    return m_Position;
}
const glm::vec3& Transform::GetRotation() const
{
    return m_Rotation;
}
const glm::vec3& Transform::GetScale() const
{
    return m_Scale;
}
glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 MVP = glm::mat4(1.0f);
    MVP = glm::translate(MVP, m_Position);
    MVP = glm::rotate(MVP, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    MVP = glm::rotate(MVP, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    MVP = glm::rotate(MVP, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    MVP = glm::scale(MVP, m_Scale);
    return MVP;
}