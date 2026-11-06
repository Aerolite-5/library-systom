#pragma once
#include "Reader.h"

class Student : public Reader
{
    std::string major;

public:
    Student(const std::string& id, const std::string& name,
            const std::string& major);

    std::string Type() const override;
    int GetMaxBorrow() const override;
    int GetLoanDays() const override;
    void Show() const override;
};
