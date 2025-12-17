/* 学号 姓名 班级 */

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <cstring>
#include "16-b5.h"
using namespace std;

/* 给出 TString 类的所有成员函数的体外实现 */
void TString::init_CStr(const char *str)
{
    if (str == nullptr || str[0] == '\0')
    {
        content = nullptr;
        len = 0;
    }
    else
    {
        len = strlen(str);
        content = new char[len + 1];
        strcpy(content, str);
    }
}

void TString::allocateMemory(int length)
{
    if (content != nullptr)
        delete[] content;
    if (length > 0)
    {
        content = new char[length + 1];
        len = length;
    }
    else
    {
        content = nullptr;
        len = 0;
    }
}

TString::TString() : content(nullptr), len(0) {}

TString::TString(const char *str) : content(nullptr), len(0)
{
    init_CStr(str);
}

TString::TString(const TString &other) : content(nullptr), len(0)
{
    if (other.content != nullptr)
    {
        len = other.len;
        content = new char[len + 1];
        strcpy(content, other.content);
    }
}

TString::~TString()
{
    if (content != nullptr)
    {
        delete[] content;
        content = nullptr;
    }
    len = 0;
}

TString &TString::operator=(const TString &other)
{
    if (this != &other)
    {
        if (content != nullptr)
            delete[] content;
        if (other.content != nullptr)
        {
            len = other.len;
            content = new char[len + 1];
            strcpy(content, other.content);
        }
        else
        {
            content = nullptr;
            len = 0;
        }
    }
    return *this;
}

TString &TString::operator=(const char *str)
{
    if (content != nullptr)
        delete[] content;
    init_CStr(str);
    return *this;
}
/*
TString &TString::operator=(const TString &other)
{
    if (this != &other)
    {
        if (content != nullptr)
            delete[] content;
        if (other.content != nullptr)
        {
            len = other.len;
            content = new char[len + 1];
            strcpy(content, other.content);
        }
        else
        {
            content = nullptr;
            len = 0;
        }
    }
    return *this;
}

TString &TString::operator=(const char *str)
{
    if (content != nullptr)
        delete[] content;
    init_CStr(str);
    return *this;
}
*/
istream &operator>>(istream &in, TString &str)
{
    char buffer[1024];
    in >> buffer;
    str = buffer;
    return in;
}

ostream &operator<<(ostream &out, const TString &str)
{
    if (str.content == nullptr || str.len == 0)
        out << "<EMPTY>";
    else
        out << str.content;
    return out;
}

TString TString::operator+(const TString &other) const
{
    if (content == nullptr || len == 0)
        return other;
    if (other.content == nullptr || other.len == 0)
        return *this;

    TString result;
    result.len = len + other.len;
    result.content = new char[result.len + 1];
    strcpy(result.content, content);
    strcat(result.content, other.content);
    return result;
}

TString TString::operator+(const char *str) const
{
    if (str == nullptr || str[0] == '\0')
        return *this;
    if (content == nullptr || len == 0)
        return TString(str);

    TString result;
    int strLen = strlen(str);
    result.len = len + strLen;
    result.content = new char[result.len + 1];
    strcpy(result.content, content);
    strcat(result.content, str);
    return result;
}

TString operator+(const char *str, const TString &tstr)
{
    if (str == nullptr || str[0] == '\0')
        return tstr;
    if (tstr.content == nullptr || tstr.len == 0)
        return TString(str);

    TString result;
    int strLen = strlen(str);
    result.len = strLen + tstr.len;
    result.content = new char[result.len + 1];
    strcpy(result.content, str);
    strcat(result.content, tstr.content);
    return result;
}

TString TString::operator+(char ch) const
{
    TString result;
    result.len = len + 1;
    result.content = new char[result.len + 1];
    if (content != nullptr && len > 0)
        strcpy(result.content, content);
    else
        result.content[0] = '\0';
    result.content[len] = ch;
    result.content[len + 1] = '\0';
    return result;
}

TString operator+(char ch, const TString &tstr)
{
    TString result;
    result.len = 1 + tstr.len;
    result.content = new char[result.len + 1];
    result.content[0] = ch;
    result.content[1] = '\0';
    if (tstr.content != nullptr && tstr.len > 0)
        strcat(result.content, tstr.content);
    return result;
}

TString &TString::operator+=(const TString &other)
{
    if (other.content == nullptr || other.len == 0)
        return *this;
    if (content == nullptr || len == 0)
    {
        *this = other;
        return *this;
    }

    int newLen = len + other.len;
    char *newContent = new char[newLen + 1];
    strcpy(newContent, content);
    strcat(newContent, other.content);

    delete[] content;
    content = newContent;
    len = newLen;
    return *this;
}

TString &TString::operator+=(const char *str)
{
    if (str == nullptr || str[0] == '\0')
        return *this;
    if (content == nullptr || len == 0)
    {
        *this = str;
        return *this;
    }

    int strLen = strlen(str);
    int newLen = len + strLen;
    char *newContent = new char[newLen + 1];
    strcpy(newContent, content);
    strcat(newContent, str);

    delete[] content;
    content = newContent;
    len = newLen;
    return *this;
}

TString &TString::operator+=(char ch)
{
    int newLen = len + 1;
    char *newContent = new char[newLen + 1];

    if (content != nullptr && len > 0)
        strcpy(newContent, content);
    else
        newContent[0] = '\0';

    newContent[len] = ch;
    newContent[len + 1] = '\0';

    delete[] content;
    content = newContent;
    len = newLen;
    return *this;
}

TString &TString::append(const TString &other)
{
    return (*this += other);
}

TString &TString::append(const char *str)
{
    return (*this += str);
}

TString &TString::append(char ch)
{
    return (*this += ch);
}

TString TString::operator-(const TString &other) const
{
    if (content == nullptr || len == 0 || other.content == nullptr || other.len == 0)
        return *this;
    const char *pos = strstr(content, other.content);
    if (pos == nullptr)
        return *this;
    TString result;
    int offset = static_cast<int>(pos - content);
    result.len = len - other.len;

    if (result.len == 0)
    {
        result.content = nullptr;
        return result;
    }

    result.content = new char[result.len + 1];
    if (offset > 0)
    {
        strncpy(result.content, content, offset);
        result.content[offset] = '\0';
    }
    else
        result.content[0] = '\0';
    strcat(result.content, pos + other.len);

    return result;
}

TString TString::operator-(const char *str) const
{
    if (content == nullptr || len == 0 || str == nullptr || str[0] == '\0')
        return *this;

    return (*this - TString(str));
}

TString TString::operator-(char ch) const
{
    if (content == nullptr || len == 0)
        return *this;

    TString result;
    int index = -1;
    for (int i = 0; i < len; i++)
    {
        if (content[i] == ch)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
        return *this;
    result.len = len - 1;
    result.content = new char[result.len + 1];
    if (index > 0)
    {
        strncpy(result.content, content, index);
        result.content[index] = '\0';
    }
    else
        result.content[0] = '\0';
    strcat(result.content, content + index + 1);

    return result;
}

TString &TString::operator-=(const TString &other)
{
    if (content == nullptr || len == 0 || other.content == nullptr || other.len == 0)
        return *this;

    const char *pos = strstr(content, other.content);
    if (pos == nullptr)
        return *this;

    int offset = static_cast<int>(pos - content);
    int newLen = len - other.len;

    if (newLen == 0)
    {
        clear();
        return *this;
    }

    char *newContent = new char[newLen + 1];

    if (offset > 0)
    {
        strncpy(newContent, content, offset);
        newContent[offset] = '\0';
    }
    else
        newContent[0] = '\0';
    strcat(newContent, pos + other.len);

    delete[] content;
    content = newContent;
    len = newLen;

    return *this;
}

TString &TString::operator-=(const char *str)
{
    if (content == nullptr || len == 0 || str == nullptr || str[0] == '\0')
        return *this;

    *this = *this - str;
    return *this;
}

TString &TString::operator-=(char ch)
{
    if (content == nullptr || len == 0)
        return *this;
    int index = -1;
    for (int i = 0; i < len; i++)
    {
        if (content[i] == ch)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
        return *this;

    int newLen = len - 1;
    char *newContent = new char[newLen + 1];
    if (index > 0)
    {
        strncpy(newContent, content, index);
        newContent[index] = '\0';
    }
    else
        newContent[0] = '\0';
    strcat(newContent, content + index + 1);
    delete[] content;
    content = newContent;
    len = newLen;

    return *this;
}

TString TString::operator*(int n) const
{
    if (n <= 0 || content == nullptr || len == 0)
        return TString();

    TString result;
    result.len = len * n;
    result.content = new char[result.len + 1];
    result.content[0] = '\0';

    for (int i = 0; i < n; i++)
        strcat(result.content, content);

    return result;
}

TString &TString::operator*=(int n)
{
    if (n <= 0)
        clear();
    else if (n != 1 && content != nullptr && len > 0)
        *this = *this * n;
    return *this;
}

/* 反转操作 */

TString TString::operator!() const
{
    if (content == nullptr || len == 0)
        return TString();

    TString result;
    result.len = len;
    result.content = new char[len + 1];

    for (int i = 0; i < len; i++)
        result.content[i] = content[len - 1 - i];
    result.content[len] = '\0';
    return result;
}

bool TString::operator==(const TString &other) const
{
    if (content == nullptr && (other.content == nullptr || other.len == 0))
        return true;
    if (content == nullptr || other.content == nullptr)
        return false;
    return strcmp(content, other.content) == 0;
}

bool TString::operator!=(const TString &other) const
{
    return !(*this == other);
}

bool TString::operator<(const TString &other) const
{
    if (content == nullptr && (other.content == nullptr || other.len == 0))
        return false;
    if (content == nullptr)
        return true;
    if (other.content == nullptr)
        return false;
    return strcmp(content, other.content) < 0;
}

bool TString::operator<=(const TString &other) const
{
    return (*this < other) || (*this == other);
}

bool TString::operator>(const TString &other) const
{
    return !(*this <= other);
}

bool TString::operator>=(const TString &other) const
{
    return !(*this < other);
}

bool TString::operator==(const char *str) const
{
    if (content == nullptr && (str == nullptr || str[0] == '\0'))
        return true;
    if (content == nullptr || str == nullptr)
        return false;
    return strcmp(content, str) == 0;
}

bool TString::operator!=(const char *str) const
{
    return !(*this == str);
}

bool TString::operator<(const char *str) const
{
    if (content == nullptr && (str == nullptr || str[0] == '\0'))
        return false;
    if (content == nullptr)
        return true;
    if (str == nullptr)
        return false;
    return strcmp(content, str) < 0;
}

bool TString::operator<=(const char *str) const
{
    return (*this < str) || (*this == str);
}

bool TString::operator>(const char *str) const
{
    return !(*this <= str);
}

bool TString::operator>=(const char *str) const
{
    return !(*this < str);
}

bool operator==(const char *str, const TString &tstr)
{
    return tstr == str;
}

bool operator!=(const char *str, const TString &tstr)
{
    return !(tstr == str);
}

bool operator<(const char *str, const TString &tstr)
{
    return tstr > str;
}

bool operator<=(const char *str, const TString &tstr)
{
    return tstr >= str;
}

bool operator>(const char *str, const TString &tstr)
{
    return tstr < str;
}

bool operator>=(const char *str, const TString &tstr)
{
    return tstr <= str;
}

int TString::length() const
{
    return len;
}

const char *TString::c_str() const
{
    if (content == nullptr)
        return "";
    return content;
}

char &TString::operator[](int index)
{
    static char dummy = '\0';
    if (content == nullptr || index < 0 || index >= len)
        return dummy;
    return content[index];
}

const char &TString::operator[](int index) const
{
    static const char dummy = '\0';
    if (content == nullptr || index < 0 || index >= len)
        return dummy;
    return content[index];
}

void TString::clear()
{
    if (content != nullptr)
    {
        delete[] content;
        content = nullptr;
    }
    len = 0;
}

bool TString::empty() const
{
    return (content == nullptr || len == 0);
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */
int TStringLen(const TString &str)
{
    return str.length();
}