#include "Renderer.h"
#include <GLFW/glfw3.h>

void Renderer::BeginFrame() 
{

}

void Renderer::Clear()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 红色
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清空颜色和深度缓冲区
}

void Renderer::EndFrame()
{

}

void Renderer::Init()
{
    glEnable(GL_DEPTH_TEST); // 开启深度检测
}