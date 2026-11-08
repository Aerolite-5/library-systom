#pragma once
#include <ctime>
#include <iostream>
#include <string>

class FineBill
{
    std::string billId;
    std::string readerId;
    std::string readerName;
    std::string resourceId;
    std::string resourceName;
    std::string reason;
    double amount;
    std::time_t billTime;
    bool paid;

public:
    FineBill(const std::string& billId,
             const std::string& readerId, const std::string& readerName,
             const std::string& resourceId, const std::string& resourceName,
             const std::string& reason, double amount);

    std::string GetBillId() const;
    std::string GetReaderId() const;
    std::string GetBillDateText() const;
    double GetAmount() const;
    bool IsPaid() const;
    void MarkPaid();

    void Show(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const FineBill& bill);
