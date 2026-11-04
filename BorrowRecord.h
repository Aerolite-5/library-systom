#pragma once
#include <iostream>
#include <string>

class BorrowRecord
{
    std::string resourceId;
    std::string resourceName;
    std::string readerId;
    std::string readerName;
    bool returned;

public:
    BorrowRecord(const std::string& resourceId, const std::string& resourceName,
                 const std::string& readerId, const std::string& readerName);

    std::string GetResourceId() const;
    std::string GetReaderId() const;
    bool IsReturned() const;
    void MarkReturned();

    void Show() const;
};
