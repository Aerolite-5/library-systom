#pragma once
#include <iostream>
#include <string>

// 实验四：读者也做成抽象基类，学生和教师通过派生类实现不同借阅规则。
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
    virtual int GetMaxBorrow() const = 0;
    virtual int GetLoanDays() const = 0;
    virtual void Show() const = 0;
};
