#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<sstream>
#include<vector>
#include <ctime>

#include"../include/txt_compare.h"
#include"../include/class_aat.h"
#include"../include/class_cft.h"
#include"../include/exe_running.h"
#include"../include/hw_check_exe.h"
#include"../include_mariadb_x86/mysql/mysql.h"

using namespace std;

// 数据库配置结构体
struct database_cfg {
	string db_host; // 数据库主机地址
	unsigned short db_port; // 数据库端口
	string db_name; // 数据库名称
	string db_username; // 数据库用户名
	string db_password;// 数据库密码
	string db_curr_term;//当前学期
	string db_cno_list;//课号列表
} db;

// 检查配置结构体
struct check_cfg {
	string exe_style; // exe类型：single/multi/none
	string namelist; // 学号名单文件

	string single_exe_dirname;
	string multi_exe_main_dirname;
	string multi_exe_sub_dirname;
	string stu_exe_name;
	string demo_exe_name;

	string cmd_style;
	string pipe_get_input_data_exe_name;
	string pipe_data_file;
	string redirection_data_dirname;

	int timeout; // 超时时间
	int max_output_len; // 最大输出长度

	int items_num;
	int items_begin;
	int items_end;

	vector<string> item_list;

	check_cfg()
		: exe_style("multi"),
		namelist("database"),
		single_exe_dirname(""),
		multi_exe_main_dirname(""),
		multi_exe_sub_dirname(""),
		demo_exe_name(""),
		stu_exe_name(""),
		cmd_style("normal"),
		pipe_get_input_data_exe_name(""),
		pipe_data_file(""),
		redirection_data_dirname(""),
		timeout(1),
		max_output_len(1024),
		items_num(0),
		items_begin(0),
		items_end(0)
	{
	}
}ck;

// 文本比较配置结构体
struct tc_cfg
{
	string tc_trim;
	int tc_lineskip;
	int tc_lineoffset;
	bool tc_ignoreblank;
	bool tc_not_ignore_linefeed;
	int tc_maxdiff;
	int tc_maxline;
	string tc_display;

	tc_cfg()
		: tc_trim("none"),
		tc_lineskip(0),
		tc_lineoffset(0),
		tc_ignoreblank(0),
		tc_not_ignore_linefeed(0),
		tc_maxdiff(0),
		tc_maxline(0),
		tc_display("none")
	{ 
	}
}tc;

// 学生信息结构体
struct stu_info
{
	string cno;     // 课号
	string sno;     // 学号
	string name;    // 姓名
	bool ok;		// 检查是否通过
};

// demo运行结果结构体
struct demo_result
{
	bool ok;
	bool timeout;
	string output;
};

// 学生运行状态结构体
struct stu_run_stat
{
	int ok;
	int err_timer_create;
	int err_pipe_open;
	int err_timer_start;
	int err_timeout;
	int err_output_limit;
	int err_dead_loop;
	int tc_pass;
	ostringstream items;

	stu_run_stat()
		: ok(0), err_timer_create(0), err_pipe_open(0),
		err_timer_start(0), err_timeout(0),
		err_output_limit(0), err_dead_loop(0),
		tc_pass(0) {
	}
};

// 将unsigned int类型的IP地址转换为字符串形式
static string uint_to_ipstr(unsigned int ip)
{
	ostringstream oss;
	oss << ((ip >> 24) & 0xFF) << "."
		<< ((ip >> 16) & 0xFF) << "."
		<< ((ip >> 8) & 0xFF) << "."
		<< (ip & 0xFF);
	return oss.str();
}

// 规范化组名格式
static string normalize_group_name(const string& name)
{
	if (name.empty())
		return name;

	if (name.front() == '[' && name.back() == ']')
		return name;

	return "[" + name + "]";
}

// 规范化目录格式，确保以路径分隔符结尾
static std::string normalize_dir(const std::string& dir)
{
	if (dir.empty())
		return dir;

	char last = dir[dir.size() - 1];

#ifdef _WIN32
	if (last == '\\' || last == '/')
		return dir;
	return dir + "\\";
#else
	if (last == '/')
		return dir;
	return dir + "/";
#endif
}

// 去除字符串首尾的空白字符
static void trim_string(string& s)
{
	size_t pos = s.find_first_not_of(" \t\r\n");
	if (pos == string::npos)
	{
		s.clear();
		return;
	}
	s.erase(0, pos);

	pos = s.find_last_not_of(" \t\r\n");
	if (pos != string::npos)
		s.erase(pos + 1);
}

// 获取当前时间字符串，格式为 "YYYY-MM-DD HH:MM:SS"
static string now_time()
{
	time_t t = time(nullptr);
	tm lt{};
#ifdef _WIN32
	localtime_s(&lt, &t);
#else
	lt = *localtime(&t);
#endif
	ostringstream os;
	os << put_time(&lt, "%Y-%m-%d %H:%M:%S");
	return os.str();
}

// 获取当前时间字符串，格式为 "YYYY-MM-DD-HH-MM-SS"，适合文件名使用
static string now_time_file()
{
	time_t t = time(nullptr);
	tm lt{};
#ifdef _WIN32
	localtime_s(&lt, &t);
#else
	lt = *localtime(&t);
#endif
	ostringstream os;
	os << put_time(&lt, "%Y-%m-%d-%H-%M-%S");
	return os.str();
}

// 判断字符串是否只包含数字字符
static bool is_digits(const string& s)
{
	if (s.empty())
		return false;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}

// 判断学号是否存在于学号列表中
static bool sno_exists(const vector<string>& snos, const string& sno)
{
	for (size_t i = 0; i < snos.size(); ++i)
	{
		if (snos[i] == sno)
			return true;
	}
	return false;
}

// 判断配置文件中是否存在指定组
static bool group_exists(config_file_tools& cfg, const string& group)
{
	vector<string> tmp;
	return cfg.get_all_item(group, tmp, false) > 0;
}

// 读取数据库配置
static void read_database_cfg(config_file_tools& cft, database_cfg& db, bool show)
{
	unsigned int ip;
	cft.item_get_ipaddr("[数据库]", "db_host", ip, 0xC0A80001);					// 数据库地址
	db.db_host = uint_to_ipstr(ip);
	int port;
	cft.item_get_int("[数据库]", "db_port", port, 0, 65535, 3306);				// 数据库端口
	db.db_port = static_cast<unsigned short>(port);
	cft.item_get_string("[数据库]", "db_name", db.db_name, "");					// 数据库名
	cft.item_get_string("[数据库]", "db_username", db.db_username, "");			// 数据库用户名
	cft.item_get_string("[数据库]", "db_passwd", db.db_password, "");			// 数据库密码
	cft.item_get_string("[数据库]", "db_curr_term", db.db_curr_term, "");		// 当前学期
	cft.item_get_string("[数据库]", "db_cno_list", db.db_cno_list, "");			// 课程号列表
	// 输出数据库配置信息
	if (show)
	{
		cout << "[数据库]：" << endl;
		cout << left << setw(14) << "  db_host" << " = " << db.db_host << endl;
		cout << left << setw(14) << "  db_port" << " = " << db.db_port << endl;
		cout << left << setw(14) << "  db_name" << " = " << db.db_name << endl;
		cout << left << setw(14) << "  db_username" << " = " << db.db_username << endl;
		cout << left << setw(14) << "  db_curr_term" << " = " << db.db_curr_term << endl;
		cout << left << setw(14) << "  db_cno_list" << " = " << db.db_cno_list << endl;
		cout << endl;
	}
}

// 读取文本比较配置
static void read_tc_cfg(config_file_tools& cft, const string& group_name, tc_cfg& tc, bool show)
{
	cft.item_get_string(group_name, "tc_trim", tc.tc_trim, "");							// trim方式 none/left/right/both
	cft.item_get_int(group_name, "tc_lineskip", tc.tc_lineskip, 0, 100, 0);				// 跳过行数
	cft.item_get_int(group_name, "tc_lineoffset", tc.tc_lineoffset, -100, 100, 0);		// 行偏移
	int ignoreblank; 
	cft.item_get_int(group_name, "tc_ignoreblank", ignoreblank, 0, 1, 0);				// 忽略空白
	tc.tc_ignoreblank = bool(ignoreblank); 
	int ignorelinefeed;
	cft.item_get_int(group_name, "tc_not_ignore_linefeed", ignorelinefeed, 0, 1, 0);	// 不忽略行结束符
	tc.tc_not_ignore_linefeed = bool(ignorelinefeed);
	cft.item_get_int(group_name, "tc_maxdiff", tc.tc_maxdiff, 0, 100, 0);				// 最大差异数
	cft.item_get_int(group_name, "tc_maxline", tc.tc_maxline, 0, 10000, 0);				// 最大比较行数
	cft.item_get_string(group_name, "tc_display", tc.tc_display, "");					// 显示方式 none/normal/detailed
}

// 输出配置信息
static void print_cfg(config_file_tools& cfg, const string& group_name, check_cfg& out_cfg, bool show)
{
	if (show)
	{
		cout << endl;
		cout << "====================================================================================================" << endl;
		cout << group_name << "配置信息如下：" << endl;
		cout << "====================================================================================================" << endl;

		bool show_db = show && out_cfg.namelist == "database" && out_cfg.exe_style != "none";
		read_database_cfg(cfg, db, show_db);
		read_tc_cfg(cfg, group_name, tc, show);
		cout << group_name << "：" << endl;

		int width;
		if (out_cfg.cmd_style == "pipe")
			width = 31;
		else if (out_cfg.cmd_style == "main_with_arguments")
			width = 25;
		else
			width = 27;
		cout << left << setw(width) << "  exe_style" << "= " << out_cfg.exe_style << endl;
		if(show_db)
			cout << left << setw(width) << "  name_list" << "= " << out_cfg.namelist << endl;
		if (out_cfg.exe_style == "single")
			cout << left << setw(width) << "  single_exe_dirname" << "= " << normalize_dir(out_cfg.single_exe_dirname) << endl;
		if(out_cfg.exe_style == "multi")
		{
			cout << left << setw(width) << "  multi_exe_main_dirname" << "= " << normalize_dir(out_cfg.multi_exe_main_dirname) << endl;
			cout << left << setw(width) << "  multi_exe_sub_dirname" << "= " << normalize_dir(out_cfg.multi_exe_sub_dirname) << endl;
		}

		if (out_cfg.exe_style != "none")
			cout << left << setw(width) << "  stu_exe_name" << "= " << out_cfg.stu_exe_name << endl;

		cout << left << setw(width) << "  demo_exe_name" << "= " << out_cfg.demo_exe_name << endl;
		cout << left << setw(width) << "  cmd_style" << "= " << out_cfg.cmd_style << endl;
		cout << left << setw(width) << "  max_output_len" << "= " << out_cfg.max_output_len << endl;
		cout << left << setw(width) << "  timeout" << "= " << out_cfg.timeout << endl;

		if (out_cfg.cmd_style == "pipe")
		{
			cout << left << setw(width) << "  pipe_get_input_data_exe_name" << "= " << out_cfg.pipe_get_input_data_exe_name << endl;
			cout << left << setw(width) << "  pipe_data_file" << "= " << out_cfg.pipe_data_file << endl;
		}
		else if (out_cfg.cmd_style == "redirection")
			cout << left << setw(width) << "  redirection_data_dirname" << "= " << normalize_dir(out_cfg.redirection_data_dirname) << endl;

		cout << endl;
		cout << left << setw(width) << "  tc_trim" << "= " << tc.tc_trim << endl;
		cout << left << setw(width) << "  tc_lineskip" << "= " << tc.tc_lineskip << endl;
		cout << left << setw(width) << "  tc_lineoffset" << "= " << tc.tc_lineoffset << endl;
		cout << left << setw(width) << "  tc_ignoreblank" << "= " << tc.tc_ignoreblank << endl;
		cout << left << setw(width) << "  tc_not_ignore_linefeed" << "= " << tc.tc_not_ignore_linefeed << endl;
		cout << left << setw(width) << "  tc_maxdiff" << "= " << tc.tc_maxdiff << endl;
		cout << left << setw(width) << "  tc_maxline" << "= " << tc.tc_maxline << endl;
		cout << left << setw(width) << "  tc_display" << "= " << tc.tc_display << endl;
		cout << endl;

		cout << left << setw(width) << "  items_num" << "= " << out_cfg.items_num << endl;
		cout << left << setw(width) << "  items_begin" << "= " << out_cfg.items_begin << endl;
		cout << left << setw(width) << "  items_end" << "= " << out_cfg.items_end << endl;

		for (size_t i = 0; i < out_cfg.item_list.size(); ++i)
		{
			ostringstream key;
			key << "  item_name_" << (i + 1);
			if(out_cfg.cmd_style == "pipe")
				cout << left << setw(width) << key.str() << "= " << normalize_group_name(out_cfg.item_list[i]) << endl;
			else
				cout << left << setw(width) << key.str() << "= " << out_cfg.item_list[i] << endl;
		}
		cout << "====================================================================================================" << endl;
		cout << endl;
	}
}

// 获取项目前缀字符串
static string get_item_prefix(const string& cmd_style)
{
	if (cmd_style == "pipe")
		return "item_gname";
	if (cmd_style == "redirection")
		return "item_fname";
	if (cmd_style == "main_with_arguments")
		return "item_args";
	return "";
}

static string gen_status(const string& buf, const int sum)
{
	string gen;
	if (sum > 0)
		gen += (buf + "=" + to_string(sum) + " ");
	return gen;
}

// 判断文件是否存在
static bool file_exists(const string& path)
{
	return ACCESS(path.c_str(), F_OK) == 0;
}

// 构建项列表
void hw_check_exe::build_item_list(config_file_tools& cfg, const string& group_name, check_cfg& out_cfg)
{
	out_cfg.item_list.clear();
	for (int i = out_cfg.items_begin; i <= out_cfg.items_end; ++i)
	{
		ostringstream key;

		key << get_item_prefix(out_cfg.cmd_style);
		key << "_";
		key << i;

		string val;
		
		if (cfg.item_get_raw(group_name, key.str(), val) > 0)
		{
			trim_string(val);
			out_cfg.item_list.push_back(val);
		}
	}
}

// 递归读取组配置，处理include指令
void hw_check_exe::read_group_recursive(config_file_tools& cfg, const string& group_name, check_cfg& out_cfg)
{
	string inc;
	check_cfg inc_cfg = out_cfg;
	int ret = cfg.item_get_string(group_name, "include", inc);
	if (ret > 0 && !inc.empty())
		read_group_recursive(cfg, inc, inc_cfg);
	cfg.item_get_string(group_name, "exe_style", out_cfg.exe_style, "multi");
	cfg.item_get_string(group_name, "name_list", out_cfg.namelist, inc_cfg.namelist);
	cfg.item_get_string(group_name, "single_exe_dirname", out_cfg.single_exe_dirname, inc_cfg.single_exe_dirname);
	cfg.item_get_string(group_name, "multi_exe_main_dirname", out_cfg.multi_exe_main_dirname, inc_cfg.multi_exe_main_dirname);
	cfg.item_get_string(group_name, "multi_exe_sub_dirname", out_cfg.multi_exe_sub_dirname, inc_cfg.multi_exe_sub_dirname);
	cfg.item_get_string(group_name, "stu_exe_name", out_cfg.stu_exe_name, inc_cfg.stu_exe_name);
	string inc_demo_exe_name;
	cfg.item_get_raw(group_name, "demo_exe_name", out_cfg.demo_exe_name);
	trim_string(out_cfg.demo_exe_name);
	if(out_cfg.demo_exe_name.empty())
		out_cfg.demo_exe_name = inc_cfg.demo_exe_name;
	cfg.item_get_string(group_name, "cmd_style", out_cfg.cmd_style, inc_cfg.cmd_style);
	cfg.item_get_string(group_name, "pipe_get_input_data_exe_name",		out_cfg.pipe_get_input_data_exe_name,		inc_cfg.pipe_get_input_data_exe_name);
	cfg.item_get_string(group_name, "pipe_data_file",		out_cfg.pipe_data_file,		inc_cfg.pipe_data_file);
	cfg.item_get_string(group_name, "redirection_data_dirname", out_cfg.redirection_data_dirname, inc_cfg.redirection_data_dirname);
	if (!out_cfg.redirection_data_dirname.empty() && out_cfg.redirection_data_dirname.back() != '/' && out_cfg.redirection_data_dirname.back() != '\\') 
		out_cfg.redirection_data_dirname += '\\';
	else if (out_cfg.redirection_data_dirname.empty())
		out_cfg.redirection_data_dirname = "\\";
	cfg.item_get_int(group_name, "timeout", out_cfg.timeout, 1, 3600, inc_cfg.timeout);
	cfg.item_get_int(group_name, "max_output_len", out_cfg.max_output_len, 1, 65536, inc_cfg.max_output_len);
	cfg.item_get_int(group_name, "items_num", out_cfg.items_num, 1, 1024, inc_cfg.items_num);
	cfg.item_get_int(group_name, "items_begin", out_cfg.items_begin, 1, out_cfg.items_num, inc_cfg.items_begin);
	cfg.item_get_int(group_name, "items_end", out_cfg.items_end, out_cfg.items_begin, out_cfg.items_num, inc_cfg.items_end);
	string gn = (inc.empty() ? group_name : inc);
	build_item_list(cfg, gn, out_cfg);
	read_tc_cfg(cfg_, gn, tc, false);
	print_cfg(cfg, group_name, out_cfg, checkcfg_only_);	
}

// 构造函数
hw_check_exe::hw_check_exe(
	const string& checkname,
	const string& cfgfile,
	bool checkcfg_only,
	bool debug)
	: checkname_(checkname),
	cfgfile_(cfgfile),
	checkcfg_only_(checkcfg_only),
	debug_(debug),
	cfg_(cfgfile_)
{
}

// 初始化配置
int hw_check_exe::init_cfg()
{
	if (cfg_.is_read_succeeded() == 0)
	{
		cerr << endl << "[--严重错误--] 无法打开配置文件[" << cfgfile_ << "]." << endl;
		return -1;
	}

	string group_name = "[" + checkname_ + "]";
	vector<string> items;
	int item_num = cfg_.get_all_item(group_name, items, false);

	if (item_num <= 0)
	{
		cerr << endl << "[--严重错误--] 配置文件[" << cfgfile_ << "]中的组[" << checkname_ << "]不存在 / 为空." << endl;
		return -1;
	}
	read_database_cfg(cfg_, db, false);
	read_group_recursive(cfg_, group_name, ck);
	return 0;
}

// 从数据库获取学生名单
static int get_student_list_from_db(const database_cfg& db, vector<stu_info>& stu_list, string& err_msg)
{
	stu_list.clear();
	err_msg.clear();

	MYSQL* mysql = NULL;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = NULL;

	mysql = mysql_init(NULL);
	if (mysql == NULL)
	{
		err_msg = "MySQL初始化失败.";
		return -1;
	}

	if (mysql_real_connect(mysql, db.db_host.c_str(), db.db_username.c_str(), db.db_password.c_str(), db.db_name.c_str(), db.db_port, NULL, 0) == NULL)
	{
		ostringstream dblnk;
		dblnk << db.db_host << "/" << db.db_port << "/" << db.db_name << "/" << db.db_username;
		err_msg = now_time() + string(" 连接数据库(") + dblnk.str() + ")错误([" + to_string(mysql_errno(mysql)) + "]" + mysql_error(mysql) + ")，";
		mysql_close(mysql);
		return -1;
	}

	mysql_set_character_set(mysql, "gbk");

	ostringstream sql;
	sql << "call proc_hwapp_get_stulist_from_view_student_cno(" << "'" << db.db_curr_term << "'," << "'" << db.db_cno_list << "'," << "'sno'," << "NULL" << ")";

	if (mysql_query(mysql, sql.str().c_str()) != 0)
	{
		err_msg = string("mysql_query failed: ") + mysql_error(mysql);
		mysql_close(mysql);
		return -1;
	}

	result = mysql_store_result(mysql);
	if (result == NULL)
	{
		err_msg = string("mysql_store_result failed: ") + mysql_error(mysql);
		mysql_close(mysql);
		return -1;
	}

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		stu_info s;
		if (row[1] != NULL)
			s.sno = row[1];
		if (row[2] != NULL)
			s.name = row[2];
		if (row[10] != NULL)
			s.cno = row[10];
		stu_list.push_back(s);
	}

	mysql_free_result(result);
	mysql_close(mysql);
	return 0;
}

// 检查学生信息是否合法
static bool checkstuinfo(stu_info& stu, string& err)
{
	stu.ok = true;
	err.clear();

	if (stu.sno.size() != 7 || !is_digits(stu.sno))
	{
		err = "学号[" + stu.sno + "]不符合要求";
		stu.ok = false;
	}

	if (!((stu.cno.size() == 8 || stu.cno.size() == 13) && is_digits(stu.cno)))
	{
		err = "课号[" + stu.cno + "]不符合要求";
		stu.ok = false;
	}

	return stu.ok;
}

// 从文件获取学生名单
static int get_students_from_file(const string& namelist,	vector<stu_info>& students,	string& err)
{
	students.clear();
	err.clear();
	if (namelist.empty())
	{
		err = "名单文件路径为空";
		return -1;
	}

	ifstream fin(namelist.c_str(), ios::in);
	if (!fin.is_open())
	{
		err = "无法打开名单文件：" + namelist;
		return -1;
	}

	vector<string> seen_snos;
	string line;
	int lineno = 0;

	while (getline(fin, line))
	{
		++lineno;

		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		if (line.empty())
			continue;

		if(line[0] == '#')
			continue;
		istringstream iss(line);

		stu_info stu;
		stu.ok = true;
		if (!(iss >> stu.cno >> stu.sno >> stu.name))
		{
			err = "不符合要求";
			cerr << now_time() << " 行：" << line << err << endl;
			continue;
		}

		string err;
		checkstuinfo(stu, err);

		if (sno_exists(seen_snos, stu.sno))
		{
			cerr << now_time() << " 课号=" << stu.cno << " 学号=" << stu.sno << " 姓名=" << stu.name << " 重复." << endl;
			stu.ok = false;
		}
		else
		{
			seen_snos.push_back(stu.sno);
			if (!stu.ok)
				cerr << now_time() << " 行：\"" << line << "\" 中" << err << endl;
		}
		students.push_back(stu);
	}

	fin.close();

	if (students.empty())
	{
		err = "名单文件为空或未读取到有效学生记录";
		return -1;
	}

	return 0;
}

// 输出学生名单(测试用)
static void print_student_list(const vector<stu_info>& students)
{
	time_t now = time(NULL);
	tm* t = localtime(&now);

	char timebuf[64];
	strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", t);

	cout << timebuf << " 学生答案生成情况" << endl;
	cout << "======================================================================" << endl;
	for (size_t i = 0; i < students.size(); ++i)
		cout << "序号：" << setw(3) << (i + 1) << " 学号：" << setw(8) << students[i].sno << " / 姓名：" << setw(6) << students[i].name << " / 课号：" << students[i].cno << endl;
	cout << "======================================================================" << endl;
	cout << endl;
	now = time(NULL);
	t = localtime(&now);

	strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", t);
	cout << timebuf << endl;
	cout << endl;
}

// 运行参考答案exe
istream* demo_output_;
void hw_check_exe::run_demo(vector<demo_result>&dr)
{
	dr.clear();
	dr.resize(ck.items_end - ck.items_begin + 1);
	exe_running runner;
	exe_run_result result;
	int ok = RUN_RUNTIME_ERROR;
	int okcnt = 0;
	ostringstream run_status;
	string start_time = now_time();
	stu_run_stat stat;
	for (int i = ck.items_begin; i <= ck.items_end; ++i)
	{
		ok = RUN_RUNTIME_ERROR;
		if (ck.cmd_style == "normal")
			ok = runner.run_normal(ck.demo_exe_name, result, ck.timeout, ck.max_output_len);
		else if (ck.cmd_style == "pipe")
			ok = runner.run_pipe(ck.demo_exe_name, ck.pipe_get_input_data_exe_name, ck.pipe_data_file, ck.item_list.empty() ? "" : ck.item_list[i - ck.items_begin], result, ck.timeout, ck.max_output_len);
		else if (ck.cmd_style == "redirection")
			ok = runner.run_redirection(ck.demo_exe_name, ck.redirection_data_dirname + "\\" + ck.item_list[i - ck.items_begin], result, ck.timeout, ck.max_output_len);
		else if (ck.cmd_style == "main_with_arguments")
			ok = runner.run_args(ck.demo_exe_name, ck.item_list[i - ck.items_begin], result, ck.timeout, ck.max_output_len);
		switch (ok)
		{
		case RUN_OK:
			stat.ok++;
			break;
		case RUN_TIMER_CREATE_FAIL:
			stat.err_timer_create++;
			break;
		case RUN_PIPE_OPEN_FAIL:
			stat.err_pipe_open++;
			break;
		case RUN_TIMER_START_FAIL:
			stat.err_timer_start++;
			break;
		case RUN_TIMEOUT:
			stat.err_timeout++;
			break;
		case RUN_OUTPUT_OVERFLOW:
			stat.err_output_limit++;
			break;
		case RUN_RUNTIME_ERROR:
			stat.err_dead_loop++;
			break;
		default:
			break;
		}

		demo_result& dr_item = dr[i - ck.items_begin];
		dr_item.ok = ok;
		dr_item.output = result.output;
	}
	string end_time = now_time();
	run_status << gen_status("正确运行", stat.ok)
		<< gen_status("定时器创建失败", stat.err_timer_create)
		<< gen_status("管道方式打开失败", stat.err_pipe_open)
		<< gen_status("启动定时器失败", stat.err_timer_start)
		<< gen_status("超时", stat.err_timeout)
		<< gen_status("超过输出上限", stat.err_output_limit)
		<< gen_status("死循环", stat.err_dead_loop);
	cout << now_time() << " 参考答案生成情况" << endl;
	cout << "======================================================================" << endl;
	cout << "参考exe文件：" << ck.demo_exe_name << endl;
	cout << "测试运行情况：" << run_status.str() << endl;
	cout << "时间：" << start_time << " - " << end_time << endl;
	cout << "======================================================================" << endl;
	cout << endl;

	if (stat.ok != ck.items_num)
		cerr << "[--严重错误--] " << now_time() << " 参考程序[" << ck.demo_exe_name << "]运行有错，请检查，加--debug xx可以看到更多信息." << endl;
}

// 运行学生exe
istream* stu_output_;
int hw_check_exe::run_student(const string& stu_exe_path, int item, string& stu_output)
{
	stu_output.clear();
	exe_running runner;
	exe_run_result result;
	int ok = RUN_OK;

	if (ck.cmd_style == "normal")
		ok = runner.run_normal(stu_exe_path, result, ck.timeout, ck.max_output_len);
	else if (ck.cmd_style == "pipe")
		ok = runner.run_pipe(stu_exe_path, ck.pipe_get_input_data_exe_name, ck.pipe_data_file, ck.item_list[item - ck.items_begin], result, ck.timeout, ck.max_output_len);
	else if (ck.cmd_style == "redirection")
		ok = runner.run_redirection(stu_exe_path, ck.redirection_data_dirname + "\\" + ck.item_list[item - ck.items_begin], result, ck.timeout, ck.max_output_len);
	else if (ck.cmd_style == "main_with_arguments")
		ok = runner.run_args(stu_exe_path, ck.item_list[item - ck.items_begin], result, ck.timeout, ck.max_output_len);
	else
		return RUN_RUNTIME_ERROR;

	
	stu_output = result.output;
	return ok;
}

bool hw_check_exe::check_item_continuity(config_file_tools& cfg, const check_cfg& ck, string& cfgerr)
{
	if (ck.cmd_style == "normal")
		return true;

	string prefix = get_item_prefix(ck.cmd_style);
	if (prefix.empty())
		return true;

	bool error = false;

	for (int i = 1; i <= ck.items_num; ++i)
	{
		ostringstream key;
		key << prefix << "_" << i;

		string val;
		string group_name = "[" + checkname_ + "]";
		string inc;
		cfg.item_get_string(group_name, "include", inc);
		if (cfg.item_get_raw(group_name, key.str(), val) <= 0 && cfg.item_get_raw(inc, key.str(), val) <= 0)
		{
			cfgerr += "缺少配置项 [" + key.str() + "]\n";
			error = true;
			continue;
		}

		if (ck.cmd_style == "pipe")
		{
			if (val.empty())
			{
				cfgerr += key.str() + " 的值为空\n";
				error = true;
			}
		}
		else if (ck.cmd_style == "redirection")
		{
			string fullpath = ck.redirection_data_dirname;
			if (!fullpath.empty() && fullpath[fullpath.size() - 1] != '\\' && fullpath[fullpath.size() - 1] != '/')				
				fullpath += "\\";
			trim_string(val);
			fullpath += val;
			if (!file_exists(fullpath))
			{
				cfgerr += "重定向数据文件不存在: [" + fullpath + "]\n";
				error = true;
			}
		}
		else if (ck.cmd_style == "main_with_arguments")
			continue;
	}
	return !error;
}


int hw_check_exe::check_(std::vector<stu_info>& stk)
{
	bool flag = false; // 是否存在配置错误
	string cfgerr;
	if (ck.exe_style != "none") // 仅在需要运行学生程序时检查学生名单
	{
		if (ck.namelist == "database")
		{
			string err;
			if (get_student_list_from_db(db, stk, err) != 0)
			{
				cerr << err << "程序终止" << endl;
				return -1;
			}
		}
		else
		{
			string err;
			if (get_students_from_file(ck.namelist, stk, err) != 0)
			{
				cfgerr += "name_list 指定的文件[" + ck.namelist + "]不存在.\n";
				flag = true;
			}
		}
	}
	string inc;
	cfg_.item_get_string("[" + checkname_ + "]", "include", inc);
	if (!group_exists(cfg_, inc) && !inc.empty())
	{
		cfgerr += "配置文件[" + cfgfile_ + "]中的组" + inc + "不存在/为空\n";
		flag = true;
	}

	if (ck.exe_style != "single" && ck.exe_style != "multi" && ck.exe_style != "none")
	{
		cfgerr += "exe_style的值不是none/single/multi\n";
		flag = true;
	}
	if (!file_exists(ck.demo_exe_name))
	{
		cfgerr += "demo_exe_name 指定的文件[" + ck.demo_exe_name + "]不存在.\n";
		flag = true;
	}
	if (ck.cmd_style != "normal" && ck.cmd_style != "pipe" && ck.cmd_style != "redirection" && ck.cmd_style != "main_with_arguments")
	{
		cfgerr += "cmd_style的值不是normal/pipe/redirection/main_with_arguments\n";
		flag = true;
	}
	if (ck.cmd_style == "pipe")
	{
		if (!file_exists(ck.pipe_data_file))
		{
			cfgerr += "pipe_data_file 指定的文件[" + ck.pipe_data_file + "]不存在.\n";
			flag = true;
		}
		if (!file_exists(ck.pipe_get_input_data_exe_name))
		{
			cfgerr += "pipe_get_input_data_exe_name 指定的文件[" + ck.pipe_get_input_data_exe_name + "]不存在.\n";
			flag = true;
		}
	}
	if(tc.tc_trim != "none" && tc.tc_trim != "left" && tc.tc_trim != "right" && tc.tc_trim != "all")
	{
		cfgerr += "tc_trim的值不是none/left/right/all\n";
		flag = true;
	}
	if(tc.tc_display != "none" && tc.tc_display != "normal" && tc.tc_display != "detailed")
	{
		cfgerr += "tc_display的值不是none/normal/detailed\n";
		flag = true;
	}
	if (ck.items_num <= 0)
	{
		cfgerr += "items_num[1]最小为1\n";
		flag = true;
	}
	else if (ck.items_end - ck.items_begin + 1 != ck.items_num)
	{
		cfgerr += "items_begin / items_end 与 items_num 不匹配\n";
		flag = true;
	}
	if (!check_item_continuity(cfg_, ck, cfgerr))
	{
		flag = true;
	}
	if (flag)
	{
		cerr << endl;
		cerr<<"[--严重错误--] 配置文件存在下列的错误：" << endl;
		cerr << cfgerr;
		return -1;
	}
	else
		return 0;
}

void hw_check_exe::check()
{
	string check_start_time = now_time_file(); // 获取检查开始时间，用于结果文件命名
	if (checkcfg_only_) // 仅检查配置文件
	{
		init_cfg();
		return;
	}
	if (init_cfg() != 0) // 初始化配置失败
		return;
	vector<stu_info> students;
	vector<demo_result> demo_results;
	if (check_(students) != 0)
		return;
	demo_results.resize(ck.items_end - ck.items_begin + 1);
	run_demo(demo_results);
	// 若只测demo，结束
	if (ck.exe_style == "none")
		return;
	string namelist_tag = (ck.namelist == "database") ? "database" : "txt";
	// 生成结果表格文件名
	ostringstream fname;
	fname << "check-result-" << "2451317" << "-" << check_start_time << "-" << ck.exe_style << "-" << ck.cmd_style << "-" << namelist_tag << "-" << ck.stu_exe_name << ".xls";
	ofstream ofs(fname.str().c_str(), ios::out | ios::trunc);
	if (!ofs)
		return ;
	// 打印结果表头部信息
	ofs << "exe_style\t" << ck.exe_style << "\n";
	ofs << "cmd_style\t" << ck.cmd_style << "\n";
	ofs << "name_list\t" << ck.namelist << "\n";
	ofs << "stu_exe_name\t" << ck.stu_exe_name << "\n";
	ofs << "start_time\t" << check_start_time << "\n";
	ofs << "\n";
	// 打印结果表头
	ofs << "序号\t课号\t学号\t姓名\t正确运行\t定时器创建失败\t管道方式打开失败\t启动定时器失败\t超时\t超过输出上限\t死循环\tTC通过总数";
	for (int i = ck.items_begin; i <= ck.items_end; ++i)
	{
		if (ck.cmd_style == "pipe")
			ofs << "\t" << normalize_group_name(ck.item_list[i - ck.items_begin]);
		else
			ofs << "\t" << ck.item_list[i - ck.items_begin];
	}
	ofs << "\n";
	// 逐个学生测试
	int seq = 0;
	for (size_t si = 0; si < students.size(); ++si)
	{
		const stu_info& stu = students[si];
		int runned_cnt = 0;
		string begin_time = now_time();
		string end_time;
		ostringstream out;			//控制台提示信息流
		ostringstream run_status;	//运行状态信息流
		ostringstream correct_cnt;	// 逐项正确项流
		if(!stu.ok)
			continue;
		// 输出学生信息
		++seq;
		out << now_time() << endl;
		out << "======================================================================" << endl;
		out << "序号：" << seq << " 学号：" << stu.sno << " / 姓名：" << stu.name << " / 课号：" << stu.cno << endl;
		ofs << seq << "\t=text(\"" << stu.cno << "\", \"#\")\t" << stu.sno << "\t" << stu.name << "\t";
		// 学生exe文件路径
		string stu_exe_path;
		if (ck.exe_style == "single")
			stu_exe_path = ck.single_exe_dirname + "\\" + stu.sno + "-" + stu.cno + "-" + ck.stu_exe_name;
		else if (ck.exe_style == "multi")
			stu_exe_path = ck.multi_exe_main_dirname + "\\" + stu.sno + "-" + stu.cno + "\\" + ck.multi_exe_sub_dirname + "\\" + ck.stu_exe_name;
		// 检查学生exe文件是否存在
		if (!file_exists(stu_exe_path))
		{
			// 生成不存在的exe文件名
			string exe_name;
			if (ck.exe_style == "single")
				exe_name = stu.sno + "-" + stu.cno + "-" + ck.stu_exe_name;
			else if (ck.exe_style == "multi")
				exe_name = ck.stu_exe_name;
			// 输出文件不存在信息
			out << "EXE文件：" << exe_name << "不存在" << endl;
			out << "======================================================================" << endl;
			cout << out.str() << endl;
			ofs << "/\t/\t/\t/\t/\t/\t/" << "\t0";
			for (int item = ck.items_begin; item <= ck.items_end; ++item)
				ofs << "\t0";
			ofs << "\n";
			continue;
		}
		// 逐项运行学生程序并进行比较
		stu_run_stat stat;
		for (int item = ck.items_begin; item <= ck.items_end; ++item)
		{
			// 创建参考答案输出流和学生答案输出流
			stringstream demo_output_ss;
			demo_output_ss.str(demo_results[item - ck.items_begin].output);
			demo_output_ = &demo_output_ss;
			string stu_output;
			stringstream stu_output_ss;
			stu_output_ss.str(stu_output);
			stu_output_ = &stu_output_ss;
			// 运行学生程序
			int rc = run_student(stu_exe_path, item, stu_output);
			stu_output_ss.str("");
			stu_output_ss.clear();
			stu_output_ss << stu_output;
			// 判断错误代码
			switch (rc)
			{
			case RUN_OK:
				stat.ok++;
				break;
			case RUN_TIMER_CREATE_FAIL:
				stat.err_timer_create++;
				break;
			case RUN_PIPE_OPEN_FAIL:
				stat.err_pipe_open++;
				break;
			case RUN_TIMER_START_FAIL:
				stat.err_timer_start++;
				break;
			case RUN_TIMEOUT:
				stat.err_timeout++;
				break;
			case RUN_OUTPUT_OVERFLOW:
				stat.err_output_limit++;
				break;
			case RUN_RUNTIME_ERROR:
				stat.err_dead_loop++;
				break;
			default:
				break;
			}
			// 进行文本比较
			txt_compare cmp(*demo_output_, *stu_output_, tc.tc_trim, tc.tc_display, tc.tc_lineskip, tc.tc_lineoffset, tc.tc_maxdiff, tc.tc_maxline, tc.tc_ignoreblank, tc.tc_not_ignore_linefeed, debug_);
			// 文本比较结果
			int ans = cmp.compare();
			if (ans == 0)
				stat.tc_pass++;
			correct_cnt << (ans == 0 ? 1 : 0);
			stat.items << "\t" << (ans == 0 ? "1" : "0");
		}
		// 输出结果写入文件
		ofs << stat.ok << "\t" << stat.err_timer_create << "\t" << stat.err_pipe_open << "\t" << stat.err_timer_start << "\t" << stat.err_timeout << "\t"
			<< stat.err_output_limit << "\t" << stat.err_dead_loop << "\t" << stat.tc_pass << stat.items.str() << "\n";
		// 输出运行情况
		run_status << gen_status("正确运行", stat.ok) 
				<< gen_status("定时器创建失败", stat.err_timer_create) 
				<< gen_status("管道方式打开失败", stat.err_pipe_open)
				<< gen_status("启动定时器失败", stat.err_timer_start) 
				<< gen_status("超时", stat.err_timeout) 
				<< gen_status("超过输出上限", stat.err_output_limit) 
				<< gen_status("死循环", stat.err_dead_loop);
		// 输出结果到控制台
		correct_cnt << 0;
		end_time = now_time();
		out << "测试运行情况：" << run_status.str() << endl;
		out << "逐项正确性：" << correct_cnt.str() << endl;
		out << "tc正确项数：" << stat.tc_pass << endl;
		out << "时间：" << begin_time << " - " << end_time << endl;
		out << "======================================================================" << endl;
		cout << out.str() << endl;
	}
	// 输出结果文件已生成
	cout << now_time() << " 检查结果文件[" << fname.str() << "]已生成." << endl;
	ofs << "\n";
	ofs.close();
}