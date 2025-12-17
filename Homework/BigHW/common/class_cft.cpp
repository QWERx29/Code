
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream> 
#include <string.h>
/* 添加自己需要的头文件，注意限制 */
#include "../include/class_cft.h"
using namespace std;

static string erase_space(const string str)
{
	string s = str;
	while (!s.empty() && (s.front() == ' ' || s.front() == '\t'))
		s.erase(s.begin());
	while (!s.empty() && (s.back() == ' ' || s.back() == '\t'))
		s.pop_back();
	return s;
}
static string get_gname(const char* const name)
{
	if (name == nullptr)
		return "";
	string s = name;
	s = erase_space(s);
	if (s.size() >= 2 && s.front() == '[' && s.back() == ']')
	{
		string t = erase_space(s.substr(1, s.size() - 2));
		t = erase_space(t);
		return t;
	}
	return s;
}

void config_file_tools::init(const char* const _cfgname, const enum BREAK_CTYPE _ctype)
{
	break_type_ = _ctype;
	read_success = false;
	is_empty = true;
	groups_.clear();

	if (_cfgname == nullptr)
		return;

	string cfgname = _cfgname;
	if (cfgname.size() == 0)
		return;

	FILE* fp = fopen(cfgname.c_str(), "rb");
	if (!fp)
		return;

	char buf[MAX_LINE + 5];

	// 初始空组
	groups_.push_back(CFT_Group());
	groups_.back().name = "";

	while (true)
	{
		if (!fgets(buf, MAX_LINE + 5, fp))
			break;

		if (strlen(buf) >= MAX_LINE) 
		{
			fclose(fp);
			read_success = false;
			return;
		}

		string line = buf;

		// 去掉 \r\n
		while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
			line.pop_back();

		// 截断注释
		size_t p;
		p = line.find("//"); if (p != string::npos) line = line.substr(0, p);
		p = line.find('#');  if (p != string::npos) line = line.substr(0, p);
		p = line.find(';');  if (p != string::npos) line = line.substr(0, p);

		// trim
		auto trim = [&](string& s) 
			{
			int L = 0;
			while (L < (int)s.size() && (s[L] == ' ' || s[L] == '\t')) L++;
			int R = (int)s.size() - 1;
			while (R >= L && (s[R] == ' ' || s[R] == '\t')) R--;
			if (L > R) { s = ""; return; }
			s = s.substr(L, R - L + 1);
			};

		trim(line);
		if (line.empty())
			continue;

		// 判断是否是组名
		if (line[0] == '[' && line.back() == ']') 
		{
			string g = line.substr(1, line.size() - 2);
			trim(g);

			bool found = false;
			for (size_t i = 0; i < groups_.size(); ++i)
				if (groups_[i].name == g)
					found = true;

			if (!found) 
			{
				CFT_Group G;
				G.name = g;
				groups_.push_back(G);
			}
			continue;
		}

		// 是项 → 放入当前组
		CFT_Group& grp = groups_.back();
		CFT_Item item;
		item.raw = line;
		grp.items.push_back(item);
		is_empty = false;
	}

	fclose(fp);
	read_success = true;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const char* const _cfgname, const enum BREAK_CTYPE _ctype)
{
	init(_cfgname, _ctype);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const string& _cfgname, const enum BREAK_CTYPE _ctype)
{
	init(_cfgname.c_str(), _ctype);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::~config_file_tools()
{
}

/***************************************************************************
  函数名称：
  功    能：判断读配置文件是否成功
  输入参数：
  返 回 值：true - 成功，已读入所有的组/项
		   false - 失败，文件某行超长/文件全部是注释语句
  说    明：
***************************************************************************/
bool config_file_tools::is_read_succeeded() const
{
	if(!read_success)
		return false;
	if (is_empty)
		return false;
	return true;
}

/***************************************************************************
  函数名称：
  功    能：返回配置文件中的所有组
  输入参数：vector <string>& ret : vector 中每项为一个组名
  返 回 值：读到的组的数量（简单配置文件的组数量为1，组名为"）
  说    明：
***************************************************************************/
int config_file_tools::get_all_group(vector <string>& ret)
{
	ret.clear();
	if (!is_read_succeeded())
		return 0;
	if (groups_.empty())
		return 0;
	for (size_t i = 0; i < groups_.size(); ++i)
		ret.push_back("["+groups_[i].name+"]");
	return static_cast<int>(ret.size());
}

/***************************************************************************
  函数名称：
  功    能：查找指定组的所有项并返回项的原始内容
  输入参数：const char* const group_name：组名
		   vector <string>& ret：vector 中每项为一个项的原始内容
		   const bool is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：项的数量，0表示空
  说    明：
***************************************************************************/
int config_file_tools::get_all_item(const char* const group_name, vector <string>& ret, const bool is_case_sensitive)
{
	ret.clear();
	if (group_name == nullptr)
		return 0;
	if (!is_read_succeeded())
		return 0;
	string _gname = get_gname(group_name);
	for (size_t i = 0; i < groups_.size(); ++i)
	{
		const string& gname = groups_[i].name;
		bool gmatch = false;
		if (is_case_sensitive)
		{
			if (gname == _gname)
				gmatch = true;
		}
		else
		{
			if (gname.size() == _gname.size())
			{
				bool same = true;
				for (size_t k = 0; k < gname.size(); ++k)
				{
					if (tolower(gname[k]) != tolower(_gname[k]))
					{
						same = false;
						break;
					}
				}
				if (same) gmatch = true;
			}
		}
		if (!gmatch)
			continue;
		for (auto& it : groups_[i].items)
			ret.push_back(it.raw);
		return (int)ret.size();
	}
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::get_all_item(const string& group_name, vector <string>& ret, const bool is_case_sensitive)
{
	return get_all_item(group_name.c_str(), ret, is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的原始内容（=后的所有字符，string方式）
  输入参数：const char* const group_name
		   const char* const item_name
		   string &ret
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_raw(const char* const group_name, const char* const item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	ret.clear();
	if (group_name == nullptr || item_name == nullptr)
		return 0;
	if (!is_read_succeeded())
		return 0;
	string _gname = get_gname(group_name);
	string _iname = erase_space(item_name);
	for (size_t gi = 0; gi < groups_.size(); ++gi) 
	{
		const string& gname = groups_[gi].name;
		bool gmatch = false;
		if (group_is_case_sensitive) 
		{
			if (gname == _gname)
				gmatch = true;
		}
		else 
		{
			if (gname.size() == _gname.size())
			{
				bool same = true;
				for (size_t k = 0; k < gname.size(); ++k) 
				{
					if (tolower(gname[k]) != tolower(_gname[k])) {same = false;	break;}
				}
				if (same) gmatch = true;
			}
		}
		if (!gmatch) 
			continue;
		for (size_t ii = 0; ii < groups_[gi].items.size(); ++ii) 
		{
			const string& rawline = groups_[gi].items[ii].raw;
			size_t pos = string::npos;
			if (break_type_ == BREAK_CTYPE::Equal)
				pos = rawline.find('=');
			else 
			{
				for (size_t p = 0; p < rawline.size(); ++p) 
				{
					if (rawline[p] == ' ' || rawline[p] == '\t') 
					{
						pos = p;
						break;
					}
				}
			}
			if (pos == string::npos)
				continue;
			string left = rawline.substr(0, pos);
			left = erase_space(left);
			string right = rawline.substr(pos + 1);
			bool item_match = false;
			if (item_is_case_sensitive) 
			{
				if (left == _iname)
					item_match = true;
			}
			else 
			{
				if (left.size() == strlen(item_name)) 
				{
					bool same = true;
					for (size_t k = 0; k < left.size(); ++k) 
					{
						if (tolower(left[k]) != tolower(_iname[k])) {same = false;break;}
					}
					if (same) item_match = true;
				}
			}
			if (!item_match) continue;
			ret = right;
			return 1;
		}
	}
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_raw(const string& group_name, const string& item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_raw(group_name.c_str(), item_name.c_str(), ret, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：1 - 该项的项名存在
		   0 - 该项的项名不存在
  说    明：
***************************************************************************/
int config_file_tools::item_get_null(const char* const group_name, const char* const item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	// 参数检查
	if (group_name == nullptr || item_name == nullptr)
		return 0;

	// 文件读取失败
	if (!is_read_succeeded())
		return 0;

	// ----------- 匹配组名 -----------
	for (size_t gi = 0; gi < groups_.size(); ++gi) 
	{

		const string& gname = groups_[gi].name;
		bool gmatch = false;

		// 组名大小写敏感
		if (group_is_case_sensitive) 
		{
			if (gname == group_name)
				gmatch = true;
		}
		else 
		{
			// 组名大小写不敏感
			size_t len1 = gname.size();
			size_t len2 = strlen(group_name);
			if (len1 == len2) 
			{
				bool same = true;
				for (size_t k = 0; k < len1; ++k) 
				{
					char c1 = gname[k];
					char c2 = group_name[k];
					if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
					if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
					if (c1 != c2) { same = false; break; }
				}
				if (same) gmatch = true;
			}
		}

		if (!gmatch) continue;

		// ----------- 在该组中查找项名 -----------
		for (size_t ii = 0; ii < groups_[gi].items.size(); ++ii) {

			const string& rawline = groups_[gi].items[ii].raw;

			// 查找分隔符
			size_t pos = string::npos;

			if (break_type_ == BREAK_CTYPE::Equal) {
				pos = rawline.find('=');
			}
			else {
				// 空格/tab 作为分隔符
				for (size_t p = 0; p < rawline.size(); ++p) {
					if (rawline[p] == ' ' || rawline[p] == '\t') {
						pos = p;
						break;
					}
				}
			}

			// 无分隔符 → 该项不存在（item_get_null 不认为它是项）
			if (pos == string::npos)
				continue;

			// 左侧是项名（构造函数已做 trim）
			string left = rawline.substr(0, pos);

			// ----------- 匹配项名 -----------
			bool imatch = false;

			if (item_is_case_sensitive) {
				if (left == item_name)
					imatch = true;
			}
			else {
				if (left.size() == strlen(item_name)) {
					bool same = true;
					for (size_t k = 0; k < left.size(); ++k) {
						char c1 = left[k];
						char c2 = item_name[k];
						if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
						if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
						if (c1 != c2) { same = false; break; }
					}
					if (same) imatch = true;
				}
			}

			if (imatch)
				return 1; // 找到该项
		}
	}

	return 0; // 未找到
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_null(const string& group_name, const string& item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_null(group_name.c_str(), item_name.c_str(), group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   char& value                                ：读到的char的值（返回1时可信，返回0则不可信）
		   const char* const choice_set = nullptr     ：合法的char的集合（例如："YyNn"表示合法输入为Y/N且不分大小写，该参数有默认值nullptr，表示全部字符，即不检查）
		   const char def_value = DEFAULT_CHAR_VALUE  ：读不到/读到非法的情况下的默认值，该参数有默认值DEFAULT_CHAR_VALUE，分两种情况
															当值是   DEFAULT_CHAR_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_CHAR_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：1 - 取到正确值
			   未取到值/未取到正确值，设置了缺省值（包括设为缺省值）
		   0 - 未取到（只有为未指定默认值的情况下才会返回0）
  说    明：
***************************************************************************/
int config_file_tools::item_get_char(const char* const group_name, const char* const item_name, char& value,
						const char* const choice_set, const char def_value,
						const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	value = DEFAULT_CHAR_VALUE;
	string raw;
	int ret = this->item_get_raw(group_name, item_name, raw, group_is_case_sensitive, item_is_case_sensitive);
	if (ret == 0) // 项不存在
	{
		if (def_value == DEFAULT_CHAR_VALUE)
			return 0;
		value = def_value;
		return 1;
	}
	istringstream iss(raw);
	char ch;
	
	if (!(iss >> ch)) // 提取失败
	{
		//if (def_value == DEFAULT_CHAR_VALUE)
		//	return 0;
		value = def_value;
		cout << "ch=" << ch << endl;
		//return 1;
	}
	
	// 提取成功，检查 choice_set
	if (choice_set != nullptr)
	{
		bool ok = false;
		for (const char* p = choice_set; *p; ++p)
		{
			if (*p == ch)
			{
				ok = true;
				break;
			}
		}
		if (!ok) // 不在合法集合内
		{
			if (def_value == DEFAULT_CHAR_VALUE)
				return 0;
			value = def_value;
			return 1;
		}
	}
	value = ch;
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_char(const string& group_name, const string& item_name, char& value,
						const char* const choice_set, const char def_value, 
						const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_char(group_name.c_str(), item_name.c_str(), value, choice_set, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为int型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   int& value                                 ：读到的int的值（返回1时可信，返回0则不可信）
		   const int min_value = INT_MIN              : 期望数据范围的下限，默认为INT_MIN
		   const int max_value = INT_MAX              : 期望数据范围的上限，默认为INT_MAX
		   const int def_value = DEFAULT_INT_VALUE    ：读不到/读到非法的情况下的默认值，该参数有默认值 DEFAULT_INT_VALUE，分两种情况
															当值是   DEFAULT_INT_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_INT_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_int(const char* const group_name, const char* const item_name, int& value,
							const int min_value, const int max_value, const int def_value,
							const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	string raw;
	int ret = this->item_get_raw(group_name, item_name, raw, group_is_case_sensitive, item_is_case_sensitive);
	if (ret == 0) // 项不存在
	{
		if (def_value == DEFAULT_INT_VALUE)
			return 0;   // 无默认值 → 返回 0（value 不可信）
		value = def_value;
		return 1;       // 有默认值 → value=默认值，返回 1
	}
	istringstream iss(raw);
	int tmp;
	iss >> tmp;
	if (iss.fail())
	{
		if (def_value == DEFAULT_INT_VALUE)
			return 0;
		value = def_value;
		return 1;
	}
	if (tmp < min_value || tmp > max_value)
	{
		if (def_value == DEFAULT_INT_VALUE)
			return 0;   // 无默认值 → 失败
		value = def_value;
		return 1;
	}
	value = tmp;
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_int(const string& group_name, const string& item_name, int& value,
						const int min_value, const int max_value, const int def_value, 
						const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_int(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为double型
  输入参数：const char* const group_name                  ：组名
		   const char* const item_name                   ：项名
		   double& value                                 ：读到的int的值（返回1时可信，返回0则不可信）
		   const double min_value = __DBL_MIN__          : 期望数据范围的下限，默认为INT_MIN
		   const double max_value = __DBL_MAX__          : 期望数据范围的上限，默认为INT_MAX
		   const double def_value = DEFAULT_DOUBLE_VALUE ：读不到/读到非法的情况下的默认值，该参数有默认值DEFAULT_DOUBLE_VALUE，分两种情况
																当值是   DEFAULT_DOUBLE_VALUE 时，返回0（值不可信）
																当值不是 DEFAULT_DOUBLE_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false     : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false      : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_double(const char* const group_name, const char* const item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	value = def_value;

	// ---------- 第 1 步：读取原始项值 ----------
	string raw;
	int ret = item_get_raw(group_name, item_name, raw, group_is_case_sensitive, item_is_case_sensitive);

	if (ret == 0) 
	{
		// 未取到项
		if (def_value == DEFAULT_DOUBLE_VALUE)
			return 0;               // 不可信 → 返回 0
		else
			return 1;               // 使用默认值 → 返回 1
	}

	// ---------- 第 2 步：istringstream 解析 double ----------
	istringstream iss(raw);
	double tmp = 0.0;

	if (!(iss >> tmp)) 
	{
		// 解析失败
		if (def_value == DEFAULT_DOUBLE_VALUE)
			return 0;               // 不可信
		else
			return 1;               // 使用默认值
	}

	// ---------- 第 3 步：成功读取 ----------
	value = tmp;
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_double(const string& group_name, const string& item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_double(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char * / char []型
  输入参数：const char* const group_name                  ：组名
		   const char* const item_name                   ：项名
		   char *const value                             ：读到的C方式的字符串（返回1时可信，返回0则不可信）
		   const int str_maxlen                          ：指定要读的最大长度（含尾零）
																如果<1则返回空串(不是DEFAULT_CSTRING_VALUE，虽然现在两者相同，但要考虑default值可能会改)
																如果>MAX_STRLEN 则上限为MAX_STRLEN
		   const char* const def_str                     ：读不到情况下的默认值，该参数有默认值DEFAULT_CSTRING_VALUE，分两种情况
																当值是   DEFAULT_CSTRING_VALUE 时，返回0（值不可信）
																当值不是 DEFAULT_CSTRING_VALUE 时，令value=def_value并返回1（注意，不是直接=）
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：1、为简化，未对\"等做转义处理，均按普通字符
		   2、含尾零的最大长度为str_maxlen，调用时要保证有足够空间
		   3、如果 str_maxlen 超过了系统预设的上限 MAX_STRLEN，则按 MAX_STRLEN 取
***************************************************************************/
int config_file_tools::item_get_cstring(const char* const group_name, const char* const item_name, char* const value,
						const int str_maxlen, const char* const def_value, 
						const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	if (value == nullptr || str_maxlen == 0)
		return 0;
	value[0] = '\0';
	string raw;
	int ret = this->item_get_raw(group_name, item_name, raw, group_is_case_sensitive, item_is_case_sensitive);
	if (ret == 0)
	{
		vector<string> all;
		this->get_all_item(group_name, all, group_is_case_sensitive);
		for (size_t i = 0; i < all.size(); ++i)
		{
			const string& line = all[i];
			if (line.rfind(item_name, 0) == 0)
			{
				string remainder = line.substr(strlen(item_name));
				remainder = erase_space(remainder);
				size_t p = remainder.find_first_of("=\t ");
				if (p != string::npos)
				{
					remainder = remainder.substr(p + 1);
					remainder = erase_space(remainder);
				}
				raw = remainder;
				ret = 1;
				break;
			}
		}
	}
	if (ret == 0) 
	{
		if (def_value == nullptr)
			return 0; // 未指定默认值 → 不可信
		else 
		{
			strncpy_s(value, str_maxlen, def_value, _TRUNCATE);
			value[str_maxlen - 1] = '\0';
			return 1;
		}
	}
	istringstream iss(raw);
	string token;
	iss >> token;
	if (iss.fail()) 
	{
		if (def_value == nullptr)
			return 0;
		else 
		{
			strncpy_s(value, str_maxlen, def_value, _TRUNCATE);
			value[str_maxlen - 1] = '\0';
			return 1;
		}
	}
	strncpy_s(value, str_maxlen, raw.c_str(), _TRUNCATE);
	value[ str_maxlen - 1] = '\0';
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_cstring(const string& group_name, const string& item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)

{
	/* 本函数已实现 */
	return item_get_cstring(group_name.c_str(), item_name.c_str(), value, str_maxlen, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为 string 型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   string &value                              ：读到的string方式的字符串（返回1时可信，返回0则不可信）
		   const string &def_value                    ：读不到情况下的默认值，该参数有默认值DEFAULT_STRING_VALUE，分两种情况
															当值是   DEFAULT_STRING_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_STRING_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：为简化，未对\"等做转义处理，均按普通字符
***************************************************************************/
int config_file_tools::item_get_string(const char* const group_name, const char* const item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	//value.clear();
	string raw;
	int ret = item_get_raw(group_name, item_name, raw, group_is_case_sensitive, item_is_case_sensitive);
	if (ret == 0) 
	{
		if (def_value == DEFAULT_STRING_VALUE)
			return 0;
		value = def_value;
		return 1;
	}
	istringstream iss(raw);
	string token;
	iss >> token;
	if (iss.fail())
	{
		if (def_value == DEFAULT_STRING_VALUE)
			return 0;
		value = def_value;
		return 1;
	}
	value = token;
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_string(const string& group_name, const string& item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_string(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为 IPv4 地址的32bit整型（主机序）
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   unsigned int &value                        ：读到的IP地址，32位整型方式（返回1时可信，返回0则不可信）
		   const unsigned int &def_value              ：读不到情况下的默认值，该参数有默认值DEFAULT_IPADDR_VALUE，分两种情况
															当值是   DEFAULT_IPADDR_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_IPADDR_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_ipaddr(const char* const group_name, const char* const item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	value = def_value;
	string raw;
	int ret = item_get_raw(group_name, item_name, raw, group_is_case_sensitive, item_is_case_sensitive);
	if (ret == 0) 
	{
		if (def_value == DEFAULT_IPADDR_VALUE)
			return 0;
		else
			return 1;
	}
	istringstream iss(raw);
	string token;
	if (!(iss >> token)) 
	{
		if (def_value == DEFAULT_IPADDR_VALUE)
			return 0;
		else
			return 1;
	}
	int parts[4] = { 0, 0, 0, 0 };
	int part_index = 0;

	string current;
	for (size_t i = 0; i <= token.size(); ++i) 
	{
		if (i == token.size() || token[i] == '.') 
		{
			// 解析一个段
			if (current.size() == 0) 
			{
				part_index = 5; // 让其非法
				break;
			}

			// 将 current 转换成整数
			istringstream ss(current);
			int v = -1;
			if (!(ss >> v) || v < 0 || v > 255) 
			{
				part_index = 5; // 非法
				break;
			}

			parts[part_index] = v;
			part_index++;
			current.clear();
		}
		else
			current.push_back(token[i]);
	}
	// 必须刚好 4 段
	if (part_index != 4) 
	{
		if (def_value == DEFAULT_IPADDR_VALUE)
			return 0;
		else
			return 1;
	}
	unsigned int ip = (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | (parts[3]);
	value = ip;
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_ipaddr(const string& group_name, const string& item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_ipaddr(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}
