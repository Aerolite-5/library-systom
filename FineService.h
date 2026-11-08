#pragma once
#include <string>
#include <vector>

#include "FineBill.h"
#include "Repository.h"

class ResourceCatalog;
class ReaderRegistry;

// 罚款服务：只处理罚款单开具、查询和缴纳。
class FineService
{
    ResourceCatalog& resources;
    ReaderRegistry& readers;
    Repository<FineBill> fines;
    int nextFineNumber;

public:
    FineService(ResourceCatalog& resources, ReaderRegistry& readers);

    bool IssueFine(const std::string& readerId, const std::string& resourceId,
                   const std::string& reason, double amount);
    void ShowAll() const;
    bool Pay(const std::string& billId);
};
