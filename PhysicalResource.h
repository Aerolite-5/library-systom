#pragma once
#include "Resource.h"

// 纸质资源有库存：借出减 1，归还加 1。
class PhysicalResource : public Resource
{
    int stock;

protected:
    void ShowStock(std::ostream& os) const;

public:
    PhysicalResource(const std::string& id, const std::string& name,
                     const std::string& category, int stock);

    bool IsDigital() const override;

    bool CanBorrow(std::string& reason) const override;
    bool OnBorrow() override;
    void OnReturn() override;
    bool AddStock(int count, std::string& reason);
    bool ReduceStock(int count, std::string& reason);

    int GetStock() const;
};
