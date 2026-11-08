#pragma once
#include "PhysicalResource.h"

class Magazine : public PhysicalResource
{
    std::string issue;

public:
    Magazine(const std::string& id, const std::string& name,
             const std::string& category, const std::string& issue, int stock);

    std::string GetIssue() const;

    std::string Type() const override;
    void Show(std::ostream& os) const override;
};
