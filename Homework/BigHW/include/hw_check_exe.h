#pragma once
#include<string>
#include<vector>
#include "../include/class_cft.h"

#ifdef _WIN32
#include <io.h>      // _access
#define ACCESS _access
#define F_OK 0
#else
#include <unistd.h> // access
#define ACCESS access
#endif


using namespace std;

// 声明 check_cfg 结构体
struct check_cfg;
struct stu_info;
struct demo_result;


class hw_check_exe
{
public:

	hw_check_exe(const string& checkname,
		const string& cfgfile,
		bool checkcfg_only,
		bool debug);

	void read_group_recursive(config_file_tools& cfg, const string& group_name, check_cfg& out_cfg);
	void build_item_list(config_file_tools& cfg, const string& group_name, check_cfg& out_cfg);
	int init_cfg();
	void run_demo(vector<demo_result>& dr);

	bool check_item_continuity(config_file_tools& cfg, const check_cfg& ck, string& cfgerr);
	int check_(std::vector<stu_info>& stk);

	int run_student(const string& stu_exe_path, int item, string& stu_output);


	void check();

private:
	string checkname_;
	string cfgfile_;
	bool   checkcfg_only_;
	bool   debug_;

	config_file_tools cfg_;
};

