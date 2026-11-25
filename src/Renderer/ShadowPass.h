#pragma once
#include "ShadowMap.h"
#include "Resources/Shader.h"
#include "RenderQueue.h"


class ShadowPass
{
private:
    ShadowMap& m_ShadowMap;
    Shader& m_ShadowDepthShader;
public:
    ShadowPass(ShadowMap& shadowMap, Shader& shadowDepthShader);
    ~ShadowPass();

    void Render(const RenderQueue& queue, const glm::mat4& lightSpaceMatrix);
};


