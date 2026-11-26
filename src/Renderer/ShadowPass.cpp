#include "ShadowPass.h"

ShadowPass::ShadowPass(ShadowMap& shadowMap, Shader& shadowDepthShader)
    :
    m_ShadowMap(shadowMap),
    m_ShadowDepthShader(shadowDepthShader)
{
    
}

ShadowPass::~ShadowPass()
{
}

void ShadowPass::Render(const RenderQueue& queue, const glm::mat4& lightSpaceMatrix)
{
    m_ShadowMap.Bind();
    glViewport(0, 0, m_ShadowMap.GetWidth(), m_ShadowMap.GetHeight());
    glClear(GL_DEPTH_BUFFER_BIT);
    m_ShadowDepthShader.Bind();
    m_ShadowDepthShader.SetMat4("u_LightSpaceMatrix", lightSpaceMatrix);
    for(const RenderItem& item : queue.GetOpaqueItems()) {
        m_ShadowDepthShader.SetMat4("u_Model", item.m_Transform->GetMatrix());
        item.m_Mesh->Draw();
    }
    m_ShadowMap.Unbind();
}