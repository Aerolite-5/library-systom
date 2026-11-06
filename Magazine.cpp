#pragma execution_character_set("utf-8")
#include "Magazine.h"

#include <iostream>

Magazine::Magazine(const std::string& id, const std::string& name, int stock,
                   const std::string& issue)
    : Resource(id, name), stock(stock > 0 ? stock : 0), issue(issue)
{
}

int Magazine::GetStock() const
{
    return stock;
}

std::string Magazine::Type() const
{
    return "杂志";
}

bool Magazine::IsDigital() const
{
    return false;
}

bool Magazine::CanBorrow() const
{
    return stock > 0;
}

void Magazine::OnBorrow()
{
    if (stock > 0)
        --stock;
}

void Magazine::OnReturn()
{
    ++stock;
}

bool Magazine::AddStock(int count)
{
    if (count <= 0)
        return false;
    stock += count;
    return true;
}

std::string Magazine::BorrowMessage() const
{
    return "借阅成功，杂志库存已减少。";
}

void Magazine::Show() const
{
    std::cout << "[杂志] 编号:" << id << " 名称:" << name
              << " 库存:" << stock
              << " 期号:" << issue << "\n";
}
