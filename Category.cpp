#pragma execution_character_set("utf-8")
#include "Category.h"

Category::Category(const std::string& id, const std::string& name)
    : id(id), name(name)
{
}

std::string Category::GetId() const
{
    return id;
}

std::string Category::GetName() const
{
    return name;
}

void Category::Show(std::ostream& os) const
{
    os << id << " " << name;
}

std::ostream& operator<<(std::ostream& os, const Category& category)
{
    category.Show(os);
    return os;
}
