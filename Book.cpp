#pragma execution_character_set("utf-8")
#include "Book.h"

Book::Book(const std::string& id, const std::string& name,
           const std::string& category, const std::string& author,
           const std::string& publisher, int stock)
    : PhysicalResource(id, name, category, stock), author(author), publisher(publisher)
{
}

std::string Book::GetAuthor() const
{
    return author;
}

std::string Book::GetPublisher() const
{
    return publisher;
}

std::string Book::Type() const
{
    return "图书";
}

void Book::Show(std::ostream& os) const
{
    os << "[" << Type() << "] 编号:" << GetId()
       << " 书名:" << GetName()
       << " 分类:" << GetCategory();
    ShowStock(os);
    os << " 作者:" << author << " 出版社:" << publisher;
}
