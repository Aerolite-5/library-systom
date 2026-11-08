#pragma once
#include "Resource.h"

// 电子书没有库存限制，可以多人同时借阅。
class ES : public Resource
{
    std::string format;
    double sizeMB;

public:
    ES(const std::string& id, const std::string& name,
       const std::string& category, const std::string& format,
       double sizeMB);

    std::string GetFormat() const;
    double GetSizeMB() const;
    std::string Type() const override;

    bool IsDigital() const override;
    bool CanBorrow(std::string& reason) const override;
    bool OnBorrow() override;
    void OnReturn() override;

    void Show(std::ostream& os) const override;
};
