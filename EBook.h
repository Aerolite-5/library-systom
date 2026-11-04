#pragma once
#include "Resource.h"

// 电子书：没有库存，可以多人同时借阅。
class EBook : public Resource
{
    double sizeMB;

public:
    EBook(const std::string& id, const std::string& name, double sizeMB);

    std::string Type() const override;
    bool CanBorrow() const override;
    void OnBorrow() override;
    void OnReturn() override;
    void Show() const override;
};
