#include "RenderQueue.h"

RenderQueue::RenderQueue(/* args */)
{
}

RenderQueue::~RenderQueue()
{
}

void RenderQueue::Submit(Mesh& mesh, Transform& transform)
{
    RenderItem renderItem;
    renderItem.m_Mesh = &mesh;
    renderItem.m_Transform = &transform;
    RenderType renderType = renderItem.m_Mesh->GetMaterial().GetRenderType();
    if(renderType == RenderType::Opaque) {
        m_OpaqueItems.push_back(renderItem);
    } else if(renderType == RenderType::Transparent) {
        m_TransparentItems.push_back(renderItem);
    }
}

const std::vector<RenderItem>& RenderQueue::GetOpaqueItems() const
{
    return m_OpaqueItems;
}

const std::vector<RenderItem>& RenderQueue::GetTransparentItems() const
{
    return m_TransparentItems;
}

void RenderQueue::SortTransparent(Camera& camera) 
{
    sort(m_TransparentItems.begin(), m_TransparentItems.end(), [&camera](const RenderItem& a, const RenderItem& b){
        glm::vec3 delta_a = a.m_Transform->GetPosition() - camera.GetPosition();
        glm::vec3 delta_b = b.m_Transform->GetPosition() - camera.GetPosition();
        float distance_a = glm::dot(delta_a, delta_a);
        float distance_b = glm::dot(delta_b, delta_b);
        return distance_a > distance_b;
    });
}

void RenderQueue::Clear() 
{
    m_OpaqueItems.clear();
    m_TransparentItems.clear();
}