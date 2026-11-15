#include <string>

class Entity
{
private:
    unsigned int m_ID;
    std::string m_Name;
public:
    Entity(unsigned int id, const std::string& name);
    
    unsigned int GetID() const;
    const std::string& GetName() const;
};

