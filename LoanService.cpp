#pragma execution_character_set("utf-8")
#include "LoanService.h"

#include "PhysicalResource.h"
#include "ReaderRegistry.h"
#include "ResourceCatalog.h"

#include <algorithm>
#include <iostream>
#include <utility>

LoanService::LoanService(ResourceCatalog& resources, ReaderRegistry& readers)
    : resources(resources), readers(readers)
{
}

int LoanService::CountActiveLoans(const std::string& readerId) const
{
    int count = 0;
    for (std::size_t i = 0; i < records.size(); ++i)
    {
        if (!records[i].IsReturned() && records[i].GetReaderId() == readerId)
            ++count;
    }
    return count;
}

bool LoanService::Borrow(const std::string& resourceId, const std::string& readerId)
{
    Resource* resource = resources.Find(resourceId);
    if (resource == nullptr)
    {
        std::cout << "未找到资源。\n";
        return false;
    }

    Reader* reader = readers.Find(readerId);
    if (reader == nullptr)
    {
        std::cout << "未找到读者。\n";
        return false;
    }

    if (CountActiveLoans(readerId) >= reader->GetMaxBorrowCount())
    {
        std::cout << "该读者同时借阅已达上限（"
                  << reader->GetMaxBorrowCount() << " 项）。\n";
        return false;
    }

    for (std::size_t i = 0; i < records.size(); ++i)
    {
        if (!records[i].IsReturned()
            && records[i].GetResourceId() == resourceId
            && records[i].GetReaderId() == readerId)
        {
            std::cout << "该读者已借阅该资源且未归还。\n";
            return false;
        }
    }

    std::string reason;
    if (!resource->CanBorrow(reason))
    {
        std::cout << reason << "\n";
        return false;
    }
    if (!resource->OnBorrow())
    {
        std::cout << "借阅失败。\n";
        return false;
    }

    records.push_back(BorrowRecord(resource->GetId(), resource->GetName(),
                                   resource->Type(), reader->GetId(),
                                   reader->GetName(), reader->Type(),
                                   reader->GetLoanDays()));

    PhysicalResource* physical = dynamic_cast<PhysicalResource*>(resource);
    if (physical != nullptr)
        std::cout << "借阅成功，当前库存 " << physical->GetStock() << "。\n";
    else
        std::cout << "借阅成功，电子书可以多人同时借阅。\n";
    return true;
}

bool LoanService::Return(const std::string& resourceId, const std::string& readerId)
{
    for (std::size_t i = records.size(); i > 0; --i)
    {
        BorrowRecord& record = records[i - 1];
        if (record.IsReturned() || record.GetResourceId() != resourceId
            || record.GetReaderId() != readerId)
        {
            continue;
        }

        Resource* resource = resources.Find(resourceId);
        if (resource == nullptr)
        {
            std::cout << "记录对应的资源已不存在，无法完成归还。\n";
            return false;
        }

        resource->OnReturn();
        record.MarkReturned();

        PhysicalResource* physical = dynamic_cast<PhysicalResource*>(resource);
        if (physical != nullptr)
            std::cout << "归还成功，当前库存 " << physical->GetStock() << "。\n";
        else
            std::cout << "归还成功。\n";
        return true;
    }

    std::cout << "未找到该读者的未归还记录。\n";
    return false;
}

void LoanService::ShowRecords(const std::string& readerId) const
{
    int index = 1;
    bool found = false;
    for (std::size_t i = 0; i < records.size(); ++i)
    {
        if (!readerId.empty() && records[i].GetReaderId() != readerId)
            continue;
        std::cout << index++ << ". " << records[i] << "\n";
        found = true;
    }
    if (!found)
        std::cout << "暂无借阅记录。\n";
}

void LoanService::ShowRanking() const
{
    if (records.empty())
    {
        std::cout << "暂无借阅记录。\n";
        return;
    }

    std::vector<std::pair<std::string, int>> ranking;
    for (std::size_t i = 0; i < records.size(); ++i)
    {
        const std::string id = records[i].GetResourceId();
        bool found = false;
        for (std::size_t j = 0; j < ranking.size(); ++j)
        {
            if (ranking[j].first == id)
            {
                ++ranking[j].second;
                found = true;
                break;
            }
        }
        if (!found)
            ranking.push_back(std::make_pair(id, 1));
    }

    std::sort(ranking.begin(), ranking.end(),
              [](const std::pair<std::string, int>& left,
                 const std::pair<std::string, int>& right)
              {
                  if (left.second != right.second)
                      return left.second > right.second;
                  return left.first < right.first;
              });

    std::cout << "\n借阅总次数：" << records.size() << " 次\n";
    for (std::size_t i = 0; i < ranking.size(); ++i)
    {
        const Resource* resource = resources.Find(ranking[i].first);
        std::cout << i + 1 << ". " << ranking[i].first << " 《"
                  << (resource != nullptr ? resource->GetName() : "已删除资源")
                  << "》 借阅 " << ranking[i].second << " 次";
        if (resource != nullptr)
            std::cout << "（" << resource->Type() << "）";
        std::cout << "\n";
    }
}

bool LoanService::HasActiveLoan(const std::string& readerId) const
{
    for (std::size_t i = 0; i < records.size(); ++i)
    {
        if (!records[i].IsReturned() && records[i].GetReaderId() == readerId)
            return true;
    }
    return false;
}

bool LoanService::HasActiveLoanForResource(const std::string& resourceId) const
{
    for (std::size_t i = 0; i < records.size(); ++i)
    {
        if (!records[i].IsReturned() && records[i].GetResourceId() == resourceId)
            return true;
    }
    return false;
}

const Repository<BorrowRecord>& LoanService::Records() const
{
    return records;
}
