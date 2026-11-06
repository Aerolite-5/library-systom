#pragma once
#include "Reader.h"

class Teacher : public Reader
{
    std::string department;
    std::string title;

public:
    Teacher(const std::string& id, const std::string& name,
            const std::string& department, const std::string& title);

    std::string Type() const override;
    int GetMaxBorrow() const override;
    int GetLoanDays() const override;
    void Show() const override;
};
