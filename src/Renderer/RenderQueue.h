#pragma once 

#include "Resources/Mesh.h"
#include "Transform.h"
#include <vector>
#include "Camera.h"

struct RenderItem
{
    Mesh* m_Mesh;
    Transform* m_Transform;
};

class RenderQueue
{
private:
    std::vector<RenderItem> m_OpaqueItems;
    std::vector<RenderItem> m_TransparentItems;
public:
    RenderQueue(/* args */);
    ~RenderQueue();
    void Submit(Mesh& mesh, Transform& transform);
    const std::vector<RenderItem>& GetOpaqueItems() const;
    const std::vector<RenderItem>& GetTransparentItems() const;
    void SortTransparent(Camera& camera);
    void Clear();
};



