// 2451317 冯久恒 大数据
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <string>

using namespace std;

// 参数配置结构体
struct ParamConfig
{
    const char *name;        // 参数名称
    const char *description; // 参数描述
    bool hasValue;           // 是否带额外参数
    int defaultValue;        // 默认值
    int minValue;            // 最小值
    int maxValue;            // 最大值
};

// 解析结果结构体
struct PingConfig
{
    int packetSize;
    int packetCount;
    bool continuous;
    char ipAddress[16]; // 存储IP地址
};

void usage(const char *procName, const ParamConfig *params, int paramCount)
{
    cout << "Usage: " << procName;
    for (int i = 0; i < paramCount; i++)
    {
        cout << " [" << params[i].name;
        if (params[i].description != "")
            cout << " " << params[i].description;
        cout << "]";
    }
    cout.setf(ios::left);
    cout << " IP地址" << endl;
    cout << "       ==================================" << endl;
    cout << "        " << setw(5) << "参数" << setw(9) << "附加参数" << setw(12) << "范围" << "默认值" << endl;
    cout << "       ==================================" << endl;

    for (int i = 0; i < paramCount; i++)
    {
        string range = "[" + to_string(params[i].minValue) + ".." + to_string(params[i].maxValue) + "]";
        cout << "        " << setw(5) << params[i].name;
        cout << setw(9) << (int)params[i].hasValue;
        cout << setw(12) << range;
        cout << params[i].defaultValue;
        cout << endl;
    }
    cout << "       ==================================" << endl;
    cout << endl;
}

// 检查IP地址格式
bool checkIP(const char *ip)
{
    int dots = 0;
    int num = 0;
    int digitCount = 0;
    bool hasDigit = false;

    for (int i = 0; ip[i] != '\0'; i++)
    {
        if (isdigit(ip[i]))
        {
            num = num * 10 + (ip[i] - '0');
            digitCount++;
            hasDigit = true;

            if (num > 255)
                return false;

            if (digitCount > 1 && num == 0)
                return false;
        }
        else if (ip[i] == '.')
        {
            if (!hasDigit || digitCount == 0 || num > 255)
                return false;
            dots++;
            num = 0;
            digitCount = 0;
            hasDigit = false;
        }
        else
            return false;
    }

    if (!hasDigit || digitCount == 0 || num > 255 || dots != 3)
        return false;
    return true;
}

// 查找参数配置
const ParamConfig *findParamConfig(const ParamConfig *params, int paramCount, const char *name)
{
    for (int i = 0; i < paramCount; i++)
        if (strcmp(params[i].name, name) == 0)
            return &params[i];
    return NULL;
}

// 字符串转换为整数
bool stringToInt(const char *str, int *value)
{
    char *endptr;
    long result = strtol(str, &endptr, 10);

    if (*endptr != '\0' || str[0] == '\0')
        return false;

    *value = (int)result;
    return true;
}

// 解析命令行参数
int parseArguments(int argc, char *argv[], PingConfig *config, const ParamConfig *params, int paramCount)
{
    for (int i = 0; i < paramCount; i++)
    {
        if (strcmp(params[i].name, "-l") == 0)
            config->packetSize = params[i].defaultValue;
        else if (strcmp(params[i].name, "-n") == 0)
            config->packetCount = params[i].defaultValue;
        else if (strcmp(params[i].name, "-t") == 0)
            config->continuous = false;
    }
    if (argc == 1)
    {
        usage(argv[0], params, paramCount);
        return -1;
    }

    const char *lastArg = argv[argc - 1];
    if (lastArg[0] == '-' || !checkIP(lastArg))
    {
        cerr << "IP地址错误" << endl;
        return -1;
    }
#ifdef _WIN32
    strncpy_s(config->ipAddress, lastArg, 15);
#else
    strncpy(config->ipAddress, lastArg, 15);
#endif
    config->ipAddress[15] = '\0';

    int i = 1;
    while (i < argc - 1)
    {
        const char *arg = argv[i];

        if (arg[0] != '-')
        {
            cerr << "参数" << arg << "不是以-开头的合法参数" << endl;
            return -1;
        }
        const ParamConfig *paramConfig = findParamConfig(params, paramCount, arg);
        if (!paramConfig)
        {
            cerr << "参数" << arg << "不存在" << endl;
            return -1;
        }

        if (paramConfig->hasValue)
        {
            if (i + 1 >= argc - 1)
            {
                cerr << "参数" << arg << "没有后续参数" << endl;
                return -1;
            }
            const char *valueStr = argv[i + 1];
            if (valueStr[0] == '-')
            {
                cerr << "参数" << arg << "没有后续参数" << endl;
                return -1;
            }

            int value;
            if (!stringToInt(valueStr, &value) || value < paramConfig->minValue || value > paramConfig->maxValue)
                value = paramConfig->defaultValue;
            if (strcmp(arg, "-l") == 0)
                config->packetSize = value;
            else if (strcmp(arg, "-n") == 0)
                config->packetCount = value;
            i += 2;
        }
        else
        {
            if (strcmp(arg, "-t") == 0)
                config->continuous = true;
            i++;
        }
    }
    return 0;
}

void display(const PingConfig *config, const ParamConfig *params)
{
    cout << "参数检查通过" << endl;
    cout << params[0].name << " 参数：" << config->packetSize << endl;
    cout << params[1].name << " 参数：" << config->packetCount << endl;
    cout << params[2].name << " 参数：" << config->continuous << endl;
    cout << "IP地址：" << config->ipAddress << endl;
}

int main(int argc, char *argv[])
{
    const int PARAM_COUNT = 3;
    ParamConfig params[PARAM_COUNT] = {
        {"-l", "大小", true, 64, 32, 64000},
        {"-n", "数量", true, 4, 1, 1024},
        {"-t", "", false, 0, 0, 1}};

    PingConfig config;

    int result = parseArguments(argc, argv, &config, params, PARAM_COUNT);

    if (result == 0)
        display(&config, params);
    else
        return 1;

    return 0;
}