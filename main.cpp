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

void AddResourceFlow(Library& library)
{
    std::cout << "\n资源类型：1-图书  2-杂志  3-电子资源\n";
    const int type = ReadInt("类型：");
    const std::string id = ReadText("编号：");
    const std::string name = ReadText("名称：");

    if (type == 1)
    {
        const int stock = ReadInt("库存：");
        const std::string author = ReadText("作者：");
        const std::string publisher = ReadText("出版社：");
        library.AddBook(id, name, stock, author, publisher);
    }
    else if (type == 2)
    {
        const int stock = ReadInt("库存：");
        const std::string issue = ReadText("期号：");
        library.AddMagazine(id, name, stock, issue);
    }
    else if (type == 3)
    {
        const std::string format = ReadText("格式：");
        const double size = ReadDouble("大小(MB)：");
        library.AddES(id, name, format, size);
    }
    else
    {
        std::cout << "资源类型无效。\n";
    }
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

void AddStockFlow(Library& library)
{
    const std::string resourceId = ReadText("资源编号：");
    const int count = ReadInt("增加数量：");
    library.AddStock(resourceId, count);
}

void SearchFlow(Library& library)
{
    const std::string keyword = ReadText("关键字（编号/名称）：");
    const std::vector<Resource*> result = library.Search(keyword);
    if (result.empty())
    {
        std::cout << "没有找到匹配的资源。\n";
        return;
    }
    for (std::size_t i = 0; i < result.size(); ++i)
        result[i]->Show();
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
        std::cout << "\n===== 图书借阅管理 =====\n"
                  << "1. 添加资源\n"
                  << "2. 增加库存\n"
                  << "3. 借书\n"
                  << "4. 还书\n"
                  << "5. 查看资源\n"
                  << "6. 查询资源\n"
                  << "7. 查看读者\n"
                  << "8. 查看借阅记录\n"
                  << "0. 退出\n"
                  << "请选择：";
        const int choice = ReadInt("");
        if (std::cin.eof() || choice == 0)
            break;

        if (choice == 1)
            AddResourceFlow(library);
        else if (choice == 2)
            AddStockFlow(library);
        else if (choice == 3)
            BorrowFlow(library);
        else if (choice == 4)
            ReturnFlow(library);
        else if (choice == 5)
            library.ShowResources();
        else if (choice == 6)
            SearchFlow(library);
        else if (choice == 7)
            library.ShowReaders();
        else if (choice == 8)
            library.ShowRecords();
        else
            std::cout << "没有该选项。\n";
    }

    std::cout << "再见！\n";
    return 0;
}
