#pragma execution_character_set("utf-8")
#include "Account.h"

#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

namespace
{
// ---------------- SHA-256（密码加盐散列，不保存明文） ----------------
const std::uint32_t kSha256Constants[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

std::uint32_t RotateRight(std::uint32_t value, int bits)
{
    return (value >> bits) | (value << (32 - bits));
}

std::string Sha256(const std::string& text)
{
    std::vector<unsigned char> message(text.begin(), text.end());
    const std::uint64_t bitLength = static_cast<std::uint64_t>(message.size()) * 8;

    message.push_back(0x80);
    while (message.size() % 64 != 56)
        message.push_back(0x00);
    for (int shift = 56; shift >= 0; shift -= 8)
        message.push_back(static_cast<unsigned char>((bitLength >> shift) & 0xFF));

    std::uint32_t hash[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    for (std::size_t offset = 0; offset < message.size(); offset += 64)
    {
        std::uint32_t words[64] = {};
        for (int i = 0; i < 16; ++i)
        {
            const std::size_t index = offset + static_cast<std::size_t>(i) * 4;
            words[i] = (static_cast<std::uint32_t>(message[index]) << 24)
                     | (static_cast<std::uint32_t>(message[index + 1]) << 16)
                     | (static_cast<std::uint32_t>(message[index + 2]) << 8)
                     | static_cast<std::uint32_t>(message[index + 3]);
        }
        for (int i = 16; i < 64; ++i)
        {
            const std::uint32_t s0 = RotateRight(words[i - 15], 7)
                                   ^ RotateRight(words[i - 15], 18)
                                   ^ (words[i - 15] >> 3);
            const std::uint32_t s1 = RotateRight(words[i - 2], 17)
                                   ^ RotateRight(words[i - 2], 19)
                                   ^ (words[i - 2] >> 10);
            words[i] = words[i - 16] + s0 + words[i - 7] + s1;
        }

        std::uint32_t a = hash[0];
        std::uint32_t b = hash[1];
        std::uint32_t c = hash[2];
        std::uint32_t d = hash[3];
        std::uint32_t e = hash[4];
        std::uint32_t f = hash[5];
        std::uint32_t g = hash[6];
        std::uint32_t h = hash[7];

        for (int i = 0; i < 64; ++i)
        {
            const std::uint32_t s1 = RotateRight(e, 6) ^ RotateRight(e, 11) ^ RotateRight(e, 25);
            const std::uint32_t ch = (e & f) ^ ((~e) & g);
            const std::uint32_t temp1 = h + s1 + ch + kSha256Constants[i] + words[i];
            const std::uint32_t s0 = RotateRight(a, 2) ^ RotateRight(a, 13) ^ RotateRight(a, 22);
            const std::uint32_t majority = (a & b) ^ (a & c) ^ (b & c);
            const std::uint32_t temp2 = s0 + majority;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
        hash[5] += f;
        hash[6] += g;
        hash[7] += h;
    }

    std::ostringstream result;
    result << std::hex << std::setfill('0');
    for (int i = 0; i < 8; ++i)
        result << std::setw(8) << hash[i];
    return result.str();
}
} // namespace

Account::Account()
    : currentIndex(-1)
{
    Entry entry;
    entry.username = "王铭扬";
    entry.salt = MakeSalt();
    entry.passwordHash = HashPassword(entry.salt, "wmy070522");
    entries.push_back(entry);
}

bool Account::Login(const std::string& username, const std::string& password)
{
    if (IsLoggedIn())
        return false;

    const int index = FindIndex(username);
    if (index < 0 || !VerifyPassword(entries[static_cast<std::size_t>(index)], password))
    {
        std::cout << "用户名或密码错误。\n";
        return false;
    }

    currentIndex = index;
    std::cout << "登录成功。\n";
    return true;
}

void Account::Logout()
{
    currentIndex = -1;
}

bool Account::IsLoggedIn() const
{
    return currentIndex >= 0 && static_cast<std::size_t>(currentIndex) < entries.size();
}

std::string Account::CurrentUsername() const
{
    if (!IsLoggedIn())
        return "";
    return entries[static_cast<std::size_t>(currentIndex)].username;
}

bool Account::ChangeCurrentPassword(const std::string& oldPassword, const std::string& newPassword)
{
    if (!IsLoggedIn())
        return false;

    Entry& entry = entries[static_cast<std::size_t>(currentIndex)];
    if (!VerifyPassword(entry, oldPassword))
    {
        std::cout << "原密码错误。\n";
        return false;
    }
    if (newPassword.size() < 6)
    {
        std::cout << "新密码至少 6 位。\n";
        return false;
    }
    if (newPassword == oldPassword)
    {
        std::cout << "新密码不能与原密码相同。\n";
        return false;
    }

    SetPassword(entry, newPassword);
    std::cout << "修改成功。\n";
    return true;
}

bool Account::AddAccount(const std::string& username, const std::string& password)
{
    const std::string name = Trim(username);
    if (name.empty())
    {
        std::cout << "用户名不能为空。\n";
        return false;
    }
    if (name.size() > 60)
    {
        std::cout << "用户名过长。\n";
        return false;
    }
    if (FindIndex(name) >= 0)
    {
        std::cout << "用户名已存在。\n";
        return false;
    }
    if (password.size() < 6)
    {
        std::cout << "密码至少 6 位。\n";
        return false;
    }

    Entry entry;
    entry.username = name;
    entry.salt = MakeSalt();
    entry.passwordHash = HashPassword(entry.salt, password);
    entries.push_back(entry);
    std::cout << "添加成功。\n";
    return true;
}

bool Account::DeleteAccount(const std::string& username)
{
    const int index = FindIndex(username);
    if (index < 0)
    {
        std::cout << "账号不存在。\n";
        return false;
    }
    if (index == currentIndex)
    {
        std::cout << "不能删除当前登录账号。\n";
        return false;
    }

    entries.erase(entries.begin() + index);
    if (index < currentIndex)
        --currentIndex;
    std::cout << "删除成功。\n";
    return true;
}

int Account::FindIndex(const std::string& username) const
{
    const std::string name = Trim(username);
    for (std::size_t i = 0; i < entries.size(); ++i)
    {
        if (entries[i].username == name)
            return static_cast<int>(i);
    }
    return -1;
}

bool Account::VerifyPassword(const Entry& entry, const std::string& password) const
{
    const std::string computed = HashPassword(entry.salt, password);
    const std::string& stored = entry.passwordHash;
    if (computed.size() != stored.size())
        return false;

    unsigned char difference = 0;
    for (std::size_t i = 0; i < computed.size(); ++i)
        difference |= static_cast<unsigned char>(computed[i] ^ stored[i]);
    return difference == 0;
}

void Account::SetPassword(Entry& entry, const std::string& password)
{
    entry.salt = MakeSalt();
    entry.passwordHash = HashPassword(entry.salt, password);
}

std::string Account::Trim(const std::string& text)
{
    const std::string whitespace = " \t\r\n";
    const std::size_t begin = text.find_first_not_of(whitespace);
    if (begin == std::string::npos)
        return "";
    const std::size_t end = text.find_last_not_of(whitespace);
    return text.substr(begin, end - begin + 1);
}

std::string Account::MakeSalt()
{
    std::random_device device;
    const std::uint64_t seed = static_cast<std::uint64_t>(std::time(nullptr))
                             ^ (static_cast<std::uint64_t>(device()) << 32)
                             ^ static_cast<std::uint64_t>(device());
    std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 255);

    static const char* hex = "0123456789abcdef";
    std::string salt;
    salt.reserve(16);
    for (int i = 0; i < 8; ++i)
    {
        const int byte = distribution(generator);
        salt.push_back(hex[(byte >> 4) & 0x0F]);
        salt.push_back(hex[byte & 0x0F]);
    }
    return salt;
}

std::string Account::HashPassword(const std::string& salt, const std::string& password)
{
    return Sha256(salt + ":" + password);
}
