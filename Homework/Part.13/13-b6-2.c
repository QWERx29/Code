// 学号 姓名 班级
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#endif
// 根据需要可加入其它头文件

// 此处为示例，允许修改结构体名称，允许修改结构体中的成员内容，要求sizeof必须是64
#pragma pack(push, 1) // problem
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
   1、所有新增的函数，均不允许定义新的 FILE* 并进行打开/读/写/关闭等操作
   2、上述限制同样适用于main函数
*/
void displayData(const struct gameData *data)
{
    printf("          玩家昵称：%s\n", data->nickname);
    printf("            生命值：%d\n", data->health);
    printf("            力量值：%d\n", data->strength);
    printf("            体质值：%d\n", data->constitution);
    printf("            灵巧值：%d\n", data->dexterity);
    printf("            金钱值：%d\n", data->money);
    printf("            名声值：%d\n", data->reputation);
    printf("            魅力值：%d\n", data->charm);
    printf("游戏累计时间(us)值：%d\n", data->playTime);
    printf("        移动速度值：%d\n", (int)data->moveSpeed);
    printf("        攻击速度值：%d\n", (int)data->attackSpeed);
    printf("        攻击范围值：%d\n", (int)data->attackRange);
    printf("          攻击力值：%d\n", data->attack);
    printf("          防御力值：%d\n", data->defense);
    printf("          敏捷度值：%d\n", (int)data->agility);
    printf("            智力值：%d\n", (int)data->intelligence);
    printf("            经验值：%d\n", (int)data->experience);
    printf("            等级值：%d\n", (int)data->level);
    printf("            魔法值：%d\n", data->magic);
    printf("        消耗魔法值：%d\n", (int)data->magicConsumption);
    printf("      魔法伤害力值：%d\n", (int)data->magicDamage);
    printf("          命中率值：%d\n", (int)data->hitRate);
    printf("      魔法防御力值：%d\n", (int)data->magicDefense);
    printf("          暴击率值：%d\n", (int)data->criticalRate);
    printf("            耐力值：%d\n", (int)data->stamina);
    printf("\n");
}

void getString(const char *prompt, char *value, size_t maxLen)
{
    char input[100];
    printf("%s，当前值=%s，请输入 : ", prompt, value);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    if (fgets(input, sizeof(input), stdin) == NULL)
        return;
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0';
    if (strlen(input) > maxLen)
        input[maxLen] = '\0';
    strcpy(value, input);
}

void getUShort(const char *prompt, unsigned short *value, unsigned short minVal, unsigned short maxVal)
{
    int input;
    printf("\n");
    while (1)
    {
        printf("%s，当前值=%hu，范围[%hu..%hu]，请输入 : ", prompt, value, minVal, maxVal);
        if (scanf("%d", &input) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            continue;
        }
        else if (input < minVal || input > maxVal)
        {
            printf("非法的%s值：%d\n", prompt, input);
            continue;
        }
        else
            break;
    }
    *value = (unsigned short)input;
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void getUInt(const char *prompt, unsigned int *value, unsigned int minVal, unsigned int maxVal)
{
    int input;
    printf("\n");
    while (1)
    {
        printf("%s，当前值=%u，范围[%u..%u]，请输入 : ", prompt, value, minVal, maxVal);
        if (scanf("%d", &input) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            continue;
        }
        else if (input < minVal || input > maxVal)
        {
            printf("非法的%s值：%d\n", prompt, input);
            continue;
        }
        else
            break;
    }
    *value = (unsigned int)input;
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void getULL(const char *prompt, unsigned long long *value, unsigned long long minVal, unsigned long long maxVal)
{
    unsigned long long input;
    printf("\n");
    while (1)
    {
        printf("%s，当前值=%llu，范围[%llu..%llu]，请输入 : ", prompt, value, minVal, maxVal);
        if (scanf("%llu", &input) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            continue;
        }
        else if (input < minVal || input > maxVal)
        {
            printf("非法的%s值：%d\n", prompt, input);
            continue;
        }
        else
            break;
    }
    *value = input;
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void getUChar(const char *prompt, unsigned char *value, unsigned char minVal, unsigned char maxVal)
{
    unsigned int input;
    while (1)
    {
        printf("%s，当前值=%u，范围[%u..%u]，请输入 : ", prompt, value, minVal, maxVal);
        if (scanf("%llu", &input) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            continue;
        }
        else if (input < minVal || input > maxVal)
        {
            printf("非法的%s值：%d\n", prompt, input);
            continue;
        }
        else
            break;
    }
    *value = (unsigned char)input;
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void printUsage(const char *fileName)
{
    printf("usage : %s --modify | --read\n", fileName);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次fopen、一次fread（因为包含错误处理，允许多次fclose）
***************************************************************************/
int read()
{
    /* 本函数中只允许定义一个 FILE* */
    FILE *fp;
    struct gameData data;
    /* 文件打开，具体要求为：
       1、要求以读方式打开，打开方式***自行指定
       2、除本次fopen外，本函数其它地方不允许再出现fopen/freopen  */
    fp = fopen("game.dat", "rb");
    if (fp == NULL)
    {
        printf("无法打开文件game.dat\n");
        return -1;
    }
    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 fread(***, 1, sizeof(demo), fp);
    */
    if (fread(&data, sizeof(struct gameData), 1, fp) != 1)
    {
        printf("读取文件失败\n");
        fclose(fp);
        return -1;
    }

    displayData(&data);
    fclose(fp);
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次open、一次read、一次write（因为包含错误处理，允许多次fclose）
***************************************************************************/
int modify()
{
    /* 本函数中只允许定义一个 FILE* */
    FILE *fp;
    struct gameData data;
    /* 文件打开，具体要求为：
       1、要求以读写方式打开，打开方式***自行指定
       2、除本次fopen外，本函数其它地方不允许再出现fopen/freopen  */
    fp = fopen("game.dat", "r+b");
    if (fp == NULL)
    {
        printf("无法打开文件game.dat\n");
        return -1;
    }
    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 fread(***, 1, sizeof(demo), fp);
             只允许用一次性写入64字节的方法将***的内容写入game.dat中（缓冲区名称、结构体名称自行指定）
                 fwrite(***, 1, sizeof(demo), fp);
    */
    if (fread(&data, sizeof(struct gameData), 1, fp) != 1)
    {
        printf("读取文件game.dat失败\n");
        fclose(fp);
        return -1;
    }

    char choice;
    do
    {
        printf("--------------------------------------\n");
        printf(" 游戏存档文件修改工具\n");
        printf("--------------------------------------\n");
        printf("  a. 玩家昵称    (%s)\n", data.nickname);
        printf("  b. 生命        (%d)\n", data.health);
        printf("  c. 力量        (%d)\n", data.strength);
        printf("  d. 体质        (%d)\n", data.constitution);
        printf("  e. 灵巧        (%d)\n", data.dexterity);
        printf("  f. 金钱数量    (%d)\n", data.money);
        printf("  g. 名声        (%d)\n", data.reputation);
        printf("  h. 魅力        (%d)\n", data.charm);
        printf("  i. 游戏累计时间(%d)\n", data.playTime);
        printf("  j. 移动速度    (%d)\n", (int)data.moveSpeed);
        printf("  k. 攻击速度    (%d)\n", (int)data.attackSpeed);
        printf("  l. 攻击范围    (%d)\n", (int)data.attackRange);
        printf("  m. 攻击力      (%d)\n", data.attack);
        printf("  n. 防御力      (%d)\n", data.defense);
        printf("  o. 敏捷度      (%d)\n", (int)data.agility);
        printf("  p. 智力        (%d)\n", (int)data.intelligence);
        printf("  q. 经验        (%d)\n", (int)data.experience);
        printf("  r. 等级        (%d)\n", (int)data.level);
        printf("  s. 魔法值      (%d)\n", data.magic);
        printf("  t. 魔法消耗值  (%d)\n", (int)data.magicConsumption);
        printf("  u. 魔法伤害力  (%d)\n", (int)data.magicDamage);
        printf("  v. 命中率      (%d)\n", (int)data.hitRate);
        printf("  w. 魔法防御力  (%d)\n", (int)data.magicDefense);
        printf("  x. 暴击率      (%d)\n", (int)data.criticalRate);
        printf("  y. 耐力        (%d)\n", (int)data.stamina);
        printf("--------------------------------------\n");
        printf("  0.放弃修改\n");
        printf("  1.存盘退出\n");
        printf("--------------------------------------\n");
        printf("请选择[a..y, 0..1] ");
#ifdef _WIN32
        choice = _getch();
#else
        choice = getchar();
        while (getchar() != '\n')
            ;
#endif
        printf("\n");
        switch (choice)
        {
        case 'a':
            getString("玩家昵称", data.nickname, 15);
            break;
        case 'b':
            getUShort("生命", &data.health, 0, 10000);
            break;
        case 'c':
            getUShort("力量", &data.strength, 0, 10000);
            break;
        case 'd':
            getUShort("体质", &data.constitution, 0, 8192);
            break;
        case 'e':
            getUShort("灵巧", &data.dexterity, 0, 1024);
            break;
        case 'f':
            getUInt("金钱", &data.money, 0, 100000000);
            break;
        case 'g':
            getUInt("名声", &data.reputation, 0, 1000000);
            break;
        case 'h':
            getUInt("魅力", &data.charm, 0, 1000000);
            break;
        case 'i':
            getULL("游戏累计时间", &data.playTime, 0, 10000000000000000ULL);
            break;
        case 'j':
            getUChar("移动速度", &data.moveSpeed, 0, 100);
            break;
        case 'k':
            getUChar("攻击速度", &data.attackSpeed, 0, 100);
            break;
        case 'l':
            getUChar("攻击范围", &data.attackRange, 0, 100);
            break;
        case 'm':
            getUShort("攻击力", &data.attack, 0, 2000);
            break;
        case 'n':
            getUShort("防御力", &data.defense, 0, 2000);
            break;
        case 'o':
            getUChar("敏捷度", &data.agility, 0, 100);
            break;
        case 'p':
            getUChar("智力", &data.intelligence, 0, 100);
            break;
        case 'q':
            getUChar("经验", &data.experience, 0, 100);
            break;
        case 'r':
            getUChar("等级", &data.level, 0, 100);
            break;
        case 's':
            getUShort("魔法值", &data.magic, 0, 10000);
            break;
        case 't':
            getUChar("魔法消耗", &data.magicConsumption, 0, 100);
            break;
        case 'u':
            getUChar("魔法伤害力", &data.magicDamage, 0, 100);
            break;
        case 'v':
            getUChar("命中率", &data.hitRate, 0, 100);
            break;
        case 'w':
            getUChar("魔法防御力", &data.magicDefense, 0, 100);
            break;
        case 'x':
            getUChar("暴击率", &data.criticalRate, 0, 100);
            break;
        case 'y':
            getUChar("耐力", &data.stamina, 0, 100);
            break;
        case '0':
            break;
        case '1':
        {
            fseek(fp, 0, SEEK_SET);
            if (fwrite(&data, sizeof(struct gameData), 1, fp) != 1)
            {
                printf("写入文件失败\n");
                fclose(fp);
                return -1;
            }
            printf("\n");
        }
        break;
        default:
            break;
        }
        if (choice == '1')
        {
            printf("\n");
            break;
        }
    } while (choice != '0');

    fclose(fp);
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
