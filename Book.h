#pragma once
#include "Resource.h"

class Book : public Resource
{
    int stock;
    std::string author;
    std::string publisher;

public:
    Book(const std::string& id, const std::string& name, int stock,
         const std::string& author, const std::string& publisher);

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
