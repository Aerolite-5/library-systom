#pragma execution_character_set("utf-8")
#include "Book.h"

#include <iostream>

Book::Book(const std::string& id, const std::string& name,
           int stock, const std::string& author)
    : Resource(id, name), stock(stock > 0 ? stock : 0), author(author)
{
}

int Book::GetStock() const
{
    return stock;
}

std::string Book::Type() const
{
    return "图书";
}

bool Book::CanBorrow() const
{
    return stock > 0;
}

void Book::OnBorrow()
{
    if (stock > 0)
        --stock;
}

void Book::OnReturn()
{
    ++stock;
}

void Book::Show() const
{
    std::cout << "[图书] 编号:" << id
              << " 书名:" << name
              << " 库存:" << stock
              << " 作者:" << author << "\n";
}
