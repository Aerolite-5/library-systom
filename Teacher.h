#pragma once
#include "Reader.h"

class Teacher : public Reader
{
    std::string department;
    std::string title;

public:
    Teacher(const std::string& id, const std::string& name,
            const std::string& department, const std::string& title);

    std::string GetDepartment() const;
    std::string GetTitle() const;

    std::string Type() const override;
    int GetMaxBorrowCount() const override;
    int GetLoanDays() const override;
    void Show(std::ostream& os) const override;
};
