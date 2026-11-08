#pragma execution_character_set("utf-8")
#include "Library.h"

#include "PhysicalResource.h"

#include <iostream>

Library::Library()
    : loanService(resourceCatalog, readerRegistry),
      fineService(resourceCatalog, readerRegistry)
{
}

ResourceCatalog& Library::Resources()
{
    return resourceCatalog;
}

ReaderRegistry& Library::Readers()
{
    return readerRegistry;
}

LoanService& Library::Loans()
{
    return loanService;
}

FineService& Library::Fines()
{
    return fineService;
}

void Library::ShowStatistics() const
{
    int physicalTitles = 0;
    int currentStock = 0;
    int digitalTitles = 0;

    const auto& resources = resourceCatalog.All();
    for (std::size_t i = 0; i < resources.size(); ++i)
    {
        if (resources[i]->IsDigital())
        {
            ++digitalTitles;
        }
        else
        {
            const PhysicalResource* physical =
                dynamic_cast<const PhysicalResource*>(resources[i]);
            if (physical != nullptr)
            {
                ++physicalTitles;
                currentStock += physical->GetStock();
            }
        }
    }

    int students = 0;
    int teachers = 0;
    const auto& readers = readerRegistry.All();
    for (std::size_t i = 0; i < readers.size(); ++i)
    {
        if (readers[i]->Type() == "学生")
            ++students;
        else
            ++teachers;
    }

    int activePaper = 0;
    int activeDigital = 0;
    const auto& records = loanService.Records();
    for (std::size_t i = 0; i < records.size(); ++i)
    {
        if (records[i].IsReturned())
            continue;
        const Resource* resource = resourceCatalog.Find(records[i].GetResourceId());
        if (resource != nullptr && resource->IsDigital())
            ++activeDigital;
        else
            ++activePaper;
    }

    std::cout << "\n资源种数：" << resources.size() << "\n"
              << "纸质资源：" << physicalTitles << " 种，可借库存 "
              << currentStock << " 册，借出 " << activePaper << " 册\n"
              << "电子资源：" << digitalTitles << " 种，借阅中 "
              << activeDigital << " 项（不占库存）\n"
              << "读者人数：" << readers.size() << " 人（学生 " << students
              << "，教师 " << teachers << "）\n"
              << "当前借阅：" << activePaper + activeDigital << " 项\n";
}
