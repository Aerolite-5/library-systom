#pragma execution_character_set("utf-8")
#include "Student.h"

#include <iostream>

Student::Student(const std::string& id, const std::string& name,
                 const std::string& major)
    : Reader(id, name), major(major)
{
}

std::string Student::Type() const
{
    return "学生";
}

int Student::GetMaxBorrow() const
{
    return 5;
}

int Student::GetLoanDays() const
{
    return 30;
}

void Student::Show() const
{
    std::cout << "[学生] " << id << " " << name << "（" << major
              << "） 最多借 5 项，借期 30 天\n";
}
