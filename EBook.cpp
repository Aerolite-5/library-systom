#pragma execution_character_set("utf-8")
#include "EBook.h"

#include <iomanip>
#include <iostream>

EBook::EBook(const std::string& id, const std::string& name, double sizeMB)
    : Resource(id, name), sizeMB(sizeMB > 0.0 ? sizeMB : 0.0)
{
}

std::string EBook::Type() const
{
    return "电子书";
}

bool EBook::CanBorrow() const
{
    return true;
}

void EBook::OnBorrow()
{
}

void EBook::OnReturn()
{
}

void EBook::Show() const
{
    std::cout << "[电子书] 编号:" << id
              << " 名称:" << name
              << " 大小:" << std::fixed << std::setprecision(1) << sizeMB
              << "MB 可多人同时借阅\n";
}
