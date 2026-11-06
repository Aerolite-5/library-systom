#pragma once
#include "Resource.h"

class Magazine : public Resource
{
    int stock;
    std::string issue;

public:
    Magazine(const std::string& id, const std::string& name, int stock,
             const std::string& issue);

    int GetStock() const;

    std::string Type() const override;
    bool IsDigital() const override;
    bool CanBorrow() const override;
    void OnBorrow() override;
    void OnReturn() override;
    bool AddStock(int count) override;
    std::string BorrowMessage() const override;
    void Show() const override;
};
