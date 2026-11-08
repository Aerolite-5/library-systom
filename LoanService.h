#pragma once
#include <string>
#include <vector>

#include "BorrowRecord.h"
#include "Repository.h"

class ResourceCatalog;
class ReaderRegistry;

// 借阅服务：只处理借书、还书、借阅记录和借阅热度。
class LoanService
{
    ResourceCatalog& resources;
    ReaderRegistry& readers;
    Repository<BorrowRecord> records;

    int CountActiveLoans(const std::string& readerId) const;

public:
    LoanService(ResourceCatalog& resources, ReaderRegistry& readers);

    bool Borrow(const std::string& resourceId, const std::string& readerId);
    bool Return(const std::string& resourceId, const std::string& readerId);

    void ShowRecords(const std::string& readerId = "") const;
    void ShowRanking() const;

    bool HasActiveLoan(const std::string& readerId) const;
    bool HasActiveLoanForResource(const std::string& resourceId) const;
    const Repository<BorrowRecord>& Records() const;
};
