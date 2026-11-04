#pragma once
#include <string>
#include <vector>

#include "BorrowRecord.h"
#include "Reader.h"
#include "Resource.h"

class Library
{
    std::vector<Resource*> resources;
    std::vector<Reader> readers;
    std::vector<BorrowRecord> records;

    Resource* FindResource(const std::string& id);
    Reader* FindReader(const std::string& id);
    int CountActiveLoans(const std::string& readerId) const;

public:
    Library();
    ~Library();

    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

    bool AddBook(const std::string& id, const std::string& name,
                 int stock, const std::string& author);
    bool AddEBook(const std::string& id, const std::string& name, double sizeMB);

    bool Borrow(const std::string& resourceId, const std::string& readerId);
    bool Return(const std::string& resourceId, const std::string& readerId);

    void ShowResources() const;
    void ShowReaders() const;
    void ShowRecords() const;
};
