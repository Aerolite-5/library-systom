#include <iostream>
#include <vector>
#include <string>
#include "Book.h"

class Reader
{
private:
    std::string name;
public:
    Reader(std::string name);
    void BorrowBook(Book* book);
    void ReturnBook(Book* book);
};

Reader::Reader(std::string name)
{
    this->name = name;
}

void Reader::BorrowBook(Book* book)
{
    std::cout << name << "尝试借阅【" << book->GetName() << "】" << std::endl;
    if (book->Borrow())
    {
        std::cout << "借书成功！" << std::endl;
    }
    else
    {
        std::cout << "该书已被借出！" << std::endl;
    }
}

void Reader::ReturnBook(Book* book)
{
    std::cout << name << "归还【" << book->GetName() << "】" << std::endl;
    if (book->Return())
    {
        std::cout << "还书成功！" << std::endl;
    }
    else
    {
        std::cout << "该书未借出！" << std::endl;
    }
}

class Library
{
private:
    std::vector<Book> bookList;
public:
    void AddBook(Book book);
    void ShowAllBooks() const;
    Book* GetBookById(std::string id);
};

void Library::AddBook(Book book)
{
    bookList.push_back(book);
}

void Library::ShowAllBooks() const
{
    std::cout << "\n图书列表" << std::endl;
    for (auto& b : bookList)
    {
        std::cout << "书号：" << b.GetId()
            << " 书名：" << b.GetName()
            << " 状态：" << (b.IsBorrowed() ? "已借出" : "可借阅") << std::endl;
    }
    std::cout << std::endl;
}

Book* Library::GetBookById(std::string id)
{
    for (auto& book : bookList)
    {
        if (book.GetId() == id)
        {
            return &book;
        }
    }
    return nullptr;
}

int main()
{
    Library lib;
    lib.AddBook(Book("B001", "语文"));
    lib.AddBook(Book("B002", "数学"));
    lib.AddBook(Book("B003", "英语"));

    Reader stu("小明");
    lib.ShowAllBooks();

    Book* pBook = lib.GetBookById("B001");

    stu.BorrowBook(pBook);
    stu.BorrowBook(pBook);
    stu.ReturnBook(pBook);
    stu.BorrowBook(pBook);

    std::cout << "\n借阅后图书状态" << std::endl;
    lib.ShowAllBooks();

    return 0;
}
