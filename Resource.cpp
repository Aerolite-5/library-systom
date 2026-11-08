#pragma execution_character_set("utf-8")
#include "Resource.h"

Resource::Resource(const std::string& id, const std::string& name,
                   const std::string& category)
    : id(id), name(name), category(category)
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

std::string Resource::GetCategory() const
{
    return category;
}

void Resource::SetName(const std::string& value)
{
    name = value;
}

void Resource::SetCategory(const std::string& value)
{
    category = value;
}

std::ostream& operator<<(std::ostream& os, const Resource& resource)
{
    resource.Show(os);
    return os;
}
