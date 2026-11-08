#pragma once

#include <string>
#include <vector>

class Account
{
public:
    Account();

    bool Login(const std::string& username, const std::string& password);
    void Logout();
    bool IsLoggedIn() const;
    std::string CurrentUsername() const;

    bool ChangeCurrentPassword(const std::string& oldPassword, const std::string& newPassword);
    bool AddAccount(const std::string& username, const std::string& password);
    bool DeleteAccount(const std::string& username);

private:
    struct Entry
    {
        std::string username;
        std::string salt;
        std::string passwordHash;
    };

    std::vector<Entry> entries;
    int currentIndex;

    int FindIndex(const std::string& username) const;
    bool VerifyPassword(const Entry& entry, const std::string& password) const;
    void SetPassword(Entry& entry, const std::string& password);

    static std::string Trim(const std::string& text);
    static std::string MakeSalt();
    static std::string HashPassword(const std::string& salt, const std::string& password);
};
