#pragma execution_character_set("utf-8")
#include "FineBill.h"
#include "BorrowDate.h"

#include <iomanip>
#include <sstream>

FineBill::FineBill(const std::string& billId,
                   const std::string& readerId, const std::string& readerName,
                   const std::string& resourceId, const std::string& resourceName,
                   const std::string& reason, double amount)
    : billId(billId),
      readerId(readerId),
      readerName(readerName),
      resourceId(resourceId),
      resourceName(resourceName),
      reason(reason),
      amount(amount > 0.0 ? amount : 0.0),
      billTime(std::time(nullptr)),
      paid(false)
{
}

std::string FineBill::GetBillId() const
{
    return billId;
}

std::string FineBill::GetReaderId() const
{
    return readerId;
}

std::string FineBill::GetBillDateText() const
{
    return FormatDate(billTime);
}

double FineBill::GetAmount() const
{
    return amount;
}

bool FineBill::IsPaid() const
{
    return paid;
}

void FineBill::MarkPaid()
{
    paid = true;
}

void FineBill::Show(std::ostream& os) const
{
    std::ostringstream money;
    money << std::fixed << std::setprecision(2) << amount;

    os << "单号:" << billId << " 日期:" << GetBillDateText()
       << " 读者:" << readerId << " " << readerName;
    if (!resourceId.empty())
        os << " 资源:" << resourceId << "《" << resourceName << "》";
    os << " 原因:" << reason << " 金额:" << money.str() << "元 状态:"
       << (paid ? "已缴纳" : "未缴纳");
}

std::ostream& operator<<(std::ostream& os, const FineBill& bill)
{
    bill.Show(os);
    return os;
}
