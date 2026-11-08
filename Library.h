#pragma once
#include "FineService.h"
#include "LoanService.h"
#include "ReaderRegistry.h"
#include "ResourceCatalog.h"

// Library 只作为组合根，把资源、读者、借阅、罚款四个职责组织起来。
class Library
{
    ResourceCatalog resourceCatalog;
    ReaderRegistry readerRegistry;
    LoanService loanService;
    FineService fineService;

public:
    Library();

    ResourceCatalog& Resources();
    ReaderRegistry& Readers();
    LoanService& Loans();
    FineService& Fines();

    void ShowStatistics() const;
};
