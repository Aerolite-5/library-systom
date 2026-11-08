#pragma execution_character_set("utf-8")
#include "ResourceCatalog.h"

#include "Book.h"
#include "ES.h"
#include "Magazine.h"
#include "PhysicalResource.h"

#include <algorithm>
#include <iostream>

ResourceCatalog::ResourceCatalog()
{
    categories.push_back(Category("C01", "计算机"));
    categories.push_back(Category("C02", "文学"));
    categories.push_back(Category("C03", "体育"));
}

ResourceCatalog::~ResourceCatalog()
{
    for (std::size_t i = 0; i < resources.size(); ++i)
        delete resources[i];
}

bool ResourceCatalog::Add(Resource* resource)
{
    if (resource == nullptr)
        return false;
    if (Find(resource->GetId()) != nullptr)
    {
        std::cout << "资源编号已存在。\n";
        delete resource;
        return false;
    }
    resources.push_back(resource);
    return true;
}

bool ResourceCatalog::AddBook(const std::string& id, const std::string& name,
                              const std::string& category, const std::string& author,
                              const std::string& publisher, int stock)
{
    if (id.empty() || name.empty() || category.empty() || stock <= 0)
    {
        std::cout << "编号、书名、分类不能为空，库存必须大于 0。\n";
        return false;
    }

    if (!Add(new Book(id, name, category, author, publisher, stock)))
        return false;
    std::cout << "新增图书成功，初始库存 " << stock << "。\n";
    return true;
}

bool ResourceCatalog::AddMagazine(const std::string& id, const std::string& name,
                                  const std::string& category, const std::string& issue,
                                  int stock)
{
    if (id.empty() || name.empty() || category.empty() || stock <= 0)
    {
        std::cout << "编号、名称、分类不能为空，库存必须大于 0。\n";
        return false;
    }

    if (!Add(new Magazine(id, name, category, issue, stock)))
        return false;
    std::cout << "新增杂志成功，初始库存 " << stock << "。\n";
    return true;
}

bool ResourceCatalog::AddES(const std::string& id, const std::string& name,
                            const std::string& category, const std::string& format,
                            double sizeMB)
{
    if (id.empty() || name.empty() || category.empty())
    {
        std::cout << "编号、名称和分类不能为空。\n";
        return false;
    }

    if (!Add(new ES(id, name, category, format, sizeMB)))
        return false;
    std::cout << "新增电子资源成功，可多人同时借阅。\n";
    return true;
}

bool ResourceCatalog::AddStock(const std::string& resourceId, int count)
{
    Resource* resource = Find(resourceId);
    if (resource == nullptr)
    {
        std::cout << "未找到资源。\n";
        return false;
    }

    PhysicalResource* physical = dynamic_cast<PhysicalResource*>(resource);
    if (physical == nullptr)
    {
        std::cout << "电子书可以多人同时借阅，不需要库存。\n";
        return false;
    }

    std::string reason;
    if (!physical->AddStock(count, reason))
    {
        std::cout << reason << "\n";
        return false;
    }
    std::cout << "库存已增加，当前库存 " << physical->GetStock() << "。\n";
    return true;
}

bool ResourceCatalog::ReduceStock(const std::string& resourceId, int count)
{
    Resource* resource = Find(resourceId);
    if (resource == nullptr)
    {
        std::cout << "未找到资源。\n";
        return false;
    }

    PhysicalResource* physical = dynamic_cast<PhysicalResource*>(resource);
    if (physical == nullptr)
    {
        std::cout << "电子书可以多人同时借阅，不需要库存。\n";
        return false;
    }

    std::string reason;
    if (!physical->ReduceStock(count, reason))
    {
        std::cout << reason << "\n";
        return false;
    }
    std::cout << "库存已减少，当前库存 " << physical->GetStock() << "。\n";
    return true;
}

bool ResourceCatalog::Modify(const std::string& id, const std::string& name,
                             const std::string& category)
{
    Resource* resource = Find(id);
    if (resource == nullptr)
    {
        std::cout << "未找到资源。\n";
        return false;
    }
    if (!name.empty())
        resource->SetName(name);
    if (!category.empty())
        resource->SetCategory(category);
    std::cout << "修改成功。\n";
    return true;
}

bool ResourceCatalog::Delete(const std::string& id)
{
    Resource* resource = Find(id);
    if (resource == nullptr)
    {
        std::cout << "未找到资源。\n";
        return false;
    }

    resources.erase(std::find(resources.begin(), resources.end(), resource));
    delete resource;
    std::cout << "删除成功。\n";
    return true;
}

void ResourceCatalog::ShowOne(const std::string& id) const
{
    const Resource* resource = Find(id);
    if (resource == nullptr)
    {
        std::cout << "未找到资源。\n";
        return;
    }
    std::cout << *resource << "\n";
}

void ResourceCatalog::ShowAll() const
{
    if (resources.empty())
    {
        std::cout << "暂无资源。\n";
        return;
    }
    for (std::size_t i = 0; i < resources.size(); ++i)
        std::cout << i + 1 << ". " << *resources[i] << "\n";
}

std::vector<Resource*> ResourceCatalog::Search(const std::string& keyword) const
{
    std::vector<Resource*> result;
    for (std::size_t i = 0; i < resources.size(); ++i)
    {
        Resource* resource = resources[i];
        if (resource->GetId().find(keyword) != std::string::npos
            || resource->GetName().find(keyword) != std::string::npos
            || resource->GetCategory().find(keyword) != std::string::npos)
        {
            result.push_back(resource);
        }
    }
    return result;
}

Resource* ResourceCatalog::Find(const std::string& id)
{
    for (std::size_t i = 0; i < resources.size(); ++i)
    {
        if (resources[i]->GetId() == id)
            return resources[i];
    }
    return nullptr;
}

const Resource* ResourceCatalog::Find(const std::string& id) const
{
    for (std::size_t i = 0; i < resources.size(); ++i)
    {
        if (resources[i]->GetId() == id)
            return resources[i];
    }
    return nullptr;
}

const Repository<Category>& ResourceCatalog::Categories() const
{
    return categories;
}

const Repository<Resource*>& ResourceCatalog::All() const
{
    return resources;
}
