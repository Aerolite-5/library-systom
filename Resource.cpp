#pragma execution_character_set("utf-8")
#include "Resource.h"

Resource::Resource(const std::string& id, const std::string& name)
    : id(id), name(name)
{
}

std::string Resource::GetId() const
{
    return id;
}

std::string Resource::GetName() const
{
    return name;
}
