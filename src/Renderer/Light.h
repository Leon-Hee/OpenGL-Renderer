#pragma once
#include <glm/glm.hpp>

enum class LightType
{
    Directional,
    Point,
    Spot
};

class Light
{
private:
    LightType m_Type;
    glm::vec3 m_Position;
    glm::vec3 m_Direction;
    glm::vec3 m_Color;
    float m_Intensity;
    float m_Constant;
    float m_Linear;
    float m_Quadratic;
    float m_InnerCutOff;
    float m_OuterCutOff;
public:
    Light( // 种类，位置，方向，颜色，强度，常数项，一次项，二次项，内圆锥，外圆锥
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
    );
    ~Light();

    void SetType(LightType type);
    LightType GetType() const;

    void SetPosition(const glm::vec3& position);
    const glm::vec3& GetPosition() const;

    void SetDirection(const glm::vec3& direction);
    const glm::vec3& GetDirection() const;

    void SetColor(const glm::vec3& color);
    const glm::vec3& GetColor() const;

    void SetIntensity(float intensity);
    float GetIntensity() const;

    void SetConstant(float constant);
    float GetConstant() const;

    void SetLinear(float linear);
    float GetLinear() const;

    void SetQuadratic(float quadratic);
    float GetQuadratic() const;

    void SetInnerCutoff(float cutoff); // 存cos值
    float GetInnerCutoff() const;

    void SetOuterCutoff(float cutoff); // 存cos值
    float GetOuterCutoff() const;
};


