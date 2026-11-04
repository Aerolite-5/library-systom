#pragma once
#include <iostream>
#include <string>

// 读者暂不派生，只保留一个类，便于把实验三重点放在资源继承上。
class Reader
{
    std::string id;
    std::string name;
    std::string role;
    int maxBorrow;

public:
    Reader(const std::string& id, const std::string& name,
           const std::string& role);

    std::string GetId() const;
    std::string GetName() const;
    int GetMaxBorrow() const;

    void Show() const;
};
