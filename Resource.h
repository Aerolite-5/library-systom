#pragma once
#include <iostream>
#include <string>

// 资源抽象基类：不同资源用不同方式实现借阅和库存处理。
class Resource
{
protected:
    std::string id;
    std::string name;
    std::string category;

public:
    Resource(const std::string& id, const std::string& name,
             const std::string& category);
    virtual ~Resource() = default;

    std::string GetId() const;
    std::string GetName() const;
    std::string GetCategory() const;

    void SetName(const std::string& value);
    void SetCategory(const std::string& value);

    virtual std::string Type() const = 0;
    virtual bool IsDigital() const = 0;

    virtual bool CanBorrow(std::string& reason) const = 0;
    virtual bool OnBorrow() = 0;
    virtual void OnReturn() = 0;

    virtual void Show(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Resource& resource);
