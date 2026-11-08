#pragma once
#include "PhysicalResource.h"

class Book : public PhysicalResource
{
    std::string author;
    std::string publisher;

public:
    Book(const std::string& id, const std::string& name,
         const std::string& category, const std::string& author,
         const std::string& publisher, int stock);

    std::string GetAuthor() const;
    std::string GetPublisher() const;

    std::string Type() const override;
    void Show(std::ostream& os) const override;
};
