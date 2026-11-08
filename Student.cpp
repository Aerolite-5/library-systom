#pragma execution_character_set("utf-8")
#include "Student.h"

Student::Student(const std::string& id, const std::string& name,
                 const std::string& major)
    : Reader(id, name), major(major)
{
}

std::string Student::GetMajor() const
{
    return major;
}

std::string Student::Type() const
{
    return "学生";
}

int Student::GetMaxBorrowCount() const
{
    return 5;
}

int Student::GetLoanDays() const
{
    return 30;
}

void Student::Show(std::ostream& os) const
{
    os << "[学生] " << GetId() << " " << GetName()
       << "（" << major << "）";
}
