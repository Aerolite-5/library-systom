#pragma once
#include "Reader.h"

class Student : public Reader
{
    std::string major;

public:
    Student(const std::string& id, const std::string& name,
            const std::string& major);

    std::string GetMajor() const;

    std::string Type() const override;
    int GetMaxBorrowCount() const override;
    int GetLoanDays() const override;
    void Show(std::ostream& os) const override;
};
