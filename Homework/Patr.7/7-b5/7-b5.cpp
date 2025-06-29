// 2451317 冯久恒 计算机

/* 允许按需加入系统的宏定义、需要的头文件等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "read_stulist.h"
using namespace std;

#define MAX_FILENAME_LEN		512	//定义文件名的最大长度

/* stu_metge 类存放每个学生的信息，包括学号、姓名、其它需要的私有信息，已有内容不准动，可加入符合限制要求的新内容 */
class stu_merge {
private:
	int  stu_no;					//学号
	char stu_name[MAX_NAME_LEN];    //姓名
	int  stu_choose;				//选课情况

	friend class stu_list;
	/* 允许按需加入private数据成员、成员函数以及其它需要的内容 */

public:
	//本类不允许定义任何的公有数据成员及成员函数
};

/* stu_list 类整个选课信息，已有内容不准动，可加入符合限制要求的新内容 */
class stu_list {
private:
	student list_round_1[MAX_STU_NUM];	//第一轮选课的学生名单（不排序、不去重）
	int list_num_1;						//第一轮选课的学生人数

	student list_round_2[MAX_STU_NUM];	//第二轮选课的学生名单（不排序、不去重）
	int list_num_2;						//第二轮选课的学生人数

	stu_merge list_merge[MAX_STU_NUM];	//合并后的学生名单（去重，按升序排列）
	int list_merge_num;					//合并后的学生人数（目前不打印，但可用于内部管理，如果不需要，也不要删除）

	/* 允许按需加入private数据成员和成员函数
	   注意，不允许加入array / set / map / vector等STL容器 */

public:
	stu_list();										//构造函数，按需完成初始化功能，如果不需要，保留空函数即可
	int read(const char* filename, const int round);	//从文件中读入选课信息，round为1/2，表示选课轮次
	int print(const char* prompt = NULL);				//打印最终的选课名单

	/* 允许按需加入其它public成员函数（提示：合并、去重、排序等）
	   不允许定义公有的数据成员
	   不允许在成员函数中使用array / set / map / vector等STL容器 */
	bool is_in_list(const student* list, int size, int stu_no) 
	{
		for (int i = 0; i < size; i++) 
			if (list[i].no == stu_no)
				return true;
		return false;
	}
	void merge_and_sort() 
	{
		student all[MAX_STU_NUM * 2];
		int total = 0;
		for (int i = 0; i < list_num_1; i++)
			all[total++] = list_round_1[i];
		for (int i = 0; i < list_num_2; i++)
			all[total++] = list_round_2[i];
		for (int i = 0; i < total - 1; i++) 
		{
			int min_idx = i;
			for (int j = i + 1; j < total; j++) 
				if (all[j].no < all[min_idx].no)
					min_idx = j;
			if (min_idx != i)
				swap(all[i], all[min_idx]);
		}

		list_merge_num = 0;
		for (int i = 0; i < total; i++) 
		{
			if (i > 0 && all[i].no == all[i - 1].no)
				continue;
			stu_merge& stu = list_merge[list_merge_num];
			stu.stu_no = all[i].no;
			strcpy(stu.stu_name, all[i].name);

			bool _1 = is_in_list(list_round_1, list_num_1, stu.stu_no);
			bool _2 = is_in_list(list_round_2, list_num_2, stu.stu_no);

			if (_1 && _2)
				stu.stu_choose = 3;
			else if (_1)
				stu.stu_choose = 1;
			else
				stu.stu_choose = 2;
			list_merge_num++;
		}
	}
};

/* --- 下面可以给出stu_merge/stu_list两个类的成员函数的体外实现 --- */


/***************************************************************************
  函数名称：
  功    能：从文件中读入选课信息，round为1/2，表示选课轮次
  输入参数：
  返 回 值：
  说    明：构造函数，按需完成初始化功能，如果不需要，保留空函数即可
***************************************************************************/
stu_list::stu_list()
{
	list_num_1 = 0;
	list_num_2 = 0;
	list_merge_num = 0;
}

/***************************************************************************
  函数名称：
  功    能：演示静态链接库的使用，本函数中调用静态链接库中的预置函数
  输入参数：
  返 回 值：
  说    明：本函数不需要修改 
***************************************************************************/
int stu_list::read(const char* filename, const int round)
{
	int ret = 0;
	/* 读取第1/2轮的选课名单并打印 */
	switch (round) {
		case 1:
			this->list_num_1 = read_stulist(filename, this->list_round_1, MAX_STU_NUM);
			if (this->list_num_1 > 0)
				print_stulist("第一轮选课名单：", this->list_round_1, this->list_num_1);
			else
				ret = -1;
			break;
		case 2:
			this->list_num_2 = read_stulist(filename, this->list_round_2, MAX_STU_NUM);
			if (this->list_num_2 > 0)
				print_stulist("第二轮选课名单：", this->list_round_2, this->list_num_2);
			else
				ret = -1;
			break;
		default:
			ret = -1;
			break;
	}

	return ret;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：打印最终的选课名单
***************************************************************************/
int stu_list::print(const char* prompt)
{
	if(prompt)
		cout << prompt << endl;
	int name_len = -1;
	for (int i = 0; i < list_merge_num; i++)
	{
		int l = strlen(list_merge[i].stu_name);
		name_len = max(name_len, l);
	}
	cout << "=================================================" << endl;
	cout << left << setw(7) << " 序号  ";
	cout << left << setw(7) << "学号";
	cout << "  ";
	cout << left << setw(name_len) << "姓名";
	cout << "  ";
	cout << left << setw(6) << "第一轮  ";
	cout << left << setw(6) << "第二轮 ";
	cout << endl;
	cout << "=================================================" << endl;
	for (int i = 0; i < list_merge_num; i++)
	{
		cout << " ";
		cout << left << setw(4) << i + 1;
		cout << "  ";
		cout << left << setw(7) << list_merge[i].stu_no;
		cout << "  ";
		cout << left << setw(name_len) << list_merge[i].stu_name;
		cout << "  ";
		//cout << list_merge[i].stu_choose;
		if (list_merge[i].stu_choose == 3)
		{
			cout << left << setw(6) << "Y";
			cout << "  ";
			cout << left << setw(6) << "Y";
		}
		else if (list_merge[i].stu_choose == 1)
		{
			cout << left << setw(6) << "Y";
			cout << "  ";
			cout << left << setw(6) << "退课";
		}
		else if (list_merge[i].stu_choose == 2)
		{
			cout << left << setw(6) << "/";
			cout << "  ";
			cout << left << setw(6) << "补选";
		}
		cout << endl;
	}
	cout << "=================================================" << endl;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	char file1[MAX_FILENAME_LEN], file2[MAX_FILENAME_LEN];

	cout << "请输入前一轮选课的数据文件 : ";
	gets_s(file1); //cin不能读有空格的文件

	cout << "请输入后一轮选课的数据文件 : ";
	gets_s(file2);

	stu_list list;

	/* 读入数据 */
	if (list.read(file1, 1) < 0)
		return -1;
	if (list.read(file2, 2) < 0)
		return -1;

	/* 处理数据 */
	list.merge_and_sort();

	/* 打印 */
	list.print("最终选课名单");

	return 0;
}

