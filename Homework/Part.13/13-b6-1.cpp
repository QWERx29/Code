// 学号 姓名 班级
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#endif
// 根据需要可加入其它头文件
using namespace std;

// 此处为示例，允许修改结构体名称，允许修改结构体中的成员内容，要求sizeof必须是64
#pragma pack(push, 1)
struct gameData
{
    char nickname[16];              // 1-16: 玩家昵称
    unsigned short health;          // 17-18: 生命值
    unsigned short strength;        // 19-20: 力量值
    unsigned short constitution;    // 21-22: 体质
    unsigned short dexterity;       // 23-24: 灵巧
    unsigned int money;             // 25-28: 金钱数量
    unsigned int reputation;        // 29-32: 名声值
    unsigned int charm;             // 33-36: 魅力值
    unsigned long long playTime;    // 37-44: 游戏累计时间
    unsigned char moveSpeed;        // 45: 移动速度
    unsigned char attackSpeed;      // 46: 攻击速度
    unsigned char attackRange;      // 47: 攻击范围
    unsigned char reserved;         // 48: 预留值
    unsigned short attack;          // 49-50: 攻击力
    unsigned short defense;         // 51-52: 防御力
    unsigned char agility;          // 53: 敏捷度
    unsigned char intelligence;     // 54: 智力
    unsigned char experience;       // 55: 经验
    unsigned char level;            // 56: 等级
    unsigned short magic;           // 57-58: 魔法值
    unsigned char magicConsumption; // 59: 魔法消耗
    unsigned char magicDamage;      // 60: 魔法伤害力
    unsigned char hitRate;          // 61: 命中率
    unsigned char magicDefense;     // 62: 魔法防御力
    unsigned char criticalRate;     // 63: 暴击率
    unsigned char stamina;          // 64: 耐力
};
#pragma pack(pop)

/* 此处允许新增函数，数量不限
   1、所有新增的函数，均不允许定义新的 fstream / ifstream / ofstream 流对象，并进行打开/读/写/关闭等操作
   2、所有新增的函数，均不允许用C方式进行文件处理
   3、上述两个限制同样适用于main函数
*/
void displayData(const gameData &data)
{
    cout << "          玩家昵称：" << data.nickname << endl;
    cout << "            生命值：" << data.health << endl;
    cout << "            力量值：" << data.strength << endl;
    cout << "            体质值：" << data.constitution << endl;
    cout << "            灵巧值：" << data.dexterity << endl;
    cout << "            金钱值：" << data.money << endl;
    cout << "            名声值：" << data.reputation << endl;
    cout << "            魅力值：" << data.charm << endl;
    cout << "游戏累计时间(us)值：" << data.playTime << endl;
    cout << "        移动速度值：" << (int)data.moveSpeed << endl;
    cout << "        攻击速度值：" << (int)data.attackSpeed << endl;
    cout << "        攻击范围值：" << (int)data.attackRange << endl;
    cout << "          攻击力值：" << data.attack << endl;
    cout << "          防御力值：" << data.defense << endl;
    cout << "          敏捷度值：" << (int)data.agility << endl;
    cout << "            智力值：" << (int)data.intelligence << endl;
    cout << "            经验值：" << (int)data.experience << endl;
    cout << "            等级值：" << (int)data.level << endl;
    cout << "            魔法值：" << data.magic << endl;
    cout << "        消耗魔法值：" << (int)data.magicConsumption << endl;
    cout << "      魔法伤害力值：" << (int)data.magicDamage << endl;
    cout << "          命中率值：" << (int)data.hitRate << endl;
    cout << "      魔法防御力值：" << (int)data.magicDefense << endl;
    cout << "          暴击率值：" << (int)data.criticalRate << endl;
    cout << "            耐力值：" << (int)data.stamina << endl;
    cout << endl;
}

bool getInput(const string &prompt, unsigned short &value, unsigned short minVal, unsigned short maxVal)
{
    int input;
    cout << endl;
    while (1)
    {
        cout << prompt << "，当前值=" << value << "，范围[" << minVal << ".." << maxVal << "]，请输入 : ";
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        else if (input < minVal || input > maxVal)
        {
            cout << "非法的" << prompt << "值：" << input << endl;
            continue;
        }
        else
            break;
    }
    value = (unsigned short)input;
    cin.ignore(1024, '\n');
    return true;
}

bool getInput(const string &prompt, unsigned int &value, unsigned int minVal, unsigned int maxVal)
{
    int input;
    cout << endl;
    while (1)
    {
        cout << prompt << "，当前值=" << value << "，范围[" << minVal << ".." << maxVal << "]，请输入 : ";
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        else if (input < minVal || input > maxVal)
        {
            cout << "非法的" << prompt << "值：" << input << endl;
            continue;
        }
        else
            break;
    }
    value = (unsigned int)input;
    cin.ignore(1024, '\n');
    return true;
}

bool getInput(const string &prompt, unsigned long long &value, unsigned long long minVal, unsigned long long maxVal)
{
    unsigned long long input;
    while (1)
    {
        cout << prompt << "，当前值=" << value << "，范围[" << minVal << ".." << maxVal << "]，请输入 : ";
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        else if (input < minVal || input > maxVal)
        {
            cout << "非法的" << prompt << "值：" << input << endl;
            continue;
        }
        else
            break;
    }
    value = input;
    cin.ignore(1024, '\n');
    return true;
}

bool getInput(const string &prompt, unsigned char &value, unsigned char minVal, unsigned char maxVal)
{
    unsigned int input;
    while (1)
    {
        cout << prompt << "，当前值=" << (int)value << "，范围[" << (int)minVal << ".." << (int)maxVal << "]，请输入 : ";
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        else if (input < minVal || input > maxVal)
        {
            cout << "非法的" << prompt << "值：" << input << endl;
            continue;
        }
        else
            break;
    }
    value = static_cast<unsigned char>(input);
    cin.ignore(1024, '\n');
    return true;
}

bool getInput(const string &prompt, char *value, size_t maxLen)
{
    string input;
    cout << prompt << "，当前值=" << value << "，请输入 : ";
    getline(cin, input);
    if (input.length() > maxLen)
        input = input.substr(0, maxLen);
    strncpy(value, input.c_str(), maxLen);
    value[maxLen] = '\0';
    return true;
}

void printUsage(const string &fileName)
{
    cerr << "usage : " << fileName << " --modify | --read" << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次open、一次read（因为包含错误处理，允许多次close）
***************************************************************************/
int read()
{
    /* 本函数中只允许定义一个 ifstream流对象，不再允许定义任何形式的fstream/ifstream/ofstream流对象，也不允许使用C方式的文件处理 */
    ifstream gfile;
    gameData data;

    /* 文件打开，具体要求为：
       1、要求以读方式打开，打开方式***自行指定
       2、除本次open外，本函数其它地方不允许再出现open  */
    gfile.open("game.dat", ios::binary);
    if (!gfile.is_open())
    {
        cout << "无法打开文件game.dat" << endl;
        return -1;
    }
    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 gfile.read(***, sizeof(demo));
    */
    gfile.read(reinterpret_cast<char *>(&data), sizeof(gameData));
    if (gfile.fail())
    {
        cout << "打开game.dat文件失败" << endl;
        gfile.close();
        return -1;
    }

    displayData(data);
    gfile.close();
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次open、一次read、一次write（因为包含错误处理，允许多次close）
***************************************************************************/
int modify()
{
    /* 本函数中只允许定义一个 fstream流对象，不再允许定义任何形式的fstream/ifstream/ofstream流对象，也不允许使用C方式的文件处理 */
    fstream gfile;
    gameData data;
    bool modified = false, saved = false;
    /* 文件打开，具体要求为：
       1、要求以读写方式打开，打开方式***自行指定
       2、除本次open外，本函数其它地方不允许再出现open  */
    gfile.open("game.dat", ios::binary | ios::in | ios::out);
    if (!gfile.is_open())
    {
        cout << "无法打开文件game.dat" << endl;
        return -1;
    }
    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 gfile.read(***, sizeof(demo));
             只允许用一次性写入64字节的方法将***的内容写入game.dat中（缓冲区名称、结构体名称自行指定）
                 gfile.write(***, sizeof(demo));
    */
    gfile.read(reinterpret_cast<char *>(&data), sizeof(gameData));
    if (gfile.fail())
    {
        cout << "打开game.dat文件失败" << endl;
        gfile.close();
        return -1;
    }
    char choice;
    do
    {
        cout << "--------------------------------------" << endl;
        cout << " 游戏存档文件修改工具" << endl;
        cout << "--------------------------------------" << endl;
        cout << "  a. 玩家昵称    (" << data.nickname << ")" << endl;
        cout << "  b. 生命        (" << data.health << ")" << endl;
        cout << "  c. 力量        (" << data.strength << ")" << endl;
        cout << "  d. 体质        (" << data.constitution << ")" << endl;
        cout << "  e. 灵巧        (" << data.dexterity << ")" << endl;
        cout << "  f. 金钱数量    (" << data.money << ")" << endl;
        cout << "  g. 名声        (" << data.reputation << ")" << endl;
        cout << "  h. 魅力        (" << data.charm << ")" << endl;
        cout << "  i. 游戏累计时间(" << data.playTime << ")" << endl;
        cout << "  j. 移动速度    (" << (int)data.moveSpeed << ")" << endl;
        cout << "  k. 攻击速度    (" << (int)data.attackSpeed << ")" << endl;
        cout << "  l. 攻击范围    (" << (int)data.attackRange << ")" << endl;
        cout << "  m. 攻击力      (" << data.attack << ")" << endl;
        cout << "  n. 防御力      (" << data.defense << ")" << endl;
        cout << "  o. 敏捷度      (" << (int)data.agility << ")" << endl;
        cout << "  p. 智力        (" << (int)data.intelligence << ")" << endl;
        cout << "  q. 经验        (" << (int)data.experience << ")" << endl;
        cout << "  r. 等级        (" << (int)data.level << ")" << endl;
        cout << "  s. 魔法值      (" << data.magic << ")" << endl;
        cout << "  t. 魔法消耗值  (" << (int)data.magicConsumption << ")" << endl;
        cout << "  u. 魔法伤害力  (" << (int)data.magicDamage << ")" << endl;
        cout << "  v. 命中率      (" << (int)data.hitRate << ")" << endl;
        cout << "  w. 魔法防御力  (" << (int)data.magicDefense << ")" << endl;
        cout << "  x. 暴击率      (" << (int)data.criticalRate << ")" << endl;
        cout << "  y. 耐力        (" << (int)data.stamina << ")" << endl;
        cout << "--------------------------------------" << endl;
        cout << "  0.放弃修改" << endl;
        cout << "  1.存盘退出" << endl;
        cout << "--------------------------------------" << endl;
        cout << "请选择[a..y, 0..1] ";
#ifdef _WIN32
        choice = _getch();
#else
        choice = getchar();
        while (getchar() != '\n')
            ;
#endif
        cout << endl;
        bool inputSuccess = false;
        switch (choice)
        {
        case 'a':
            inputSuccess = getInput("玩家昵称", data.nickname, 15);
            break;
        case 'b':
            inputSuccess = getInput("生命", data.health, 0, 10000);
            break;
        case 'c':
            inputSuccess = getInput("力量", data.strength, 0, 10000);
            break;
        case 'd':
            inputSuccess = getInput("体质", data.constitution, 0, 8192);
            break;
        case 'e':
            inputSuccess = getInput("灵巧", data.dexterity, 0, 1024);
            break;
        case 'f':
            inputSuccess = getInput("金钱", data.money, 0, 100000000);
            break;
        case 'g':
            inputSuccess = getInput("名声", data.reputation, 0, 1000000);
            break;
        case 'h':
            inputSuccess = getInput("魅力", data.charm, 0, 1000000);
            break;
        case 'i':
            inputSuccess = getInput("游戏累计时间", data.playTime, 0, 10000000000000000ULL);
            break;
        case 'j':
            inputSuccess = getInput("移动速度", data.moveSpeed, 0, 100);
            break;
        case 'k':
            inputSuccess = getInput("攻击速度", data.attackSpeed, 0, 100);
            break;
        case 'l':
            inputSuccess = getInput("攻击范围", data.attackRange, 0, 100);
            break;
        case 'm':
            inputSuccess = getInput("攻击力", data.attack, 0, 2000);
            break;
        case 'n':
            inputSuccess = getInput("防御力", data.defense, 0, 2000);
            break;
        case 'o':
            inputSuccess = getInput("敏捷度", data.agility, 0, 100);
            break;
        case 'p':
            inputSuccess = getInput("智力", data.intelligence, 0, 100);
            break;
        case 'q':
            inputSuccess = getInput("经验", data.experience, 0, 100);
            break;
        case 'r':
            inputSuccess = getInput("等级", data.level, 0, 100);
            break;
        case 's':
            inputSuccess = getInput("魔法值", data.magic, 0, 10000);
            break;
        case 't':
            inputSuccess = getInput("魔法消耗", data.magicConsumption, 0, 100);
            break;
        case 'u':
            inputSuccess = getInput("魔法伤害力", data.magicDamage, 0, 100);
            break;
        case 'v':
            inputSuccess = getInput("命中率", data.hitRate, 0, 100);
            break;
        case 'w':
            inputSuccess = getInput("魔法防御力", data.magicDefense, 0, 100);
            break;
        case 'x':
            inputSuccess = getInput("暴击率", data.criticalRate, 0, 100);
            break;
        case 'y':
            inputSuccess = getInput("耐力", data.stamina, 0, 100);
            break;
        case '0':
            break;
        case '1':
        {

            gfile.seekp(0, ios::beg);
            gfile.write(reinterpret_cast<const char *>(&data), sizeof(gameData));
            if (gfile.fail())
            {
                cout << "写入文件失败" << endl;
                gfile.close();
                return -1;
            }
            inputSuccess = true;
            cout << endl;
        }
        break;
        default:
            break;
        }
        if (choice == '1')
        {
            modified = true;
            cout << endl;
            break;
        }
    } while (choice != '0');

    gfile.close();
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数允许带参数，不允许进行文件读写
***************************************************************************/
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printUsage(argv[0]);
        return -1;
    }
    if (strcmp(argv[1], "--read") == 0)
        return read();
    else if (strcmp(argv[1], "--modify") == 0)
        return modify();
    else
        return 1;
    return 0;
}