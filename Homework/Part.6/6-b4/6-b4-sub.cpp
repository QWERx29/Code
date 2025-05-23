/* 学号 姓名 班级 */

#include <cstdio>   //NULL
//不再允许包含任何系统头文件

/* ----- 不允许定义任何形式的全局变量/全部数组/只读全局变量/宏定义!!!!! ----- */

/* 函数实现部分，{ }内的东西可以任意调整，目前的return只是一个示例，可改变 */
/***************************************************************************
  函数名称：tj_strlen
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strlen(const char *str)
{
    if (str == NULL)
        return 0;
    else
    {
        char* p = (char*)str;
        while (*p != '\0')
            p++;
        return p - str;
    }
}

/***************************************************************************
  函数名称：tj_strcat
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char *tj_strcat(char *s1, const char *s2)
{
    if (s1 == NULL)
        return NULL;
    else if (s2 == NULL)
        return s1;
    else
    {
        char* p = s1;
        while (*p != '\0')
            p++;
        for (; *s2 != '\0'; s2++, p++)
            *p = *s2;
        *p = '\0';
        return s1;
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char *tj_strncat(char *s1, const char *s2, const int len)
{
    if (s1 == NULL)
        return NULL;
    else if (s2 == NULL)
        return s1;
    else
    {
        char* p = s1;
        char* q = (char*)s2;
        while (*p != '\0')
            p++;
        for (; *q != '\0' && q < s2+len; q++, p++)
            *p = *q;
        *p = '\0';
        return s1;
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char *tj_strcpy(char *s1, const char *s2)
{
    if (s1 == NULL)
        return NULL;
    if (s2 == NULL) 
    {
        *s1 = '\0';
        return s1;
    }
    char* p = s1;
    char* q = (char*)s2;
    for (; *q != '\0'; q++, p++)
        *p = *q;
    *p = '\0';
    return s1;

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char *tj_strncpy(char *s1, const char *s2, const int len)
{
    if (s1 == NULL)
        return NULL;
    else if (s2 == NULL)
        return s1;
    else
    {
        char* p = s1;
        char* q = (char*)s2;
        for (; *q != '\0' && q < s2 + len; q++, p++)
            *p = *q;
        return s1;
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcmp(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL) 
        return 0;
    else if (s1 == NULL) 
        return -1;
    else if (s2 == NULL) 
        return 1;
    else
    {
        char* p = (char*)s1;
        char* q = (char*)s2;
        for (; *p != '\0' || *q != '\0'; p++, q++)
        {
            if (*p != *q)
                break;
        }
        return (*p - *q);
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcasecmp(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL)
        return 0;
    else if (s1 == NULL)
        return -1;
    else if (s2 == NULL)
        return 1;
    else
    {
        char* p = (char*)s1;
        char* q = (char*)s2;
        for (; *p != '\0' || *q != '\0'; p++, q++)
        {
            if (*p >= 'A' && *p <= 'Z')
                *p += ('a' - 'A');
            if (*q >= 'A' && *q <= 'Z')
                *q += ('a' - 'A');
            if (*p != *q)
                break;
        }
        return (*p - *q);
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strncmp(const char *s1, const char *s2, const int len)
{
    if (s1 == NULL && s2 == NULL)
        return 0;
    else if (s1 == NULL)
        return -1;
    else if (s2 == NULL)
        return 1;
    else
    {
        char* p = (char*)s1;
        char* q = (char*)s2;
        for (; (*p != '\0' || *q != '\0') && (p + 1 < s1 + len && q + 1 < s2 + len); p++, q++)
        {
            if (*p != *q)
                break;
        }
        return (*p - *q);
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcasencmp(const char *s1, const char *s2, const int len)
{
    if (s1 == NULL && s2 == NULL)
        return 0;
    else if (s1 == NULL)
        return -1;
    else if (s2 == NULL)
        return 1;
    else
    {
        char* p = (char*)s1;
        char* q = (char*)s2;
        for (; *p != '\0' || *q != '\0'; p++, q++)
        {
            if (*p >= 'A' && *p <= 'Z')
                *p += ('a' - 'A');
            if (*q >= 'A' && *q <= 'Z')
                *q += ('a' - 'A');
        }
        p = (char*)s1, q = (char*)s2;
        for (; (*p != '\0' || *q != '\0') && (p + 1 < s1 + len && q + 1 < s2 + len); p++, q++)
        {
            if (*p != *q)
                break;
        }
        return (*p - *q);
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char *tj_strupr(char *str)
{
    if (str == NULL)
        return NULL;
    else
    {
        char* p = str;
        while (*p != '\0')
        {
            if (*p >= 'a' && *p <= 'z')
                *p -= ('a' - 'A');
            p++;
        }
        return str;
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char *tj_strlwr(char *str)
{
    if (str == NULL)
        return NULL;
    else
    {
        char* p = str;
        while (*p != '\0')
        {
            if (*p >= 'A' && *p <= 'Z')
                *p += ('a' - 'A');
            p++;
        }
        return str;
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strchr(const char *str, const char ch)
{
    if (str == NULL)
        return 0;
    else
    {
        char* p = (char*)str;
        while (*p != '\0' && *p != ch)
            p++;
        if (p - str + 1 < tj_strlen(str))
            return p - str + 1;
        else
            return 0;
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strstr(const char *str, const char *substr)
{
    if (str == NULL || substr == NULL)
        return 0;
    char* p = (char*)str;
    char* q = (char*)substr;
    for (; *p != '\0'; p++)
    {
        q = (char*)substr;
        if (*p == *q)
        {
            int f = 0;
            char* s = p;
            for (q = (char*)substr; *q != '\0'; q++, s++)
            {
                if (*q == *s)
                    continue;
                else
                    f = 1;
            }
            if (f == 0)
                return p - str + 1;
            else
                continue;
        }
    }
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strrchr(const char *str, const char ch)
{
    if (str == NULL)
        return 0;
    else
    {
        char* p = (char*)str;
        while (*p != '\0')
            p++;
        p--;
        while (*p != '\0' && *p != ch)
            p--;
        if (p - str + 1 < tj_strlen(str) && p - str + 1 > 0)
            return p - str + 1;
        else
            return 0;
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strrstr(const char *str, const char *substr)
{
    if (str == NULL || substr == NULL)
        return 0;
    char* p = (char*)str;
    char* q = (char*)substr;
    while (*p != '\0')
        p++;
    p--;
    for (; *p != '\0'; p--)
    {
        q = (char*)substr;
        if (*p == *q)
        {
            int f = 0;
            char* s = p;
            for (q = (char*)substr; *q != '\0'; q++, s++)
            {
                if (*q == *s)
                    continue;
                else
                    f = 1;
            }
            if (f == 0)
                return p - str + 1;
            else
                continue;
        }
    }
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char *tj_strrev(char *str)
{
    if (str == NULL)
        return NULL;
    else
    {
        char* p = str;
        char* q = str;
        while (*q != '\0')
            q++;
        q--;
        while (p < q)
        {
            char t;
            t = *p, * p = *q, * q = t;
            p++, q--;
        }
    }
    return str;
}
