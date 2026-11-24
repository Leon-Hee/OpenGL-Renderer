#include "Light.h"

Light::Light(
      LightType type, 
      const glm::vec3& position, 
      const glm::vec3& direction, 
      const glm::vec3& color, 
      float intensity,
      float constant,
      float linear,
      float quadratic,
      float innerCutOff,
      float outerCutOff
    )
    : m_Type(type),
      m_Position(position),
      m_Direction(direction),
      m_Color(color),
      m_Intensity(intensity),
      m_Constant(constant),
      m_Linear(linear),
      m_Quadratic(quadratic),
      m_InnerCutOff(innerCutOff),
      m_OuterCutOff(outerCutOff)
{
}

Light::~Light()
{
}

void Light::SetPosition(const glm::vec3& position)
{
    m_Position = position;
}

const glm::vec3& Light::GetPosition() const
{
    return m_Position;
}

void Light::SetType(LightType type)
{
    m_Type = type;
}

LightType Light::GetType() const
{
    return m_Type;
}

void Light::SetDirection(const glm::vec3& direction)
{
    m_Direction = direction;
}

const glm::vec3& Light::GetDirection() const
{
    return m_Direction;
}

void Light::SetColor(const glm::vec3& color) 
{
    m_Color = color;
}

const glm::vec3& Light::GetColor() const
{
    return m_Color;
}

void Light::SetIntensity(float intensity) 
{
    m_Intensity = intensity;
}

float Light::GetIntensity() const
{
    return m_Intensity;
}

void Light::SetConstant(float constant)
{
    m_Constant = constant;
}

float Light::GetConstant() const
{
    return m_Constant;
}

void Light::SetLinear(float linear)
{
    m_Linear = linear;
}

float Light::GetLinear() const
{
    return m_Linear;
}

void Light::SetQuadratic(float quadratic)
{
    m_Quadratic = quadratic;
}

float Light::GetQuadratic() const
{
    return m_Quadratic;
}

void Light::SetInnerCutoff(float cutoff)
{
    m_InnerCutOff = cutoff;
}

float Light::GetInnerCutoff() const
{
    return m_InnerCutOff;
}

void Light::SetOuterCutoff(float cutoff)
{
    m_OuterCutOff = cutoff;
}

float Light::GetOuterCutoff() const
{
    return m_OuterCutOff;
}