#pragma once
#include <ctime>
#include <iostream>
#include <string>

// 借阅记录建立资源与读者之间的关联，并保存借出、应还、归还时间。
class BorrowRecord
{
    std::string resourceId;
    std::string resourceName;
    std::string resourceType;
    std::string readerId;
    std::string readerName;
    std::string readerType;
    std::time_t borrowTime;
    std::time_t dueTime;
    std::time_t returnTime;
    bool returned;

public:
    BorrowRecord(const std::string& resourceId, const std::string& resourceName,
                 const std::string& resourceType,
                 const std::string& readerId, const std::string& readerName,
                 const std::string& readerType, int loanDays);

    std::string GetResourceId() const;
    std::string GetReaderId() const;
    std::string GetBorrowDateText() const;
    std::string GetDueDateText() const;
    std::string GetReturnDateText() const;
    bool IsReturned() const;
    void MarkReturned();

    void Show(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const BorrowRecord& record);
