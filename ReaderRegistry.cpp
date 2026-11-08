#pragma execution_character_set("utf-8")
#include "ReaderRegistry.h"

#include "Student.h"
#include "Teacher.h"

#include <iostream>

ReaderRegistry::ReaderRegistry()
{
    readers.push_back(new Student("5120250001", "胡鑫", "计算机学院"));
    readers.push_back(new Student("5120250002", "高斌", "文学院"));
    readers.push_back(new Student("5120256423", "张想", "历史学院"));
    readers.push_back(new Teacher("T2025001", "李文", "计算机学院", "副教授"));
}

ReaderRegistry::~ReaderRegistry()
{
    for (std::size_t i = 0; i < readers.size(); ++i)
        delete readers[i];
}

bool ReaderRegistry::AddStudent(const std::string& id, const std::string& name,
                                const std::string& major)
{
    if (id.empty() || name.empty())
    {
        std::cout << "学号和姓名不能为空。\n";
        return false;
    }
    if (Find(id) != nullptr)
    {
        std::cout << "读者编号已存在。\n";
        return false;
    }
    readers.push_back(new Student(id, name, major));
    std::cout << "添加学生成功。\n";
    return true;
}

bool ReaderRegistry::AddTeacher(const std::string& id, const std::string& name,
                                const std::string& department, const std::string& title)
{
    if (id.empty() || name.empty())
    {
        std::cout << "工号和姓名不能为空。\n";
        return false;
    }
    if (Find(id) != nullptr)
    {
        std::cout << "读者编号已存在。\n";
        return false;
    }
    readers.push_back(new Teacher(id, name, department, title));
    std::cout << "添加教师成功。\n";
    return true;
}

bool ReaderRegistry::Delete(const std::string& id)
{
    for (std::size_t i = 0; i < readers.size(); ++i)
    {
        if (readers[i]->GetId() != id)
            continue;
        delete readers[i];
        readers.erase(readers.begin() + static_cast<std::ptrdiff_t>(i));
        std::cout << "删除读者成功。\n";
        return true;
    }
    std::cout << "未找到该读者。\n";
    return false;
}

void ReaderRegistry::ShowAll() const
{
    if (readers.empty())
    {
        std::cout << "暂无读者。\n";
        return;
    }
    for (std::size_t i = 0; i < readers.size(); ++i)
        std::cout << i + 1 << ". " << *readers[i]
                  << " 借期:" << readers[i]->GetLoanDays() << "天\n";
}

Reader* ReaderRegistry::Find(const std::string& id)
{
    for (std::size_t i = 0; i < readers.size(); ++i)
    {
        if (readers[i]->GetId() == id)
            return readers[i];
    }
    return nullptr;
}

const Reader* ReaderRegistry::Find(const std::string& id) const
{
    for (std::size_t i = 0; i < readers.size(); ++i)
    {
        if (readers[i]->GetId() == id)
            return readers[i];
    }
    return nullptr;
}

const Repository<Reader*>& ReaderRegistry::All() const
{
    return readers;
}
