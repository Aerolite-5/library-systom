#pragma execution_character_set("utf-8")
#include <cstdlib>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#include <io.h>
#include <windows.h>
#endif

#include "Account.h"
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
    for (;;)
    {
        const std::string text = ReadText(prompt);
        if (std::cin.eof())
            return 0;
        try
        {
            return std::stoi(text);
        }
        catch (...)
        {
            std::cout << "请输入数字。\n";
        }
    }
}

double ReadDouble(const std::string& prompt)
{
    for (;;)
    {
        const std::string text = ReadText(prompt);
        if (std::cin.eof())
            return 0.0;
        try
        {
            return std::stod(text);
        }
        catch (...)
        {
            std::cout << "请输入数字。\n";
        }
    }
}

std::string ReadPassword(const std::string& prompt)
{
    std::cout << prompt;
    std::cout.flush();

#ifdef _WIN32
    if (_isatty(_fileno(stdin)))
    {
        std::string password;
        for (;;)
        {
            const int ch = _getch();
            if (ch == '\r' || ch == '\n')
            {
                std::cout << "\n";
                break;
            }
            if (ch == 3)
            {
                std::cout << "\n";
                std::exit(0);
            }
            if (ch == 26)
            {
                std::cout << "\n";
                std::cin.setstate(std::ios::eofbit);
                break;
            }
            if (ch == 8)
            {
                if (!password.empty())
                {
                    password.pop_back();
                    std::cout << "\b \b";
                }
                continue;
            }
            if (ch >= 32 && ch <= 126)
            {
                password.push_back(static_cast<char>(ch));
                std::cout << '*';
            }
        }
        return password;
    }
#endif

    std::string password;
    std::getline(std::cin, password);
    return password;
}

bool LoginFlow(Account& auth)
{
    std::cout << "\n========== 图书借阅管理系统 ==========\n";
    while (!auth.IsLoggedIn())
    {
        const std::string username = ReadText("用户名（0 退出）：");
        if (std::cin.eof() || username == "0")
            return false;

        const std::string password = ReadPassword("密码：");
        if (std::cin.eof())
            return false;

        auth.Login(username, password);
    }
    return true;
}

void ShowMainMenu(const Account& auth)
{
    std::cout << "\n========== 图书借阅管理系统 ==========\n"
              << " 当前用户：" << auth.CurrentUsername() << "\n"
              << "--------------------------------------\n"
              << " 1. 新增资源        2. 增加库存\n"
              << " 3. 查看单个资源    4. 查看全部资源\n"
              << " 5. 减少库存        6. 删除资源\n"
              << " 7. 借书            8. 还书\n"
              << " 9. 修改资源信息   10. 查询资源\n"
              << "11. 查看借阅记录   12. 借阅统计\n"
              << "13. 添加读者       14. 删除读者\n"
              << "15. 罚款单管理     16. 借阅热度统计\n"
              << " 0. 退出\n"
              << "======================================\n";
}

void ShowCategories(Library& library)
{
    std::cout << "已有分类：";
    const auto& categories = library.Resources().Categories();
    for (std::size_t i = 0; i < categories.size(); ++i)
        std::cout << categories[i] << "  ";
    std::cout << "\n";
}

void AddResourceFlow(Library& library)
{
    std::cout << "\n资源类型：1-图书  2-杂志  3-电子资源\n";
    const int type = ReadInt("资源类型：");
    const std::string id = ReadText("资源编号：");
    if (library.Resources().Find(id) != nullptr)
    {
        std::cout << "资源编号已存在。\n";
        return;
    }

    const std::string name = ReadText("资源名称：");
    ShowCategories(library);
    const std::string category = ReadText("分类名称：");

    if (type == 1)
    {
        const std::string author = ReadText("作者：");
        const std::string publisher = ReadText("出版社：");
        const int stock = ReadInt("库存数量：");
        library.Resources().AddBook(id, name, category, author, publisher, stock);
    }
    else if (type == 2)
    {
        const std::string issue = ReadText("期号：");
        const int stock = ReadInt("库存数量：");
        library.Resources().AddMagazine(id, name, category, issue, stock);
    }
    else if (type == 3)
    {
        const std::string format = ReadText("格式：");
        const double size = ReadDouble("大小(MB)：");
        library.Resources().AddES(id, name, category, format, size);
    }
    else
    {
        std::cout << "资源类型无效。\n";
    }
}

void AddStockFlow(Library& library)
{
    const std::string id = ReadText("资源编号：");
    const int count = ReadInt("增加数量：");
    library.Resources().AddStock(id, count);
}

void ReduceStockFlow(Library& library)
{
    const std::string id = ReadText("资源编号：");
    const int count = ReadInt("减少数量：");
    library.Resources().ReduceStock(id, count);
}

void BorrowFlow(Library& library)
{
    std::cout << "\n读者列表：\n";
    library.Readers().ShowAll();
    const std::string resourceId = ReadText("资源编号：");
    const std::string readerId = ReadText("读者编号（学号/工号）：");
    library.Loans().Borrow(resourceId, readerId);
}

void ReturnFlow(Library& library)
{
    const std::string resourceId = ReadText("资源编号：");
    const std::string readerId = ReadText("读者编号（学号/工号）：");
    library.Loans().Return(resourceId, readerId);
}

void ModifyFlow(Library& library)
{
    const std::string id = ReadText("资源编号：");
    const Resource* resource = library.Resources().Find(id);
    if (resource == nullptr)
    {
        std::cout << "未找到资源。\n";
        return;
    }
    std::cout << "当前信息：" << *resource << "\n";
    const std::string name = ReadText("新名称（直接回车保持不变）：");
    const std::string category = ReadText("新分类（直接回车保持不变）：");
    library.Resources().Modify(id, name, category);
}

void SearchFlow(Library& library)
{
    const std::string keyword = ReadText("关键字（编号/名称/分类）：");
    const std::vector<Resource*> result = library.Resources().Search(keyword);
    if (result.empty())
    {
        std::cout << "没有找到匹配的资源。\n";
        return;
    }
    std::cout << "共找到 " << result.size() << " 条：\n";
    for (std::size_t i = 0; i < result.size(); ++i)
        std::cout << i + 1 << ". " << *result[i] << "\n";
}

void RecordsFlow(Library& library)
{
    const std::string readerId = ReadText("读者编号（直接回车查看全部）：");
    library.Loans().ShowRecords(readerId);
}

void AddReaderFlow(Library& library)
{
    std::cout << "\n1-学生  2-教师\n";
    const int type = ReadInt("读者类型：");
    if (type == 1)
    {
        const std::string id = ReadText("学号：");
        const std::string name = ReadText("姓名：");
        const std::string major = ReadText("院系：");
        library.Readers().AddStudent(id, name, major);
    }
    else if (type == 2)
    {
        const std::string id = ReadText("工号：");
        const std::string name = ReadText("姓名：");
        const std::string department = ReadText("院系：");
        const std::string title = ReadText("职称：");
        library.Readers().AddTeacher(id, name, department, title);
    }
    else
    {
        std::cout << "读者类型无效。\n";
    }
}

void DeleteReaderFlow(Library& library)
{
    library.Readers().ShowAll();
    const std::string id = ReadText("要删除的读者编号：");
    if (library.Loans().HasActiveLoan(id))
        std::cout << "该读者还有未归还资源，不能删除。\n";
    else
        library.Readers().Delete(id);
}

void DeleteResourceFlow(Library& library)
{
    const std::string id = ReadText("资源编号：");
    if (library.Loans().HasActiveLoanForResource(id))
        std::cout << "该资源尚有未归还记录，不能删除。\n";
    else
        library.Resources().Delete(id);
}

void FineFlow(Library& library)
{
    std::cout << "\n1-开具罚款单  2-查看罚款单  3-缴纳罚款  0-返回\n";
    const int choice = ReadInt("请选择：");
    if (choice == 1)
    {
        const std::string readerId = ReadText("读者编号：");
        const std::string resourceId = ReadText("资源编号（直接回车表示不关联资源）：");
        const std::string reason = ReadText("罚款原因：");
        const double amount = ReadDouble("罚款金额（元）：");
        library.Fines().IssueFine(readerId, resourceId, reason, amount);
    }
    else if (choice == 2)
        library.Fines().ShowAll();
    else if (choice == 3)
        library.Fines().Pay(ReadText("罚款单号："));
    else if (choice != 0)
        std::cout << "没有该选项。\n";
}
} // namespace

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Library library;
    Account auth;

    while (!std::cin.eof())
    {
        if (!auth.IsLoggedIn())
        {
            if (!LoginFlow(auth))
                break;
            continue;
        }

        ShowMainMenu(auth);
        const int choice = ReadInt("请选择功能：");
        if (std::cin.eof())
            break;

        if (choice == 0)
            break;
        else if (choice == 1)
            AddResourceFlow(library);
        else if (choice == 2)
            AddStockFlow(library);
        else if (choice == 3)
            library.Resources().ShowOne(ReadText("资源编号："));
        else if (choice == 4)
            library.Resources().ShowAll();
        else if (choice == 5)
            ReduceStockFlow(library);
        else if (choice == 6)
            DeleteResourceFlow(library);
        else if (choice == 7)
            BorrowFlow(library);
        else if (choice == 8)
            ReturnFlow(library);
        else if (choice == 9)
            ModifyFlow(library);
        else if (choice == 10)
            SearchFlow(library);
        else if (choice == 11)
            RecordsFlow(library);
        else if (choice == 12)
            library.ShowStatistics();
        else if (choice == 13)
            AddReaderFlow(library);
        else if (choice == 14)
            DeleteReaderFlow(library);
        else if (choice == 15)
            FineFlow(library);
        else if (choice == 16)
            library.Loans().ShowRanking();
        else
            std::cout << "没有该选项。\n";
    }

    std::cout << "感谢使用，再见！\n";
    return 0;
}
