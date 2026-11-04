#pragma execution_character_set("utf-8")
#include "Reader.h"

#include <iostream>

Reader::Reader(const std::string& id, const std::string& name,
               const std::string& role)
    : id(id), name(name), role(role),
      maxBorrow(role == "教师" ? 10 : 5)
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

int Reader::GetMaxBorrow() const
{
    return maxBorrow;
}

void Reader::Show() const
{
    std::cout << "[" << role << "] " << id << " " << name
              << " 最多借 " << maxBorrow << " 项\n";
}
