#pragma once 

#include "Entity.h"
#include <vector>
#include <memory>

class Scene
{
private:
    // Scene 保存所有 Entity。
    // vector 扩容时只移动 unique_ptr，不会移动真正的 Entity 对象，
    // 因此 Entity 在内存中的地址保持稳定。
    std::vector<std::unique_ptr<Entity>> m_Entities;
    // 下一个 Entity 使用的唯一 ID。
    unsigned int m_NextEntityID;
public:
    Scene();
    Entity& CreateEntity(const std::string& name);
};



