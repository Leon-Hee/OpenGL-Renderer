#include "Renderer.h"
#include <GLFW/glfw3.h>

void Renderer::BeginFrame() 
{
    Clear();
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清空颜色和深度缓冲区
}

void Renderer::EndFrame()
{

}

void Renderer::Init()
{
    SetDepthTestFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST); // 开启深度检测
    SetFaceCulling(true);
    SetFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

void Renderer::Draw(const RenderItem& renderItem, const DrawContext& context)
{
    Material& material = renderItem.m_Mesh->GetMaterial();
    material.Bind();
    SetRenderType(material.GetRenderType());
    material.SetMat4("u_Model", renderItem.m_Transform->GetMatrix());
    material.SetMat4("u_View", context.view);
    material.SetMat4("u_Projection", context.projection);
    material.SetMat4("u_LightSpaceMatrix", context.lightSpaceMatrix);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(
        GL_TEXTURE_2D,
        context.shadowMap
    );
    material.SetInt(
        "u_ShadowMap",
        2
    );
    if (context.light.GetType() == LightType::Directional)
    {
        material.SetInt("u_LightType", 0);
        material.SetVec3(
            "u_LightDirection",
            context.light.GetDirection()
        );
    }

    else if (context.light.GetType() == LightType::Point)
    {
        material.SetInt("u_LightType", 1);
        material.SetVec3(
            "u_LightPosition",
            context.light.GetPosition()
        );
        material.SetFloat(
            "u_LightConstant",
            context.light.GetConstant()
        );

        material.SetFloat(
            "u_LightLinear",
            context.light.GetLinear()
        );

        material.SetFloat(
            "u_LightQuadratic",
            context.light.GetQuadratic()
        );

        material.SetVec3(
            "u_LightColor",
            context.light.GetColor()
        );
    }

    else if (context.light.GetType() == LightType::Spot)
    {
        material.SetInt("u_LightType", 2);

        material.SetVec3(
            "u_LightPosition",
            context.light.GetPosition()
        );

        material.SetVec3(
            "u_LightDirection",
            context.light.GetDirection()
        );

        material.SetFloat(
            "u_LightConstant",
            context.light.GetConstant()
        );

        material.SetFloat(
            "u_LightLinear",
            context.light.GetLinear()
        );

        material.SetFloat(
            "u_LightQuadratic",
            context.light.GetQuadratic()
        );

        material.SetFloat(
            "u_LightInnerCutoff",
            context.light.GetInnerCutoff()
        );

        material.SetFloat(
            "u_LightOuterCutoff",
            context.light.GetOuterCutoff()
        );

        material.SetVec3(
            "u_LightColor",
            context.light.GetColor()
        );
    }
    material.SetFloat("u_Intensity", context.light.GetIntensity());
    renderItem.m_Mesh->Draw();
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::SetViewPort(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void Renderer::SetWireFrame(bool enabled)
{
    if(enabled)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Renderer::SetDepthTest(bool enabled)
{
    if(enabled)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else 
    {
        glDisable(GL_DEPTH_TEST);
    }
}

void Renderer::SetBlend(bool enabled)
{
    if(enabled)
    {
        glEnable(GL_BLEND);
    }
    else
    {
        glDisable(GL_BLEND);
    }
}

void Renderer::SetBlendFunc()
{
    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );
}

void Renderer::SetDepthWrite(bool enabled)
{
    if(enabled)
    {
        glDepthMask(GL_TRUE);
    }
    else
    {
        glDepthMask(GL_FALSE);
    }
}

void Renderer::SetRenderType(RenderType type)
{
    if(type == RenderType::Opaque)
    {
        SetDepthTest(true);
        SetDepthWrite(true);
        SetBlend(false);
    }
    else if(type == RenderType::Transparent)
    {
        SetDepthTest(true);
        SetDepthWrite(false);
        SetBlend(true);
        SetBlendFunc();
    }
}



void Renderer::SetDepthTestFunc(unsigned int function)
{
    glDepthFunc(function);
}

void Renderer::SetFaceCulling(bool enabled)
{
    if(enabled)
    {
        glEnable(GL_CULL_FACE);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
}

void Renderer::SetFrontFace(unsigned int mode)
{
    glFrontFace(mode);
}

void Renderer::SetCullFace(unsigned int mode)
{
    glCullFace(mode);
}
