#pragma execution_character_set("utf-8")
#include "ES.h"

#include <iomanip>
#include <iostream>

ES::ES(const std::string& id, const std::string& name,
       const std::string& format, double sizeMB)
    : Resource(id, name), format(format), sizeMB(sizeMB > 0.0 ? sizeMB : 0.0)
{
}

std::string ES::Type() const
{
    return "电子资源";
}

bool ES::IsDigital() const
{
    return true;
}

bool ES::CanBorrow() const
{
    return true;
}

void ES::OnBorrow()
{
}

void ES::OnReturn()
{
}

std::string ES::BorrowMessage() const
{
    return "借阅成功，电子资源可以多人同时借阅。";
}

void ES::Show() const
{
    std::cout << "[电子资源] 编号:" << id << " 名称:" << name
              << " 格式:" << format
              << " 大小:" << std::fixed << std::setprecision(1) << sizeMB
              << "MB 可多人同时借阅\n";
}
