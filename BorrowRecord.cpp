#pragma execution_character_set("utf-8")
#include "BorrowRecord.h"

#include <iostream>

BorrowRecord::BorrowRecord(const std::string& resourceId,
                           const std::string& resourceName,
                           const std::string& readerId,
                           const std::string& readerName)
    : resourceId(resourceId), resourceName(resourceName),
      readerId(readerId), readerName(readerName), returned(false)
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

bool BorrowRecord::IsReturned() const
{
    return returned;
}

void BorrowRecord::MarkReturned()
{
    returned = true;
}

void BorrowRecord::Show() const
{
    std::cout << "资源:" << resourceId << "《" << resourceName << "》"
              << " 读者:" << readerId << " " << readerName
              << " 状态:" << (returned ? "已归还" : "借阅中") << "\n";
}
