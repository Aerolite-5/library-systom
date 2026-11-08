#pragma execution_character_set("utf-8")
#include "FineService.h"

#include "ReaderRegistry.h"
#include "ResourceCatalog.h"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace
{
std::string Money(double amount)
{
    std::ostringstream text;
    text << std::fixed << std::setprecision(2) << amount;
    return text.str();
}
} // namespace

FineService::FineService(ResourceCatalog& resources, ReaderRegistry& readers)
    : resources(resources), readers(readers), nextFineNumber(1)
{
}

bool FineService::IssueFine(const std::string& readerId, const std::string& resourceId,
                            const std::string& reason, double amount)
{
    Reader* reader = readers.Find(readerId);
    if (reader == nullptr)
    {
        std::cout << "未找到读者。\n";
        return false;
    }
    if (amount <= 0.0)
    {
        std::cout << "罚款金额必须大于 0。\n";
        return false;
    }

    std::string resourceName;
    if (!resourceId.empty())
    {
        const Resource* resource = resources.Find(resourceId);
        if (resource == nullptr)
        {
            std::cout << "未找到资源。\n";
            return false;
        }
        resourceName = resource->GetName();
    }

    std::ostringstream number;
    number << "F" << std::setw(4) << std::setfill('0') << nextFineNumber++;
    fines.push_back(FineBill(number.str(), reader->GetId(), reader->GetName(),
                             resourceId, resourceName, reason, amount));

    std::cout << "罚款单已开具，单号 " << number.str()
              << "，金额 " << Money(amount) << " 元。\n";
    return true;
}

void FineService::ShowAll() const
{
    if (fines.empty())
    {
        std::cout << "暂无罚款单。\n";
        return;
    }

    double unpaid = 0.0;
    double paid = 0.0;
    for (std::size_t i = 0; i < fines.size(); ++i)
    {
        std::cout << i + 1 << ". " << fines[i] << "\n";
        if (fines[i].IsPaid())
            paid += fines[i].GetAmount();
        else
            unpaid += fines[i].GetAmount();
    }

    std::cout << "未缴纳合计：" << Money(unpaid)
              << " 元，已缴纳合计：" << Money(paid) << " 元\n";
}

bool FineService::Pay(const std::string& billId)
{
    for (std::size_t i = 0; i < fines.size(); ++i)
    {
        if (fines[i].GetBillId() != billId)
            continue;
        if (fines[i].IsPaid())
        {
            std::cout << "该罚款单已缴纳。\n";
            return false;
        }
        fines[i].MarkPaid();
        std::cout << "缴纳成功，金额 " << Money(fines[i].GetAmount()) << " 元。\n";
        return true;
    }
    std::cout << "未找到该罚款单。\n";
    return false;
}
