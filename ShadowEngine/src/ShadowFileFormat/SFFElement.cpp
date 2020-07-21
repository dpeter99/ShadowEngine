#include "shpch.h"
#include "SFFElement.h"

SFFElement* SFFElement::GetFirstChild()
{
    return children.size() > 0 ? children[0]: nullptr;
}

SFFElement* SFFElement::GetChildByIndex(int i)
{
   ChildrenMap::iterator it = children.begin();
    for (size_t i = 0; i < i; i++)
    {
        it++;
    }
    return it->second;
}

SFFElement* SFFElement::GetChildByName(std::string name)
{
    ChildrenMap::iterator it = children.find(name);
    if (it != children.end()) {
        return it->second;
    }
    return nullptr;
}
