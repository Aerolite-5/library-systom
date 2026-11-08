#pragma once
#include <string>
#include <vector>

#include "Reader.h"
#include "Repository.h"

// 读者目录：只负责学生/教师档案，不处理借阅记录。
class ReaderRegistry
{
    Repository<Reader*> readers;

public:
    ReaderRegistry();
    ~ReaderRegistry();

    ReaderRegistry(const ReaderRegistry&) = delete;
    ReaderRegistry& operator=(const ReaderRegistry&) = delete;

    bool AddStudent(const std::string& id, const std::string& name,
                    const std::string& major);
    bool AddTeacher(const std::string& id, const std::string& name,
                    const std::string& department, const std::string& title);
    bool Delete(const std::string& id);

    void ShowAll() const;
    Reader* Find(const std::string& id);
    const Reader* Find(const std::string& id) const;
    const Repository<Reader*>& All() const;
};
