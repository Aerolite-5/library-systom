#pragma once
#include <iostream>
#include <string>

// 读者抽象基类：借阅上限和借期由具体读者类型决定。
class Reader
{
protected:
    std::string id;
    std::string name;

public:
    Reader(const std::string& id, const std::string& name);
    virtual ~Reader() = default;

    std::string GetId() const;
    std::string GetName() const;

    virtual std::string Type() const = 0;
    virtual int GetMaxBorrowCount() const = 0;
    virtual int GetLoanDays() const = 0;
    virtual void Show(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Reader& reader);
