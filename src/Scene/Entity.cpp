#include "Entity.h"

Entity::Entity(unsigned int id, const std::string& name)
{
    m_ID = id;
    m_Name = name;
}

unsigned int Entity::GetID() const 
{
    return m_ID;
}
const std::string& Entity::GetName() const
{
    return m_Name;
}