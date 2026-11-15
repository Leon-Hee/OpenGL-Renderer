#include "Scene.h"

Scene::Scene(/* args */)
{
    m_NextEntityID = 1;
}

Entity& Scene::CreateEntity(const std::string& name) 
{
    // 在堆上创建 Entity，并由 unique_ptr 自动管理其生命周期。
    // vector 中保存的是指向 Entity 的 unique_ptr，而不是 Entity 本身。
    m_Entities.emplace_back(std::make_unique<Entity>(m_NextEntityID, name));
    m_NextEntityID++;

    // back() 返回最后一个 unique_ptr。
    // * 解引用 unique_ptr，得到真正的 Entity 对象。
    // 返回 Entity&，因此调用者可以直接访问这个 Entity。
    return *m_Entities.back();
    
}

