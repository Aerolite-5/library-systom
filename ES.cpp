#pragma execution_character_set("utf-8")
#include "ES.h"

#include <iomanip>
#include <sstream>

ES::ES(const std::string& id, const std::string& name,
       const std::string& category, const std::string& format,
       double sizeMB)
    : Resource(id, name, category),
      format(format),
      sizeMB(sizeMB > 0.0 ? sizeMB : 0.0)
{
}

std::string ES::GetFormat() const
{
    return format;
}

double ES::GetSizeMB() const
{
    return sizeMB;
}

std::string ES::Type() const
{
    return "电子资源";
}

bool ES::IsDigital() const
{
    return true;
}

bool ES::CanBorrow(std::string& reason) const
{
    reason.clear();
    return true;
}

bool ES::OnBorrow()
{
    return true;
}

void ES::OnReturn()
{
}

void ES::Show(std::ostream& os) const
{
    std::ostringstream sizeText;
    sizeText << std::fixed << std::setprecision(1) << sizeMB;

    os << "[" << Type() << "] 编号:" << GetId()
       << " 名称:" << GetName()
       << " 分类:" << GetCategory()
       << " 格式:" << format
       << " 大小:" << sizeText.str() << "MB"
       << " 可多人同时借阅";
}
