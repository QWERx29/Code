// 2451317 冯久恒 大数据
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
static string uint_to_ipstr(unsigned int ip);


void args_analyse_tools::init(args_analyse_tools* obj, const char* name, const ST_EXTARGS_TYPE type, const int ext_num)
{
    obj->args_name = name;
    obj->extargs_type = type;
    obj->extargs_num = ext_num;

    obj->extargs_bool_default = false;

    obj->extargs_int_default = 0;
    obj->extargs_int_min = 0;
    obj->extargs_int_max = 0;
    obj->extargs_int_set = nullptr;

    obj->extargs_double_default = 0.0;
    obj->extargs_double_min = 0.0;
    obj->extargs_double_max = 0.0;
    obj->extargs_double_set = nullptr;

    obj->extargs_string_default = "";
    obj->extargs_string_set = nullptr;

    obj->extargs_ipaddr_default = 0;

    obj->args_existed = 0;
    obj->extargs_int_value = 0;
    obj->extargs_double_value = 0.0;
    obj->extargs_string_value = "";
    obj->extargs_ipaddr_value = 0;
}

string args_analyse_tools::getValue(const args_analyse_tools* arg, bool is_default)
{
    string val;
    switch (arg->extargs_type)
    {
    case ST_EXTARGS_TYPE::boolean:
        if (is_default) 
            val = arg->extargs_bool_default ? "true" : "false";
        else
        {
            if (arg->existed())
                val = arg->existed() ? "true" : "false";
            else
                val = "/";
        }
        break;
    case ST_EXTARGS_TYPE::int_with_default:
    case ST_EXTARGS_TYPE::int_with_set_default:
        if (is_default)
            val = to_string(arg->extargs_int_default);
        else
            val = to_string(arg->get_int());
        break;
    case ST_EXTARGS_TYPE::int_with_error:
    case ST_EXTARGS_TYPE::int_with_set_error:
        if (is_default)
            val = "/";
        else
            val = to_string(arg->get_int());
        break;
    case ST_EXTARGS_TYPE::double_with_default:
    case ST_EXTARGS_TYPE::double_with_set_default:
        if (is_default)
            val = to_string(arg->extargs_double_default);
        else
            val = to_string(arg->get_double());
        break;
    case ST_EXTARGS_TYPE::double_with_set_error:
    case ST_EXTARGS_TYPE::double_with_error:
        if (is_default)
            val = "/";
        else
            val = to_string(arg->get_double());
        break;
    case ST_EXTARGS_TYPE::str:
    case ST_EXTARGS_TYPE::str_with_set_default:
        if (is_default)
        {
            if (arg->get_string() == "")
                val = "/";
            else
                val = arg->extargs_string_default;
        }
        else
            val = arg->get_string();
        break;
    case ST_EXTARGS_TYPE::str_with_set_error:
        if (is_default)
            val = "/";
        else
            val = arg->get_string();
        break;
    case ST_EXTARGS_TYPE::ipaddr_with_default:
        if (is_default)
            val = uint_to_ipstr(arg->extargs_ipaddr_default);
        else
            val = arg->get_str_ipaddr();
        break;
    case ST_EXTARGS_TYPE::ipaddr_with_error:
        if (is_default)
            val = "/";
        else
            val = arg->get_str_ipaddr();
        break;
    default:
        val = "N/A";
    }
    return val;
}

string args_analyse_tools::getTypeName(ST_EXTARGS_TYPE type)
{
    string type_str;
    switch (type)
    {
    case ST_EXTARGS_TYPE::boolean:
        type_str = "Bool";
        break;
    case ST_EXTARGS_TYPE::int_with_default:
        type_str = "IntWithDefault";
        break;
    case ST_EXTARGS_TYPE::int_with_error:
        type_str = "IntWithError";
        break;
    case ST_EXTARGS_TYPE::int_with_set_default:
        type_str = "IntSETWithDefault";
        break;
    case ST_EXTARGS_TYPE::int_with_set_error:
        type_str = "IntSETWithError";
        break;
    case ST_EXTARGS_TYPE::double_with_default:
        type_str = "DoubleWithDefault";
        break;
    case ST_EXTARGS_TYPE::double_with_error:
        type_str = "DoubleWithError";
        break;
    case ST_EXTARGS_TYPE::double_with_set_default:
        type_str = "DoubleSETWithDefault";
        break;
    case ST_EXTARGS_TYPE::double_with_set_error:
        type_str = "DoubleSETWithError";
        break;
    case ST_EXTARGS_TYPE::str:
        type_str = "String";
        break;
    case ST_EXTARGS_TYPE::str_with_set_default:
        type_str = "StringSETWithDefault";
        break;
    case ST_EXTARGS_TYPE::str_with_set_error:
        type_str = "StringSETWithError";
        break;
    case ST_EXTARGS_TYPE::ipaddr_with_default:
        type_str = "IPAddrWithDefault";
        break;
    case ST_EXTARGS_TYPE::ipaddr_with_error:
        type_str = "IPAddrWithError";
        break;
    default:
        type_str = "Unknown";
    }
    return type_str;
}

string args_analyse_tools::getRangeSet(const args_analyse_tools* arg, const int pos)
{
    string rangeset_str;
    switch (arg->extargs_type)
    {
    case ST_EXTARGS_TYPE::boolean:
    case ST_EXTARGS_TYPE::str:
    case ST_EXTARGS_TYPE::ipaddr_with_default:
    case ST_EXTARGS_TYPE::ipaddr_with_error:
        rangeset_str = "/";
        break;
    case ST_EXTARGS_TYPE::int_with_default:
    case ST_EXTARGS_TYPE::int_with_error:
        rangeset_str = "[" + to_string(arg->extargs_int_min) + ".." + to_string(arg->extargs_int_max) + "]";
        break;
    case ST_EXTARGS_TYPE::int_with_set_default:
    case ST_EXTARGS_TYPE::int_with_set_error:
    {
        if (arg->extargs_int_set != nullptr) 
        {
            int i = 0;
            while (arg->extargs_int_set[i] != INVALID_INT_VALUE_OF_SET && i < 10) 
            {
                if (i > 0) rangeset_str += "/";
                rangeset_str += to_string(arg->extargs_int_set[i]);
                i++;
            }
        }
    }
    break;
    case ST_EXTARGS_TYPE::double_with_default:
    case ST_EXTARGS_TYPE::double_with_error:
    {
		string min_str = to_string(arg->extargs_double_min);
		string max_str = to_string(arg->extargs_double_max);
        size_t min_dot_pos = min_str.find('.');
		size_t max_dot_pos = max_str.find('.');
        if (min_dot_pos != string::npos && min_dot_pos + pos < min_str.length())
            min_str = min_str.substr(0, min_dot_pos + pos);
		if (max_dot_pos != string::npos && max_dot_pos + pos < max_str.length())
			max_str = max_str.substr(0, max_dot_pos + pos);
        rangeset_str = "[" + min_str + ".." + max_str + "]";
    }
        break;
    case ST_EXTARGS_TYPE::double_with_set_default:
    case ST_EXTARGS_TYPE::double_with_set_error:
    {
        if (arg->extargs_double_set != nullptr) 
        {
            int i = 0;
            while (arg->extargs_double_set[i] != INVALID_DOUBLE_VALUE_OF_SET && i < 10) 
            {
                if (i > 0) rangeset_str += "/";
                string value_str = to_string(arg->extargs_double_set[i]);
                size_t dot_pos = value_str.find('.');
                if (dot_pos != string::npos && dot_pos + pos < value_str.length())
                    value_str = value_str.substr(0, dot_pos + pos);
                rangeset_str += value_str;
                i++;
            }
        }
    }
    break;
    case ST_EXTARGS_TYPE::str_with_set_default:
    case ST_EXTARGS_TYPE::str_with_set_error:
    {
        if (arg->extargs_string_set != nullptr) 
        {
            int i = 0;
            while (arg->extargs_string_set[i] != "" && i < 10) 
            {
                if (i > 0) rangeset_str += "/";
                rangeset_str += arg->extargs_string_set[i];
                i++;
            }
        }
    }
    break;
    default:
        rangeset_str = "/";
    }
    return rangeset_str;
}

static bool is_integer(const string& str) 
{
    if (str.empty()) 
        return false;
    size_t start = 0;
    if (str[0] == '+' || str[0] == '-') 
        start = 1;
    if (start >= str.length()) 
        return false;
    for (size_t i = start; i < str.length(); i++) 
        if (str[i] < '0' || str[i] > '9') 
            return false;
    return true;
}

static bool is_double(const string& str) 
{
    if (str.empty()) 
        return false;
    size_t start = 0;
    bool has_dot = false;
    if (str[0] == '+' || str[0] == '-') 
        start = 1;
    if (start >= str.length()) 
        return false;
    for (size_t i = start; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            if (has_dot) 
                return false;
            has_dot = true;
            if (i == start || i == str.length() - 1) 
                return false;
        }
        else if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

static int string_to_int(const string& str) 
{
    int result = 0;
    int sign = 1;
    size_t start = 0;
    if (str[0] == '+') start = 1;
    else if (str[0] == '-') 
    {
        sign = -1;
        start = 1;
    }
    for (size_t i = start; i < str.length(); i++)
        result = result * 10 + (str[i] - '0');
    return result * sign;
}

static double string_to_double(const string& str) 
{
    double result = 0.0;
    double fraction = 0.0;
    double divisor = 1.0;
    int sign = 1;
    size_t start = 0;
    bool after_dot = false;

    if (str[0] == '+') start = 1;
    else if (str[0] == '-') 
    {
        sign = -1;
        start = 1;
    }
    for (size_t i = start; i < str.length(); i++) 
    {
        if (str[i] == '.')
            after_dot = true;
        else 
        {
            if (after_dot) 
            {
                divisor *= 10.0;
                fraction = fraction * 10.0 + (str[i] - '0');
            }
            else
                result = result * 10.0 + (str[i] - '0');
        }
    }

    return sign * (result + fraction / divisor);
}

static bool is_valid_ipaddr(const string& ipstr) 
{
    int a, b, c, d;
    char dot;
    stringstream ss(ipstr);
    ss >> a >> dot >> b >> dot >> c >> dot >> d;
    if (ss.fail() || !ss.eof()) return false;
    if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255)
        return false;
    return true;
}

static unsigned int ipstr_to_uint(const string& ipstr) 
{
    int a, b, c, d;
    char dot;
    stringstream ss(ipstr);
    ss >> a >> dot >> b >> dot >> c >> dot >> d;
    return (a << 24) | (b << 16) | (c << 8) | d;
}

static string uint_to_ipstr(unsigned int ip) 
{
    string ip_str;
    ip_str += to_string((ip >> 24) & 0xFF) + "." + to_string((ip >> 16) & 0xFF) + "." + to_string((ip >> 8) & 0xFF) + "." + to_string(ip & 0xFF);
    return ip_str;
}

static bool string_in_set(const string& str, const string* set, int set_size)
{
    for (int i = 0; i < set_size; i++)
        if (str == set[i]) 
            return true;
    return false;
}

static bool int_in_set(int value, const int* set, int set_size)
{
    for (int i = 0; i < set_size; i++)
        if (value == set[i]) 
            return true;
    return false;
}

static bool double_in_set(double value, const double* set, int set_size)
{
    for (int i = 0; i < set_size; i++)
        if (fabs(value - set[i]) < DOUBLE_DELTA) 
            return true;
    return false;
}

   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：null
	***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
    init(this, "", ST_EXTARGS_TYPE::null, 0);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
    init(this, name, type,ext_num);
    extargs_bool_default = def;
    extargs_int_value = def ? 1 : 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
    init(this, name, type, ext_num);
    extargs_int_default = def;
    extargs_int_min = _min;
    extargs_int_max = _max;
    extargs_int_value = def;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
    init(this, name, type, ext_num);
    // 计算集合大小
    int set_size = 0;
    if (set != nullptr) 
        while (set[set_size] != INVALID_INT_VALUE_OF_SET && set_size < 100) 
            set_size++;
    // 分配内存并复制集合
    if (set_size > 0) 
    {
        extargs_int_set = new int[set_size + 1];
        for (int i = 0; i < set_size; i++)
            extargs_int_set[i] = set[i];
        extargs_int_set[set_size] = INVALID_INT_VALUE_OF_SET;
        if (def_of_set_pos >= 0 && def_of_set_pos < set_size) 
            extargs_int_default = set[def_of_set_pos];
        else 
            extargs_int_default = set[0];
    }
    else 
    {
        extargs_int_set = nullptr;
        extargs_int_default = 0;
    }
    extargs_int_value = extargs_int_default;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
    init(this, name, type, ext_num);

    extargs_string_default = def;
    extargs_string_value = def;

    // 根据类型处理IP地址
    if (type == ST_EXTARGS_TYPE::ipaddr_with_default || type == ST_EXTARGS_TYPE::ipaddr_with_error) 
    {
        // 验证并转换IP地址
        if (is_valid_ipaddr(def)) 
        {
            extargs_ipaddr_default = ipstr_to_uint(def);
            extargs_ipaddr_value = extargs_ipaddr_default;
        }
        else 
        {
            // 如果默认IP地址无效，设置为0
            extargs_ipaddr_default = 0;
            extargs_ipaddr_value = 0;
            extargs_string_value = "0.0.0.0";

            // 对于ipaddr_with_error类型，无效的默认IP地址可能需要特殊处理
            // 但构造函数通常不报错，只是初始化
        }
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
    init(this, name, type, ext_num);
    int set_size = 0;
    if (set != nullptr)
        while (set[set_size] != "" && set_size < 100)
            set_size++;
    // 分配内存并复制集合
    if (set_size > 0)
    {
        extargs_string_set = new string[set_size + 1];
        for (int i = 0; i < set_size; i++)
            extargs_string_set[i] = set[i];
        extargs_string_set[set_size] = "";
        // 设置默认值
        if (def_of_set_pos >= 0 && def_of_set_pos < set_size)
            extargs_string_default = set[def_of_set_pos];
        else 
            extargs_string_default = set[0];
    }
    else 
    {
        extargs_string_set = nullptr;
        extargs_string_default = "";
    }
    extargs_string_value = extargs_string_default;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_default、double_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const double	def, const double _min, const double _max)
{
    init(this, name, type, ext_num);
    extargs_double_default = def;
    extargs_double_min = _min;
    extargs_double_max = _max;
    extargs_double_value = def;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_set_default、double_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set)
{
    init(this, name, type, ext_num);
    // 计算集合大小
    int set_size = 0;
    if (set != nullptr)
        while (set[set_size] != INVALID_DOUBLE_VALUE_OF_SET && set_size < 100)
            set_size++;
    // 分配内存并复制集合
    if (set_size > 0) 
    {
        extargs_double_set = new double[set_size + 1];
        for (int i = 0; i < set_size; i++)
            extargs_double_set[i] = set[i];
        extargs_double_set[set_size] = INVALID_DOUBLE_VALUE_OF_SET;
        // 设置默认值
        if (def_of_set_pos >= 0 && def_of_set_pos < set_size)
            extargs_double_default = set[def_of_set_pos];
        else
            extargs_double_default = set[0];
    }
    else 
    {
        extargs_double_set = nullptr;
        extargs_double_default = 0.0;
    }
    extargs_double_value = extargs_double_default;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
    if (extargs_int_set != nullptr) 
    {
        delete[] extargs_int_set;
        extargs_int_set = nullptr;
    }
    if (extargs_double_set != nullptr) 
    {
        delete[] extargs_double_set;
        extargs_double_set = nullptr;
    }
    if (extargs_string_set != nullptr) 
    {
        delete[] extargs_string_set;
        extargs_string_set = nullptr;
    }
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：已实现，不要动
	***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const double args_analyse_tools::get_double() const
{
	return this->extargs_double_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
    return uint_to_ipstr(this->extargs_ipaddr_value);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const* const argv, args_analyse_tools* const args, const int follow_up_args)
{
    if (argc <= 0 || argv == nullptr || args == nullptr) 
        return -1;
    int args_count = 0;
    while (args[args_count].get_name() != "" && args_count < 100) 
        args_count++;

    for (int i = 1; i < argc; i++) 
    {
        string current_arg = argv[i];
        if (current_arg.length() > 2 && current_arg.substr(0, 2) == "--") 
        {
            string arg_name = current_arg;
            // 查找匹配的参数定义
            args_analyse_tools* matched_arg = nullptr;
            for (int j = 0; j < args_count; j++) 
            {
                if (args[j].get_name() == arg_name)
                {
                    matched_arg = &args[j];
                    break;
                }
            }
            if (matched_arg == nullptr) 
            {
                cerr << "参数[" << current_arg << "]非法." << endl;
                return -1;
            }
            if (matched_arg->existed()) 
            {
                cerr << "参数[" << current_arg << "]重复." << endl;
                return -1;
            }
            matched_arg->args_existed = 1;
            // 处理不同类型的参数
            switch (matched_arg->extargs_type) 
            {
            case ST_EXTARGS_TYPE::boolean: 
            {
                matched_arg->extargs_int_value = 1;
                break;
            }
            
            case ST_EXTARGS_TYPE::int_with_default:
            case ST_EXTARGS_TYPE::int_with_error: 
            {
                if (i + 1 >= argc) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不足. ";
                    cerr << "(类型:" << "int" << ", " << "范围:" << args_analyse_tools::getRangeSet(matched_arg, 7);
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::int_with_default)
                        cerr << " " << "缺省:" << args_analyse_tools::getValue(matched_arg, true) << ")" << endl;
                    else
						cerr << ")" << endl;
                    return -1;
                }
                string value_str = argv[++i];
                if (!is_integer(value_str)) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不是整数. ";
                    cerr << "(类型:" << "int" << ", " << "范围:" << args_analyse_tools::getRangeSet(matched_arg, 7) << " ";
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::int_with_default)
                        cerr << " " << "缺省:" << args_analyse_tools::getValue(matched_arg, true) << ")" << endl;
                    else
                        cerr << ")" << endl;
                    return -1;
                }
                int value = string_to_int(value_str);
                if (value < matched_arg->extargs_int_min || value > matched_arg->extargs_int_max) 
                {
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::int_with_default)
                        value = matched_arg->extargs_int_default;
                    else 
                    {
                        cerr << "参数[" << current_arg << "]的附加参数值(" << value << ")非法. ";
                        cerr << "(类型:" << "int" << ", "
                            << "范围" << args_analyse_tools::getRangeSet(matched_arg, 7) << ")" << endl;
                        return -1;
                    }
                }
                matched_arg->extargs_int_value = value;
                break;
            }

            case ST_EXTARGS_TYPE::int_with_set_default:
            case ST_EXTARGS_TYPE::int_with_set_error: 
            {
                if (i + 1 >= argc) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不足. ";
                    cerr << "(类型:" << "int" << ", " << "可取值[" << args_analyse_tools::getRangeSet(matched_arg, 7) << "]";
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
                        cerr << " " << "缺省:" << args_analyse_tools::getValue(matched_arg, true) << ")" << endl;
                    else
                        cerr << ")" << endl;
                    return -1;
                }
                string value_str = argv[++i];
                if (!is_integer(value_str)) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不是整数. ";
                    cerr << "(类型:" << "int" << ", " << "可取值[" << args_analyse_tools::getRangeSet(matched_arg, 7) << "]";
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
                        cerr << " " << "缺省:" << args_analyse_tools::getValue(matched_arg, true) << ")" << endl;
                    else
                        cerr << ")" << endl;
                    return -1;
                }
                int value = string_to_int(value_str);
                int set_size = 0;
                if (matched_arg->extargs_int_set != nullptr)
                    while (set_size < 100 && matched_arg->extargs_int_set[set_size] != INVALID_INT_VALUE_OF_SET)
                        set_size++;
                if (!int_in_set(value, matched_arg->extargs_int_set, set_size)) 
                {
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
                        value = matched_arg->extargs_int_default;
                    else 
                    {
                        cerr << "参数[" << current_arg << "]的附加参数值(" << value << ")非法. ";
                        cerr << "(类型:" << "int" << ", "
                            << "可取值[" << args_analyse_tools::getRangeSet(matched_arg, 7) << "]) " << endl;
                        return -1;
                    }
                }
                matched_arg->extargs_int_value = value;
                break;
            }

            case ST_EXTARGS_TYPE::double_with_default:
            case ST_EXTARGS_TYPE::double_with_error: 
            {
                if (i + 1 >= argc) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不足. ";
                    cerr << "(类型:" << "double" << ", " << "范围[" << matched_arg->extargs_double_min << ".." << matched_arg->extargs_double_max << "]";
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::double_with_default)
                        cerr << " " << "缺省:" << matched_arg->extargs_double_default << ")" << endl;
                    else
                        cerr << ")" << endl;
                    return -1;
                }
                string value_str = argv[++i];
                if (!is_double(value_str)) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不是浮点数. ";
                    cerr << "(类型:" << "double" << ", " << "范围[" << matched_arg->extargs_double_min << ".." << matched_arg->extargs_double_max << "]";
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::double_with_default)
                        cerr << " " << "缺省:" << matched_arg->extargs_double_default << ")" << endl;
                    else
                        cerr << ")" << endl;
                    return -1;
                }
                double value = string_to_double(value_str);
                if (value < matched_arg->extargs_double_min || value > matched_arg->extargs_double_max) 
                {
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::double_with_default)
                        value = matched_arg->extargs_double_default;
                    else 
                    {
                        cerr << "参数[" << current_arg << "]的附加参数值(" << value << ")非法. ";
                        cerr << "(类型:" << "double" << ", "
                            << "范围[" << matched_arg->extargs_double_min << ".." << matched_arg->extargs_double_max << "]) " << endl;
                        return -1;
                    }
                }
                matched_arg->extargs_double_value = value;
                break;
            }

            case ST_EXTARGS_TYPE::double_with_set_default:
            case ST_EXTARGS_TYPE::double_with_set_error: 
            {
                if (i + 1 >= argc) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不足. ";
                    cerr << "(类型:" << "double" << ", " << "可取值[";
					int j = 0;
                    while (matched_arg->extargs_double_set[j] != INVALID_DOUBLE_VALUE_OF_SET && j < 10)
                    {
                        if (j > 0) cerr << "/";
                        cerr << matched_arg->extargs_double_set[j];
                        j++;
                    }
                    cerr << "]";
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::double_with_set_default)
                        cerr << " " << "缺省:" << matched_arg->extargs_double_default << ")" << endl;
                    else
                        cerr << ")" << endl;
                    return -1;
                }
                string value_str = argv[++i];
                if (!is_double(value_str)) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不是浮点数. ";
                    cerr << "(类型:" << "double" << ", " << "可取值[";
                    int j = 0;
                    while (matched_arg->extargs_double_set[j] != INVALID_DOUBLE_VALUE_OF_SET && j < 10)
                    {
                        if (j > 0) cerr << "/";
                        cerr << matched_arg->extargs_double_set[j];
                        j++;
                    }
                    cerr << "]";
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::double_with_set_default)
                        cerr << " " << "缺省:" << matched_arg->extargs_double_default << ")" << endl;
                    else
                        cerr << ")" << endl;
                    return -1;
                }
                double value = string_to_double(value_str);
                int set_size = 0;
                if (matched_arg->extargs_double_set != nullptr)
                    while (set_size < 100 && matched_arg->extargs_double_set[set_size] != INVALID_DOUBLE_VALUE_OF_SET)
                        set_size++;
                if (!double_in_set(value, matched_arg->extargs_double_set, set_size)) 
                {
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::double_with_set_default)
                        value = matched_arg->extargs_double_default;
                    else 
                    {
                        cerr << "参数[" << current_arg << "]的附加参数值(" << value << ")非法. ";
                        cerr << "(类型:" << "double" << ", " << "可取值[";
                        int j = 0;
                        while (matched_arg->extargs_double_set[j] != INVALID_DOUBLE_VALUE_OF_SET && j < 10)
                        {
                            if (j > 0) cerr << "/";
                            cerr << matched_arg->extargs_double_set[j];
                            j++;
                        }
                        cerr << "])";
                        return -1;
                    }
                }
                matched_arg->extargs_double_value = value;
                break;
            }

            case ST_EXTARGS_TYPE::str: 
            {
                if (i + 1 >= argc) 
                {
                    cerr << "参数" << current_arg << "缺少附加参数. (类型:string";
                    if(matched_arg->extargs_string_default!= "")
						cerr << " 缺省:" << matched_arg->extargs_string_default;
					cerr << ")" << endl;
                    return -1;
                }
                string next_arg = argv[i + 1];
                if (next_arg.length() > 2 && next_arg.substr(0, 2) == "--") 
                {
                    cerr << "参数" << current_arg << "缺少附加参数. (类型:string";
                    if (matched_arg->extargs_string_default != "")
                        cerr << " 缺省:" << matched_arg->extargs_string_default;
                    cerr << ")" << endl;
                    return -1;
                }
                matched_arg->extargs_string_value = argv[++i];
                break;
            }
            case ST_EXTARGS_TYPE::str_with_set_default:
            case ST_EXTARGS_TYPE::str_with_set_error: 
            {
                if (i + 1 >= argc) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不足. ";
                    cerr << "(类型:string, 可取值[" << args_analyse_tools::getRangeSet(matched_arg, 7) << "]";
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::str_with_set_default)
                        cerr << " " << "缺省:" << args_analyse_tools::getValue(matched_arg, true) << ")" << endl;
                    else
                        cerr << ")" << endl;
                    return -1;
                }
                string value = argv[++i];
                int set_size = 0;
                if (matched_arg->extargs_string_set != nullptr) 
                    while (set_size < 100 && matched_arg->extargs_string_set[set_size] != "") 
                        set_size++;
                if (!string_in_set(value, matched_arg->extargs_string_set, set_size)) 
                {
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::str_with_set_default)
                        value = matched_arg->extargs_string_default;
                    else 
                    {
                        cerr << "参数[" << current_arg << "]的附加参数值(" << value << ")非法. ";
                        cerr << "(类型:string, 可取值[" << args_analyse_tools::getRangeSet(matched_arg, 7) << "])" << endl;
                        return -1;
                    }
                }
                matched_arg->extargs_string_value = value;
                break;
            }

            case ST_EXTARGS_TYPE::ipaddr_with_default:
            case ST_EXTARGS_TYPE::ipaddr_with_error: 
            {
                if (i + 1 >= argc) 
                {
                    cerr << "参数[" << current_arg << "]的附加参数不足. ";
					cerr << "(类型:IP地址";
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default)
                        cerr << " " << "缺省:" << args_analyse_tools::getValue(matched_arg, true) << ")" << endl;
                    else
                        cerr << ")" << endl;
                    return -1;
                }
                string ipstr = argv[++i];
                if (!is_valid_ipaddr(ipstr)) 
                {
                    if (matched_arg->extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) 
                    {
                        matched_arg->extargs_ipaddr_value = matched_arg->extargs_ipaddr_default;
                        matched_arg->extargs_string_value = uint_to_ipstr(matched_arg->extargs_ipaddr_default);
                    }
                    else 
                    {
                        cerr << "参数[" << current_arg << "]的附加参数值(" << ipstr << ")非法. ";
                        cerr << "(类型:IP地址)" << endl;
                        return -1;
                    }
                }
                else 
                {
                    matched_arg->extargs_ipaddr_value = ipstr_to_uint(ipstr);
                    matched_arg->extargs_string_value = ipstr;
                }
                break;
            }
            default:
                cerr << "参数[" << current_arg << "]格式非法." << endl;
                return -1;
            }
        }
        else 
        {
            if (follow_up_args)
                return i;
            else
            {
                cerr << "参数[" << current_arg << "]格式非法(不是--开头的有效内容)." << endl;
                return -1;
            }
        }
    }
    return 0;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/

int args_analyse_print(const args_analyse_tools* const args)
{
    if (args == nullptr)
        return 0;
    // 计算列宽
    int name_width = 4;    // "name"
    int type_width = 4;    // "type"
    int default_width = 7; // "default"
    int exists_width = 6;  // "exists"
    int value_width = 5;   // "value"
    int range_width = 6;   // "range"

    // 统计参数数量和计算列宽
    const args_analyse_tools* valid_args[100];
    int valid_count = 0;
    int index = 0;

    // 先计算每列的最大宽度
    while (args[index].get_name() != "" && index < 100) 
    {
        valid_args[valid_count] = &args[index];
        // 更新列宽
        name_width = max(static_cast<int>(args[index].get_name().length()), name_width);
        // 类型字符串
        string type_str = args_analyse_tools::getTypeName(args[index].extargs_type);
        type_width = max(static_cast<int>(type_str.length()), type_width);
        // 默认值字符串
        string default_str = args_analyse_tools::getValue(&args[index], true);
        default_width = max(static_cast<int>(default_str.length()), default_width);
        // 当前值字符串
        string value_str = args_analyse_tools::getValue(&args[index], false);
        value_width = max(static_cast<int>(value_str.length()), value_width);
        string rangeset_str = args_analyse_tools::getRangeSet(&args[index], 7);
		range_width = max(static_cast<int>(rangeset_str.length()), range_width);
        valid_count++;
        index++;
    }

    // 确保最小宽度
    if (name_width < 4) name_width = 4;
    if (type_width < 4) type_width = 4;
    if (default_width < 7) default_width = 7;
    if (exists_width < 6) exists_width = 6;
    if (value_width < 5) value_width = 5;
    if (range_width < 6) range_width = 6;

    int total_width = name_width + type_width + default_width + exists_width + value_width + range_width + 7;

    cout << setw(total_width) << setfill('=') << "=" << endl;
    cout << setfill(' ');
    cout << " " << left << setw(name_width) << "name"
        << " " << left << setw(type_width) << "type"
        << " " << left << setw(default_width) << "default"
        << " " << left << setw(exists_width) << "exists"
        << " " << left << setw(value_width) << "value"
        << " " << left << setw(range_width) << "range/set" << endl;
    cout << setw(total_width) << setfill('=') << "=" << endl;
    cout << setfill(' ');
    // 输出数据行
    for (int i = 0; i < valid_count; i++) 
    {
        const args_analyse_tools* arg = valid_args[i];
        string type_str;
        type_str = args_analyse_tools::getTypeName(arg->extargs_type);
        // 默认值字符串
        string default_str;
        default_str = args_analyse_tools::getValue(arg, true);
        // 当前值字符串
        string value_str;
        value_str= args_analyse_tools::getValue(arg, false);
        // 范围/集合字符串
        string rangeset_str;
        rangeset_str = args_analyse_tools::getRangeSet(arg, 7);

        cout << " " << left << setw(name_width) << (arg->get_name())
             << " " << left << setw(type_width) << type_str
             << " " << left << setw(default_width) << default_str
             << " " << left << setw(exists_width) << (arg->existed() ? "1" : "0")
             << " " << left << setw(value_width) << value_str
             << " " << left << setw(range_width) << rangeset_str << endl;
    }
    cout << setw(total_width) << setfill('=') << "=" << endl;
    cout << setfill(' ') << endl;
    return 0;
}

#endif // !ENABLE_LIB_COMMON_TOOLS