#pragma execution_character_set("utf-8")
#include "Teacher.h"

#include <iostream>

Teacher::Teacher(const std::string& id, const std::string& name,
                 const std::string& department, const std::string& title)
    : Reader(id, name), department(department), title(title)
{
}

std::string Teacher::Type() const
{
    return "教师";
}

int Teacher::GetMaxBorrow() const
{
    return 10;
}

int Teacher::GetLoanDays() const
{
    return 60;
}

void Teacher::Show() const
{
    std::cout << "[教师] " << id << " " << name << "（" << department
              << " " << title << "） 最多借 10 项，借期 60 天\n";
}
