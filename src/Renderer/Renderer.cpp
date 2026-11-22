#include "Renderer.h"
#include <GLFW/glfw3.h>

void Renderer::BeginFrame() 
{

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
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST); // 开启深度检测
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

void Renderer::Draw(Mesh& mesh, Transform& transform, Camera& camera)
{
    Material& material = mesh.GetMaterial();
    material.Bind();
    SetRenderType(material.GetRenderType());
    material.SetMat4("u_Model", transform.GetMatrix());
    material.SetMat4("u_View", camera.GetViewMatrix());
    material.SetMat4("u_Projection", camera.GetProjectionMatrix());
    mesh.Draw();
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