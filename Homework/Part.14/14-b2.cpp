/* 学号 姓名 班级 */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <ctime>

using namespace std;

#ifdef _WIN32
#define CLUB 'c'
#define DIAMOND 'd'
#define HEART 'h'
#define SPADE 's'
#else
#define CLUB 'C'
#define DIAMOND 'D'
#define HEART 'H'
#define SPADE 'S'
#endif

const char *CARD_TYPES[] = {"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

/***************************************************************************
  函数名称：print
  功    能：打印某个玩家的牌面信息，如果是地主，后面加标记
  输入参数：prompt-提示信息，landlord-是否是地主，player-玩家的牌
  返 回 值：0
  说    明：使用位运算解析玩家的牌
 ***************************************************************************/
int print(const char *prompt, const bool landlord, const unsigned long long player)
{
    /* 只允许定义不超过三个基本类型的简单变量，不能定义数组变量、结构体、string等 */
    int i;
    unsigned long long temp;
    bool firstCard = true;

    cout << prompt;

    for (i = 0; i < 54; i++)
    {
        temp = 1ULL << i; // 获取第i张牌的位掩码
        if (player & temp)
        {
            if (!firstCard)
                cout << " ";

            int val = i % 13 + 1; // 牌面值：1=A, 2=2, ..., 11=J, 12=Q, 13=K
            int suit = i / 13;    // 花色：0=Club, 1=Diamond, 2=Heart, 3=Spade, 4=小王, 5=大王

            if (suit < 4)
            {
                switch (suit)
                {
                case 0:
                    cout << CLUB;
                    break; // 梅花
                case 1:
                    cout << DIAMOND;
                    break; // 方块
                case 2:
                    cout << HEART;
                    break; // 红心
                case 3:
                    cout << SPADE;
                    break; // 黑桃
                }
                cout << CARD_TYPES[val];
            }
            else
            {
                if (val == 1)
                    cout << "RJ";
                else
                    cout << "BJ";
            }
            firstCard = false;
        }
    }

    if (landlord)
        cout << " (地主)";
    cout << endl;
    return 0;
}

/***************************************************************************
  函数名称：deal
  功    能：发牌（含键盘输入地主）
  输入参数：player-三个玩家的牌数组
  返 回 值：地主编号(0-2)
  说    明：轮流发牌，每发完一轮打印一次
 ***************************************************************************/
int deal(unsigned long long *player)
{
    /* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */
    int i, j, round;
    unsigned long long allCards = 0; // 用位表示所有牌
    int landlord;
    int cur;

    srand(static_cast<unsigned int>(time(NULL)));

    for (i = 0; i < 54; i++)
        allCards |= (1ULL << i);

    player[0] = player[1] = player[2] = 0;

    for (round = 0; round < 17; round++)
    {
        for (cur = 0; cur < 3; cur++)
        {
            int remainCards = 0;
            unsigned long long tempCards = allCards;
            for (i = 0; i < 54; i++)
                if (tempCards & (1ULL << i))
                    remainCards++;
            if (remainCards == 0)
                break;

            int randomIndex = rand() % remainCards;
            int cardIndex = -1;

            tempCards = allCards;
            for (i = 0; i <= randomIndex; i++)
            {
                for (j = cardIndex + 1; j < 54; j++)
                {
                    if (tempCards & (1ULL << j))
                    {
                        cardIndex = j;
                        tempCards &= ~(1ULL << j);
                        break;
                    }
                }
            }

            player[cur] |= (1ULL << cardIndex);
            allCards &= ~(1ULL << cardIndex);
        }
        cout << "第" << (round + 1) << "轮结束：" << endl;
        print("甲的牌：", false, player[0]);
        print("乙的牌：", false, player[1]);
        print("丙的牌：", false, player[2]);
    }
    do
    {
        cout << endl
             << "请选择一个地主[0-2]：" << endl;
        cin >> landlord;
    } while (landlord < 0 || landlord > 2);

    for (i = 0; i < 54; i++)
        if (allCards & (1ULL << i))
            player[landlord] |= (1ULL << i);
    return landlord;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，不准修改
 ***************************************************************************/
int main()
{
    unsigned long long player[3] = {0}; // 存放三个玩家的发牌信息
    int landlord;                       // 返回0-2表示哪个玩家是地主

    cout << "按回车键开始发牌";
    while (getchar() != '\n')
        ;

    landlord = deal(player);
    cout << "最终牌面：" << endl;
    print("甲的牌：", (landlord == 0), player[0]);
    print("乙的牌：", (landlord == 1), player[1]);
    print("丙的牌：", (landlord == 2), player[2]);

    return 0;
}