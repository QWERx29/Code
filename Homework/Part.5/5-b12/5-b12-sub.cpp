// 2451317 冯久恒 计算机

/* 函数实现部分，{ }内的东西可以任意调整，目前的return 0只是一个示例，可改变 */

/* 不允许定义任何形式的外部全局、静态全局、宏定义、只读变量 */

/***************************************************************************
  函数名称：tj_strlen
  功    能：返回字符串长度
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strlen(const char str[])
{
    int len = 0;
	while (str[len] != '\0')
		len++;
    /* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
    return len;
}

/***************************************************************************
  函数名称：tj_strcat
  功    能：将s2复制到s1后
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcat(char s1[], const char s2[])
{
    int l1 = tj_strlen(s1), l2 = tj_strlen(s2);
	for (int i = 0; i<l2; i++)
        s1[l1 + i] = s2[i];
    s1[l1 + l2] = '\0';
    return 0; 
}

/***************************************************************************
  函数名称：tj_strncat
  功    能：将字符串s2的前len个字符追加到s1后面
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strncat(char s1[], const char s2[], const int len)
{
    int l1 = tj_strlen(s1);
    for (int i = 0; (i < len && s2[i] != '\0'); i++)
        s1[l1 + i] = s2[i];
    return 0; 
}

/***************************************************************************
  函数名称：tj_strcpy
  功    能：将字符串s2复制到s1中,覆盖s1中原内容,复制时包含\0
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcpy(char s1[], const char s2[])
{
    for (int i = 0; i <= tj_strlen(s2); i++) 
        s1[i] = s2[i];
    for (int i = tj_strlen(s2); i < 80; i++)
        s1[i] = '\0';
    return 0;
}

/***************************************************************************
  函数名称：tj_strncpy
  功    能：将字符串s2的前len个字符复制到s1中,复制时不含\0
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strncpy(char s1[], const char s2[], const int len)
{
    for (int i = 0; (i < len && s2[i] != '\0'); i++)
        s1[i] = s2[i];
    return 0;
}

/***************************************************************************
  函数名称：tj_strcmp
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcmp(const char s1[], const char s2[])
{
    int len = tj_strlen(s1) < tj_strlen(s2) ? tj_strlen(s1) : tj_strlen(s2);
    for (int i = 0; i <= len; i++)
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }
    return 0;
}

/***************************************************************************
  函数名称：tj_strcasecmp
  功    能：比较字符串s1和s2的大小,不分大小写
  输入参数：
  返 回 值：相等为0,不相等为第一个不相等字符的ASCII码差值
  说    明：
***************************************************************************/
int tj_strcasecmp(const char s1[], const char s2[])
{
    int len = tj_strlen(s1) < tj_strlen(s2) ? tj_strlen(s1) : tj_strlen(s2);
    for (int i = 0; i <= len; i++)
    {
        if (s1[i] != s2[i])
        {
            char ch1 = s1[i], ch2 = s2[i];
            if (ch1 >= 'A' && ch1 <= 'Z')
                ch1 += ('a' - 'A');
            if (ch2 >= 'A' && ch2 <= 'Z')
                ch2 += ('a' - 'A');
            if (ch1 == ch2)
                continue;
            else
                return (ch1 - ch2);
        }
        else
            continue;
    }
    return 0; //return值可根据需要修改
}

/***************************************************************************
  函数名称：tj_strncmp
  功    能：比较字符串s1和s2的前len个字符的大小,英文字母要区分大小写
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strncmp(const char s1[], const char s2[], const int len)
{
    int ls = (tj_strlen(s1) < tj_strlen(s2) ? tj_strlen(s1) : tj_strlen(s2)) + 1;
    int l = ls < len ? ls : len;
    for (int i = 0; i < l; i++)
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }
    return 0; 
}

/***************************************************************************
  函数名称：tj_strcasencmp
  功    能：比较字符串s1和s2的前len个字符的大小,英文字母不区分大小写
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strcasencmp(const char s1[], const char s2[], const int len)
{
    int ls = (tj_strlen(s1) < tj_strlen(s2) ? tj_strlen(s1) : tj_strlen(s2)) + 1;
    int l = ls < len ? ls : len;
    for (int i = 0; i < l; i++)
    {
        if (s1[i] != s2[i])
        {
            char ch1 = s1[i], ch2 = s2[i];
            if (ch1 >= 'A' && ch1 <= 'Z')
                ch1 += ('a' - 'A');
            if (ch2 >= 'A' && ch2 <= 'Z')
                ch2 += ('a' - 'A');
            if (ch1 == ch2)
                continue;
            else
                return (ch1 - ch2);
        }
        else
            continue;
    }
    return 0;
}

/***************************************************************************
  函数名称：tj_strupr
  功    能：小写字母转大写
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strupr(char str[])
{
    for (int i = 0; i < tj_strlen(str); i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= ('a' - 'A');
    }
    return 0; //return值可根据需要修改
}

/***************************************************************************
  函数名称：tj_strlwr
  功    能：大写字母转小写
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strlwr(char str[])
{
    for (int i = 0; i < tj_strlen(str); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += ('a' - 'A');
    }
    return 0;
}

/***************************************************************************
  函数名称：tj_strchr
  功    能：查找字符首次出现的位置
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strchr(const char str[], char ch)
{
    for (int i = 0; i < tj_strlen(str); i++)
    {
        if (str[i] == ch)
            return (i + 1);
    }
    return 0; //return值可根据需要修改
}

/***************************************************************************
  函数名称：tj_strstr
  功    能：查找子串首次出现的位置
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strstr(const char str[], const char substr[])
{
    for (int i = 0; i < tj_strlen(str); i++)
    {
        if (str[i] == substr[0])
        {
            int f = 0;
            for (int j = 0; j < tj_strlen(substr); j++)
            {
                if (substr[j] == str[i + j])
                    continue;
                else
                    f = 1;
            }
            if (f == 0)
                return i + 1;
            else
                continue;
        }
    }
    return 0;
}

/***************************************************************************
  函数名称：tj_strrchr
  功    能：查找字符首次出现的位置-从右往左
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strrchr(const char str[], const char ch)
{
    for (int i = tj_strlen(str)-1; i >= 0; i--)
    {
        if (str[i] == ch)
            return (i + 1);
    }
    return 0; 
}

/***************************************************************************
  函数名称：tj_strrstr
  功    能：查找子串首次出现的位置-从右往左
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strrstr(const char str[], const char substr[])
{
    for (int i = tj_strlen(str)-1; i >= 0; i--)
    {
        if (str[i] == substr[0])
        {
            int f = 0;
            for (int j = 0; j < tj_strlen(substr); j++)
            {
                if (substr[j] == str[i + j])
                    continue;
                else
                    f = 1;
            }
            if (f == 0)
                return i + 1;
            else
                continue;
        }
    }
    return 0;
}

/***************************************************************************
  函数名称：tj_strrev
  功    能：字符串翻转
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int tj_strrev(char str[])
{
    for (int i = 0; i < ((tj_strlen(str) - 1) / 2); i++)
    {
        char t;
        t = str[i];
        str[i] = str[tj_strlen(str) - i - 1];
        str[tj_strlen(str) - i - 1] = t;
    }
    return 0; 
}
