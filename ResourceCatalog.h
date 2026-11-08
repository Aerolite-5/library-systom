#pragma once
#include <string>
#include <vector>

#include "Category.h"
#include "Repository.h"
#include "Resource.h"

// 资源目录：只负责资源增删改查和库存，不处理借阅、读者、罚款。
class ResourceCatalog
{
    Repository<Resource*> resources;
    Repository<Category> categories;

    bool Add(Resource* resource);

public:
    ResourceCatalog();
    ~ResourceCatalog();

    ResourceCatalog(const ResourceCatalog&) = delete;
    ResourceCatalog& operator=(const ResourceCatalog&) = delete;

    bool AddBook(const std::string& id, const std::string& name,
                 const std::string& category, const std::string& author,
                 const std::string& publisher, int stock);
    bool AddMagazine(const std::string& id, const std::string& name,
                     const std::string& category, const std::string& issue,
                     int stock);
    bool AddES(const std::string& id, const std::string& name,
               const std::string& category, const std::string& format,
               double sizeMB);

    bool AddStock(const std::string& resourceId, int count);
    bool ReduceStock(const std::string& resourceId, int count);
    bool Modify(const std::string& id, const std::string& name,
                const std::string& category);
    bool Delete(const std::string& id);

    void ShowOne(const std::string& id) const;
    void ShowAll() const;
    std::vector<Resource*> Search(const std::string& keyword) const;

    Resource* Find(const std::string& id);
    const Resource* Find(const std::string& id) const;

    const Repository<Category>& Categories() const;
    const Repository<Resource*>& All() const;
};
