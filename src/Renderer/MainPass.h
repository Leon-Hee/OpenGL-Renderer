#pragma once
#include "RenderQueue.h"
#include "Renderer.h"
#include "Camera.h"
#include "Light.h"
#include "DrawContext.h"

class MainPass
{
private:
    Renderer& m_Renderer;
public:
    MainPass(Renderer& renderer);
    ~MainPass();
    void Render(RenderQueue& queue, Camera& camera, const DrawContext& context);
};

