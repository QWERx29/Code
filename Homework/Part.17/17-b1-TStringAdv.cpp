// 2451317 冯久恒 大数据

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "17-b1-TStringAdv.h"
using namespace std;

/* TStringAdv类的成员函数实现 */

TStringAdv &TStringAdv::assign(const TStringAdv &ts2)
{
    *this = ts2;
    return *this;
}

TStringAdv &TStringAdv::assign(const char *s)
{
    *this = s;
    return *this;
}

TStringAdv &TStringAdv::append(const TStringAdv &ts2)
{
    *this += ts2;
    return *this;
}

TStringAdv &TStringAdv::append(const char *s)
{
    *this += s;
    return *this;
}

TStringAdv &TStringAdv::append(const char &c)
{
    *this += c;
    return *this;
}

TStringAdv &TStringAdv::insert(const TStringAdv &ts2, int pos)
{
    int zeroBasedPos = pos - 1;

    if (pos < 1 || pos > length() + 1)
        return *this;

    const char *strToInsert = ts2.c_str();

    if (strToInsert == nullptr || strToInsert[0] == '\0')
        return *this;

    int insertLen = ts2.length();
    int newLen = length() + insertLen;

    char *newContent = new char[newLen + 1];
    if (zeroBasedPos > 0 && length() > 0)
    {
        strncpy(newContent, c_str(), zeroBasedPos);
        newContent[zeroBasedPos] = '\0';
    }
    else
        newContent[0] = '\0';
    strcat(newContent, strToInsert);
    if (zeroBasedPos < length())
        strcat(newContent, c_str() + zeroBasedPos);
    *this = newContent;
    delete[] newContent;

    return *this;
}

TStringAdv &TStringAdv::insert(const char *s, int pos)
{
    int zeroBasedPos = pos - 1;

    if (pos < 1 || pos > length() + 1)
        return *this;

    if (s == nullptr || s[0] == '\0')
        return *this;

    int insertLen = strlen(s);
    int newLen = length() + insertLen;

    char *newContent = new char[newLen + 1];

    if (zeroBasedPos > 0 && length() > 0)
    {
        strncpy(newContent, c_str(), zeroBasedPos);
        newContent[zeroBasedPos] = '\0';
    }
    else
        newContent[0] = '\0';

    strcat(newContent, s);

    if (zeroBasedPos < length())
        strcat(newContent, c_str() + zeroBasedPos);
    *this = newContent;
    delete[] newContent;

    return *this;
}

TStringAdv &TStringAdv::insert(const char &c, int pos)
{
    int zeroBasedPos = pos - 1;

    if (pos < 1 || pos > length() + 1)
        return *this;

    if (c == '\0')
    {
        if (pos == 1)
            clear();
        else if (zeroBasedPos <= length())
        {
            char *newContent = new char[zeroBasedPos + 1];
            if (zeroBasedPos > 0)
                strncpy(newContent, c_str(), zeroBasedPos);
            newContent[zeroBasedPos] = '\0';
            *this = newContent;
            delete[] newContent;
        }
        return *this;
    }

    int newLen = length() + 1;

    char *newContent = new char[newLen + 1];

    if (zeroBasedPos > 0 && length() > 0)
    {
        strncpy(newContent, c_str(), zeroBasedPos);
        newContent[zeroBasedPos] = '\0';
    }
    else
        newContent[0] = '\0';

    newContent[zeroBasedPos] = c;
    newContent[zeroBasedPos + 1] = '\0';

    if (zeroBasedPos < length())
        strcat(newContent, c_str() + zeroBasedPos);
    *this = newContent;
    delete[] newContent;

    return *this;
}

TStringAdv& TStringAdv::erase(const TStringAdv& ts2)
{
    *this -= ts2;
    return *this;
}

TStringAdv& TStringAdv::erase(const char* s)
{
    *this -= s;
    return *this;
}

TStringAdv& TStringAdv::erase(const char& c)
{
    *this -= c;
    return *this;
}

const TStringAdv TStringAdv::substr(const int pos, const int len) const
{
    if (pos < 1 || pos > length())
        return TStringAdv();

    int zeroBasedPos = pos - 1;

    int copyLen;
    if (len == -1)
        copyLen = length() - zeroBasedPos;
    else if (len <= 0)
        return TStringAdv();
    else
        copyLen = (zeroBasedPos + len > length()) ? (length() - zeroBasedPos) : len;

    TStringAdv result;

    if (copyLen > 0)
    {
        char* substrContent = new char[copyLen + 1];
        strncpy(substrContent, c_str() + zeroBasedPos, copyLen);
        substrContent[copyLen] = '\0';
        result = substrContent;
        delete[] substrContent;
    }

    return result;
}

char& TStringAdv::at(const int n)
{
    //int zeroBasedIndex = n - 1;
    //return (*this)[zeroBasedIndex];
    return (*this)[n];
}

int TStringAdvLen(const TStringAdv &str)
{
    return str.length();
}