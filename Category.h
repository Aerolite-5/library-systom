#pragma once
#include <iostream>
#include <string>

class Category
{
    std::string id;
    std::string name;

public:
    Category(const std::string& id = "", const std::string& name = "");

    std::string GetId() const;
    std::string GetName() const;

    void Show(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Category& category);
