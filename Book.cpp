#include "Book.h"

Book::Book(std::string id, std::string name)
{
    this->id = id;
    this->name = name;
    isBorrowed = false;
}

std::string Book::GetId() const
{
    return id;
}

std::string Book::GetName() const
{
    return name;
}

bool Book::IsBorrowed() const
{
    return isBorrowed;
}

bool Book::Borrow()
{
    if (isBorrowed)
        return false;
    isBorrowed = true;
    return true;
}

bool Book::Return()
{
    if (!isBorrowed)
        return false;
    isBorrowed = false;
    return true;
}
