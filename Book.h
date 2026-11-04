#pragma once
#include "Resource.h"

// 纸质图书：有库存，借出减 1，归还加 1。
class Book : public Resource
{
    int stock;
    std::string author;

public:
    Book(const std::string& id, const std::string& name,
         int stock, const std::string& author);

    int GetStock() const;

    std::string Type() const override;
    bool CanBorrow() const override;
    void OnBorrow() override;
    void OnReturn() override;
    void Show() const override;
};
