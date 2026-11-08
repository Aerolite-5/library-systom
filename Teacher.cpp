#pragma execution_character_set("utf-8")
#include "Teacher.h"

Teacher::Teacher(const std::string& id, const std::string& name,
                 const std::string& department, const std::string& title)
    : Reader(id, name), department(department), title(title)
{
}

std::string Teacher::GetDepartment() const
{
    return department;
}

std::string Teacher::GetTitle() const
{
    return title;
}

std::string Teacher::Type() const
{
    return "教师";
}

int Teacher::GetMaxBorrowCount() const
{
    return 10;
}

int Teacher::GetLoanDays() const
{
    return 60;
}

void Teacher::Show(std::ostream& os) const
{
    os << "[教师] " << GetId() << " " << GetName()
       << "（" << department << " " << title << "）";
}
