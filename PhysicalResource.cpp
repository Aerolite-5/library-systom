#pragma execution_character_set("utf-8")
#include "PhysicalResource.h"

PhysicalResource::PhysicalResource(const std::string& id, const std::string& name,
                                   const std::string& category, int stock)
    : Resource(id, name, category), stock(stock > 0 ? stock : 0)
{
}

bool PhysicalResource::IsDigital() const
{
    return false;
}

bool PhysicalResource::CanBorrow(std::string& reason) const
{
    if (stock <= 0)
    {
        reason = "该资源已没有可借库存。";
        return false;
    }
    return true;
}

bool PhysicalResource::OnBorrow()
{
    if (stock <= 0)
        return false;
    --stock;
    return true;
}

void PhysicalResource::OnReturn()
{
    ++stock;
}

bool PhysicalResource::AddStock(int count, std::string& reason)
{
    if (count <= 0)
    {
        reason = "数量必须大于 0。";
        return false;
    }
    stock += count;
    reason.clear();
    return true;
}

bool PhysicalResource::ReduceStock(int count, std::string& reason)
{
    if (count <= 0)
    {
        reason = "数量必须大于 0。";
        return false;
    }
    if (count > stock)
    {
        reason = "减少数量不能超过当前库存。";
        return false;
    }
    stock -= count;
    reason.clear();
    return true;
}

int PhysicalResource::GetStock() const
{
    return stock;
}

void PhysicalResource::ShowStock(std::ostream& os) const
{
    os << " 库存:" << stock;
}
