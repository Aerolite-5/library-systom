#pragma execution_character_set("utf-8")
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Library.h"

namespace
{
std::string ReadText(const std::string& prompt)
{
    std::cout << prompt;
    std::string text;
    std::getline(std::cin, text);
    return text;
}

int ReadInt(const std::string& prompt)
{
    const std::string text = ReadText(prompt);
    try
    {
        return std::stoi(text);
    }
    catch (...)
    {
        return 0;
    }
}

double ReadDouble(const std::string& prompt)
{
    const std::string text = ReadText(prompt);
    try
    {
        return std::stod(text);
    }
    catch (...)
    {
        return 0.0;
    }
}

void AddBookFlow(Library& library)
{
    const std::string id = ReadText("图书编号：");
    const std::string name = ReadText("书名：");
    const int stock = ReadInt("库存：");
    const std::string author = ReadText("作者：");
    library.AddBook(id, name, stock, author);
}

void AddEBookFlow(Library& library)
{
    const std::string id = ReadText("电子书编号：");
    const std::string name = ReadText("名称：");
    const double size = ReadDouble("大小(MB)：");
    library.AddEBook(id, name, size);
}

void BorrowFlow(Library& library)
{
    std::cout << "\n资源列表：\n";
    library.ShowResources();
    std::cout << "\n读者列表：\n";
    library.ShowReaders();
    const std::string resourceId = ReadText("资源编号：");
    const std::string readerId = ReadText("读者编号：");
    library.Borrow(resourceId, readerId);
}

void ReturnFlow(Library& library)
{
    const std::string resourceId = ReadText("资源编号：");
    const std::string readerId = ReadText("读者编号：");
    library.Return(resourceId, readerId);
}
} // namespace

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Library library;
    while (true)
    {
        std::cout << "\n===== 图书借阅管理（实验三）=====\n"
                  << "1. 添加图书\n"
                  << "2. 添加电子书\n"
                  << "3. 借书\n"
                  << "4. 还书\n"
                  << "5. 查看资源\n"
                  << "6. 查看借阅记录\n"
                  << "0. 退出\n"
                  << "请选择：";

        const int choice = ReadInt("");
        if (std::cin.eof() || choice == 0)
            break;

        if (choice == 1)
            AddBookFlow(library);
        else if (choice == 2)
            AddEBookFlow(library);
        else if (choice == 3)
            BorrowFlow(library);
        else if (choice == 4)
            ReturnFlow(library);
        else if (choice == 5)
            library.ShowResources();
        else if (choice == 6)
            library.ShowRecords();
        else
            std::cout << "没有该选项。\n";
    }

    std::cout << "再见！\n";
    return 0;
}
