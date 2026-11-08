#pragma once
#include <ctime>
#include <string>

inline std::string FormatDate(std::time_t value)
{
    if (value <= 0)
        return "-";

    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &value);
#else
    localtime_r(&value, &local);
#endif

    char buffer[24] = {};
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &local);
    return buffer;
}
