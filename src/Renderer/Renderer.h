#pragma once
#include "Resources/Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "RenderType.h"
#include "RenderQueue.h"
#include "Light.h"
#include <vector>
#include "DrawContext.h"

class Renderer
{
private:
    void SetRenderType(RenderType type);
public:
    void Init(); // 初始化Renderer的属性，如深度检测
    void BeginFrame(); // 帧开始
    void Clear(); // 清空缓冲区
    void EndFrame(); // 帧结束
    void Draw(const RenderItem& renderItem, const DrawContext& context); // 画
    void SetClearColor(float r, float g, float b, float a);
    void SetViewPort(int x, int y, int width, int height);
    void SetWireFrame(bool enabled);
    void SetDepthTest(bool enabled);
    void SetBlend(bool enabled);
    void SetBlendFunc(unsigned int source, unsigned int destination);
    void SetDepthWrite(bool enabled);

    void SetDepthTestFunc(unsigned int function);
    void SetFaceCulling(bool enabled);
    void SetFrontFace(unsigned int mode);
    void SetCullFace(unsigned int mode);
};


