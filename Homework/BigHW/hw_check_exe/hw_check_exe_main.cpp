#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//按需加入需要的头文件 
#include "../include/txt_compare.h"
#include "../include/class_aat.h"
#include "../include/hw_check_exe.h"

#include<iomanip>

enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_CHECKNAME,
	OPT_ARGS_CHECKCFG_ONLY,
	OPT_ARGS_CFGFILE
};

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const full_procname)
{
	const int offset_len = 7;
	const char* procname = strrchr(full_procname, '\\');
	if (procname == NULL)
		procname = full_procname;

	ostringstream msg;
	/* 本程序的特殊示例 */
	msg << "e.g.  :" << endl;
	msg << setw(offset_len) << ' ' << procname << " --checkname 3-b3                 : 按配置文件[3-b3]组的设定检查exe的运行结果" << endl;
	msg << setw(offset_len) << ' ' << procname << " --checkname 3-b3 --checkcfg_only : 检查配置文件[3-b3]组的设定是否正确" << endl;
	msg << setw(offset_len) << ' ' << procname << " --checkname 3-b3 --debug trace   : 按配置文件[3-b3]组的设定检查exe的运行结果，打印所有调试信息" << endl;
	msg << endl;

	cout << msg.str() << endl;
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
	const string loglevel_define[] = { "warn", "info", "debug", "trace", "" };

	args_analyse_tools args[] = {
		args_analyse_tools("--help",		   ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--debug",		   ST_EXTARGS_TYPE::str_with_set_default, 1, 0, loglevel_define),
		args_analyse_tools("--checkname",	   ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--checkcfg_only", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--cfgfile",	   ST_EXTARGS_TYPE::str, 1, string("hw_check_exe.cfg")),
		args_analyse_tools()  //最后一个，用于结束
	};

	int cur_argc, ret = 0;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0)
	{
		//错误信息在函数中已打印
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}

	/* 对help做特殊处理 */
	if (args[OPT_ARGS_HELP].existed())
	{
		//只要有 --help，其它参数都忽略，显示帮助即可
		args_analyse_print(args);
		usage(argv[0]);
		return -1; //执行完成直接退出
	}

	if (args[OPT_ARGS_CHECKNAME].existed() != 1)
	{
		cout << endl << "V 2025.12.27" << endl << endl;
		usage(argv[0]);
		cout << "必须指定参数[" << args[OPT_ARGS_CHECKNAME].get_name() << "]" << endl;
		return -1;
	}
	if (args[OPT_ARGS_DEBUG].existed())
		args_analyse_print(args);

	/* 进入实际的功能调用，完成相应的功能 */
	string checkname = args[OPT_ARGS_CHECKNAME].get_string();
	string cfgfile = args[OPT_ARGS_CFGFILE].get_string();
	bool checkcfg_only = args[OPT_ARGS_CHECKCFG_ONLY].existed();
	bool debug = args[OPT_ARGS_DEBUG].existed();

	hw_check_exe hc(checkname, cfgfile, checkcfg_only, debug);
	
	hc.check();
	return 0;
}
