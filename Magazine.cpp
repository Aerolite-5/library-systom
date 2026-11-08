#pragma execution_character_set("utf-8")
#include "Magazine.h"

Magazine::Magazine(const std::string& id, const std::string& name,
                   const std::string& category, const std::string& issue, int stock)
    : PhysicalResource(id, name, category, stock), issue(issue)
{
}

std::string Magazine::GetIssue() const
{
    return issue;
}

std::string Magazine::Type() const
{
    return "杂志";
}

void Magazine::Show(std::ostream& os) const
{
    os << "[" << Type() << "] 编号:" << GetId()
       << " 名称:" << GetName()
       << " 分类:" << GetCategory();
    ShowStock(os);
    os << " 期号:" << issue;
}
