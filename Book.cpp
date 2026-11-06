#pragma execution_character_set("utf-8")
#include "Book.h"

#include <iostream>

Book::Book(const std::string& id, const std::string& name, int stock,
           const std::string& author, const std::string& publisher)
    : Resource(id, name), stock(stock > 0 ? stock : 0),
      author(author), publisher(publisher)
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

bool Book::IsDigital() const
{
    return false;
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

bool Book::AddStock(int count)
{
    if (count <= 0)
        return false;
    stock += count;
    return true;
}

std::string Book::BorrowMessage() const
{
    return "借阅成功，纸质书库存已减少。";
}

void Book::Show() const
{
    std::cout << "[图书] 编号:" << id << " 书名:" << name
              << " 库存:" << stock
              << " 作者:" << author
              << " 出版社:" << publisher << "\n";
}
