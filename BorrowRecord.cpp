#pragma execution_character_set("utf-8")
#include "BorrowRecord.h"
#include "BorrowDate.h"

BorrowRecord::BorrowRecord(const std::string& resourceId,
                           const std::string& resourceName,
                           const std::string& resourceType,
                           const std::string& readerId,
                           const std::string& readerName,
                           const std::string& readerType, int loanDays)
    : resourceId(resourceId),
      resourceName(resourceName),
      resourceType(resourceType),
      readerId(readerId),
      readerName(readerName),
      readerType(readerType),
      borrowTime(std::time(nullptr)),
      dueTime(borrowTime + static_cast<std::time_t>(loanDays) * 24 * 60 * 60),
      returnTime(0),
      returned(false)
{
}

std::string BorrowRecord::GetResourceId() const
{
    return resourceId;
}

std::string BorrowRecord::GetReaderId() const
{
    return readerId;
}

std::string BorrowRecord::GetBorrowDateText() const
{
    return FormatDate(borrowTime);
}

std::string BorrowRecord::GetDueDateText() const
{
    return FormatDate(dueTime);
}

std::string BorrowRecord::GetReturnDateText() const
{
    return returned ? FormatDate(returnTime) : "-";
}

bool BorrowRecord::IsReturned() const
{
    return returned;
}

void BorrowRecord::MarkReturned()
{
    returned = true;
    returnTime = std::time(nullptr);
}

void BorrowRecord::Show(std::ostream& os) const
{
    os << "资源:" << resourceId << "《" << resourceName << "》"
       << " 类型:" << resourceType
       << " 读者:" << readerId << " " << readerName
       << "[" << readerType << "]"
       << " 借出:" << GetBorrowDateText()
       << " 应还:" << GetDueDateText();
    if (returned)
        os << " 归还:" << GetReturnDateText();
    os << " 状态:";
    if (returned)
        os << "已归还";
    else if (std::time(nullptr) > dueTime)
        os << "已逾期";
    else
        os << "借阅中";
}

std::ostream& operator<<(std::ostream& os, const BorrowRecord& record)
{
    record.Show(os);
    return os;
}
