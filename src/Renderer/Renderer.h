#pragma once
#include "Resources/Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "RenderType.h"
#include "RenderQueue.h"
#include "Light.h"
#include <vector>

class Renderer
{
private:
    glm::mat4 m_LightSpaceMatrix;
    unsigned int m_ShadowMap = 0;
public:
    void Init(); // 初始化Renderer的属性，如深度检测
    void BeginFrame(); // 帧开始
    void Clear(); // 清空缓冲区
    void EndFrame(); // 帧结束
    void Draw(const RenderItem& renderItem, Camera& camera, Light& light); // 画
    void SetClearColor(float r, float g, float b, float a);
    void SetViewPort(int x, int y, int width, int height);
    void SetWireFrame(bool enabled);
    void SetDepthTest(bool enabled);
    void SetBlend(bool enabled);
    void SetBlendFunc();
    void SetDepthWrite(bool enabled);
    void SetRenderType(RenderType type);
    void Execute(RenderQueue& queue, Camera& camera, Light& light);
    void SetDepthTestFunc(unsigned int function);
    void SetFaceCulling(bool enabled);
    void SetFrontFace(unsigned int mode);
    void SetCullFace(unsigned int mode);
    void SetLightSpaceMatrix(const glm::mat4& lightSpaceMatrix);
    void SetShadowMap(unsigned int texture);
};


