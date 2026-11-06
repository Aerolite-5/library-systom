#pragma execution_character_set("utf-8")
#include "Library.h"

#include "Book.h"
#include "ES.h"
#include "Magazine.h"
#include "Student.h"
#include "Teacher.h"

#include <iostream>

Library::Library()
{
    readers.push_back(new Student("5120250001", "胡鑫", "计算机学院"));
    readers.push_back(new Student("5120250002", "高斌", "文学院"));
    readers.push_back(new Student("5120256423", "张想", "历史学院"));
    readers.push_back(new Teacher("T2025001", "李文", "计算机学院", "副教授"));
}

Library::~Library()
{
    for (std::size_t i = 0; i < resources.size(); ++i)
        delete resources[i];
    for (std::size_t i = 0; i < readers.size(); ++i)
        delete readers[i];
}

Resource* Library::FindResource(const std::string& id)
{
    for (std::size_t i = 0; i < resources.size(); ++i)
    {
        if (resources[i]->GetId() == id)
            return resources[i];
    }
    return nullptr;
}

Reader* Library::FindReader(const std::string& id)
{
    for (std::size_t i = 0; i < readers.size(); ++i)
    {
        if (readers[i]->GetId() == id)
            return readers[i];
    }
    return nullptr;
}

int Library::CountActiveLoans(const std::string& readerId) const
{
    int count = 0;
    for (std::size_t i = 0; i < records.size(); ++i)
    {
        if (!records[i].IsReturned() && records[i].GetReaderId() == readerId)
            ++count;
    }
    return count;
}

bool Library::AddBook(const std::string& id, const std::string& name, int stock,
                      const std::string& author, const std::string& publisher)
{
    if (FindResource(id) != nullptr || stock <= 0)
    {
        std::cout << "编号重复或库存无效。\n";
        return false;
    }
    resources.push_back(new Book(id, name, stock, author, publisher));
    std::cout << "添加图书成功。\n";
    return true;
}

bool Library::AddMagazine(const std::string& id, const std::string& name, int stock,
                          const std::string& issue)
{
    if (FindResource(id) != nullptr || stock <= 0)
    {
        std::cout << "编号重复或库存无效。\n";
        return false;
    }
    resources.push_back(new Magazine(id, name, stock, issue));
    std::cout << "添加杂志成功。\n";
    return true;
}

bool Library::AddES(const std::string& id, const std::string& name,
                    const std::string& format, double sizeMB)
{
    if (FindResource(id) != nullptr)
    {
        std::cout << "编号重复。\n";
        return false;
    }
    resources.push_back(new ES(id, name, format, sizeMB));
    std::cout << "添加电子资源成功。\n";
    return true;
}

bool Library::Borrow(const std::string& resourceId, const std::string& readerId)
{
    Resource* resource = FindResource(resourceId);
    Reader* reader = FindReader(readerId);
    if (resource == nullptr || reader == nullptr)
    {
        std::cout << "资源或读者不存在。\n";
        return false;
    }
    if (CountActiveLoans(readerId) >= reader->GetMaxBorrow())
    {
        std::cout << "该读者已达到借阅上限。\n";
        return false;
    }

    for (std::size_t i = 0; i < records.size(); ++i)
    {
        if (!records[i].IsReturned()
            && records[i].GetResourceId() == resourceId
            && records[i].GetReaderId() == readerId)
        {
            std::cout << "该读者已借阅该资源且未归还。\n";
            return false;
        }
    }

    if (!resource->CanBorrow())
    {
        std::cout << "该资源已没有可借库存。\n";
        return false;
    }

    resource->OnBorrow();
    records.push_back(BorrowRecord(resource->GetId(), resource->GetName(),
                                   resource->Type(), reader->GetId(),
                                   reader->GetName()));
    std::cout << resource->BorrowMessage() << "\n";
    return true;
}

bool Library::Return(const std::string& resourceId, const std::string& readerId)
{
    for (std::size_t i = records.size(); i > 0; --i)
    {
        BorrowRecord& record = records[i - 1];
        if (record.IsReturned() || record.GetResourceId() != resourceId
            || record.GetReaderId() != readerId)
        {
            continue;
        }

        Resource* resource = FindResource(resourceId);
        if (resource == nullptr)
        {
            std::cout << "资源已不存在。\n";
            return false;
        }

        resource->OnReturn();
        record.MarkReturned();
        std::cout << "归还成功。\n";
        return true;
    }

    std::cout << "未找到该读者的未归还记录。\n";
    return false;
}

bool Library::AddStock(const std::string& resourceId, int count)
{
    Resource* resource = FindResource(resourceId);
    if (resource == nullptr)
    {
        std::cout << "未找到资源。\n";
        return false;
    }
    if (!resource->AddStock(count))
    {
        std::cout << "该资源不支持库存操作，或数量无效。\n";
        return false;
    }
    std::cout << "库存已增加。\n";
    return true;
}

void Library::ShowResources() const
{
    if (resources.empty())
    {
        std::cout << "暂无资源。\n";
        return;
    }
    for (std::size_t i = 0; i < resources.size(); ++i)
        resources[i]->Show();
}

void Library::ShowReaders() const
{
    for (std::size_t i = 0; i < readers.size(); ++i)
        readers[i]->Show();
}

void Library::ShowRecords() const
{
    if (records.empty())
    {
        std::cout << "暂无借阅记录。\n";
        return;
    }
    for (std::size_t i = 0; i < records.size(); ++i)
        records[i].Show();
}

std::vector<Resource*> Library::Search(const std::string& keyword) const
{
    std::vector<Resource*> result;
    for (std::size_t i = 0; i < resources.size(); ++i)
    {
        if (resources[i]->GetId().find(keyword) != std::string::npos
            || resources[i]->GetName().find(keyword) != std::string::npos)
        {
            result.push_back(resources[i]);
        }
    }
    return result;
}
