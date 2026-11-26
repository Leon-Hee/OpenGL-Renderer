#include "MainPass.h"

MainPass::MainPass(Renderer& renderer)
    : m_Renderer(renderer)
{

}

MainPass::~MainPass()
{
}


void MainPass::Render(RenderQueue& queue, Camera& camera, const DrawContext& context)
{
    const std::vector<RenderItem>& renderOpaqueItems = queue.GetOpaqueItems();
    
    for(const auto& item : renderOpaqueItems) {
        m_Renderer.Draw(item, context);
    }
    queue.SortTransparent(camera);
    const std::vector<RenderItem>& renderTransparentItems = queue.GetTransparentItems();
    
    for(const auto& item : renderTransparentItems) {
        m_Renderer.Draw(item, context);
    }
}