#pragma once
#include "Resource.h"

// 电子资源：无库存，可多人同时借阅。
class ES : public Resource
{
    std::string format;
    double sizeMB;

public:
    ES(const std::string& id, const std::string& name,
       const std::string& format, double sizeMB);

    std::string Type() const override;
    bool IsDigital() const override;
    bool CanBorrow() const override;
    void OnBorrow() override;
    void OnReturn() override;
    std::string BorrowMessage() const override;
    void Show() const override;
};
