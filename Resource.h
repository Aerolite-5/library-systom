#pragma once
#include <iostream>
#include <string>

// 资源基类：Book 和 EBook 继承它并实现虚函数。
class Resource
{
protected:
    std::string id;
    std::string name;

public:
    Resource(const std::string& id, const std::string& name);
    virtual ~Resource() = default;

    std::string GetId() const;
    std::string GetName() const;

    virtual std::string Type() const = 0;
    virtual bool CanBorrow() const = 0;
    virtual void OnBorrow() = 0;
    virtual void OnReturn() = 0;
    virtual void Show() const = 0;
};
