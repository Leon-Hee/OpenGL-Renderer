#pragma once
#include "Resources/Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "RenderType.h"

class Renderer
{
private:
    
public:
    void Init(); // 初始化Renderer的属性，如深度检测
    void BeginFrame(); // 帧开始
    void Clear(); // 清空缓冲区
    void EndFrame(); // 帧结束
    void Draw(Mesh& mesh, Transform& transform, Camera& camera); // 画
    void SetClearColor(float r, float g, float b, float a);
    void SetViewPort(int x, int y, int width, int height);
    void SetWireFrame(bool enabled);
    void SetDepthTest(bool enabled);
    void SetBlend(bool enabled);
    void SetBlendFunc();
    void SetDepthWrite(bool enabled);
    void SetRenderType(RenderType type);
};


