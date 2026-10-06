#ifndef BOOK_H
#define BOOK_H
#include <string>

class Book
{
private:
    std::string id;     
    std::string name;   
    bool isBorrowed;    
public:
    Book(std::string id, std::string name);

    std::string GetId() const;
    std::string GetName() const;
    bool IsBorrowed() const;

    bool Borrow();  
    bool Return();  
};

#endif
