#pragma once
#include <cstddef>
#include <utility>
#include <vector>

// 实验五：用类模板封装 vector 容器，统一提供增删查遍历接口。
template <typename T>
class Repository
{
    std::vector<T> items;

public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    void push_back(const T& value)
    {
        items.push_back(value);
    }

    void push_back(T&& value)
    {
        items.push_back(std::move(value));
    }

    void erase(iterator position)
    {
        items.erase(position);
    }

    std::size_t size() const
    {
        return items.size();
    }

    bool empty() const
    {
        return items.empty();
    }

    void clear()
    {
        items.clear();
    }

    T& operator[](std::size_t index)
    {
        return items[index];
    }

    const T& operator[](std::size_t index) const
    {
        return items[index];
    }

    iterator begin()
    {
        return items.begin();
    }

    iterator end()
    {
        return items.end();
    }

    const_iterator begin() const
    {
        return items.begin();
    }

    const_iterator end() const
    {
        return items.end();
    }

    std::vector<T>& Data()
    {
        return items;
    }

    const std::vector<T>& Data() const
    {
        return items;
    }
};
