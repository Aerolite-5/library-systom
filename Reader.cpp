#pragma execution_character_set("utf-8")
#include "Reader.h"

Reader::Reader(const std::string& id, const std::string& name)
    : id(id), name(name)
{
}

std::string Reader::GetId() const
{
    return id;
}

std::string Reader::GetName() const
{
    return name;
}

std::ostream& operator<<(std::ostream& os, const Reader& reader)
{
    reader.Show(os);
    return os;
}
