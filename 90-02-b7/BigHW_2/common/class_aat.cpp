/*1952339 信08 张馨月*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
static bool get_int_num(const char* const src, int& rt)
{
	int k;
	rt = 0;
	for (k = 0; src[k] && src[k] >= '0' && src[k] <= '9'; ++k)
		rt = rt * 10 + src[k] - 48;
	return src[k] == 0;
}

static int get_int_ip(const char* const src, unsigned int& rt)//1正确0不合法2非范围
{
	rt = 0;
	int p = 0, tg = 1;
	int num[4] = { (1 << 8) - 1, (1 << 8) - 1 , (1 << 8) - 1 , (1 << 8) - 1 };
	for (int i = 0; i < 4; ++i) {
		int now = 0;
		if (!src[p])
			return 0;
		for (; src[p] && src[p] >= '0' && src[p] <= '9'; ++p)
			now = now * 10 + src[p] - 48;
		if (now > ((1 << 9) - 1) || now < 0)
			tg = 2;
		num[i] &= now;
		if (!src[p]) {
			if (i != 3)
				return 0;
			else
				break;
		}
		++p;
	}
	if (tg == 2)
		return 2;
	for (int i = 0; i < 4; ++i)
		rt = rt << 8 | num[i];
	return 1;
}

static const string get_str_ip(unsigned int x)
{
	int unit = (1 << 9) - 1;
	int num[4] = { 0 };
	for (int i = 0; i < 4; ++i) {
		num[i] = x & unit;
		x >>= 8;
	}
	char aim[16] = { 0 };
	sprintf(aim, "%d.%d.%d.%d", num[3], num[2], num[1], num[0]);
	string rt = aim;
	return rt;
}

template<class T>
static bool check_in_set(T* set, T x, T end) {
	for (int i = 0; *(set + i) != end; ++i)
		if (x == *(set + i))
			return 1;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
AAT::AAT()
{
	args_name = "";
	extargs_int_set = NULL;
	extargs_string_set = NULL;
	args_existed = 0;
	/*
	extargs_bool_default = 0;
	extargs_int_default = -1;
	extargs_int_max = -1;
	extargs_int_min = -1;
	extargs_int_value = 0;
	extargs_ipaddr_default = 0;
	extargs_ipaddr_value = 0;
	extargs_num = 0;
	extargs_string_default = "/";
	extargs_string_value = "/";*/
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
AAT::AAT(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_bool_default = def;
	args_existed = 0;
	extargs_int_set = NULL;
	extargs_string_set = NULL;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
AAT::AAT(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max, const bool mutli_args)
{
	args_existed = 0;
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_int_default = def;
	extargs_int_min = _min;
	extargs_int_max = _max;
	extargs_int_set = NULL;
	extargs_string_set = NULL;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
AAT::AAT(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set, const bool mutli_args)
{
	args_existed = 0;
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_int_default = *(set + def_of_set_pos);
	extargs_int_set = NULL;
	extargs_string_set = NULL;
	int i = 0;
	for (; *(set + i) != INVALID_INT_VALUE_OF_SET; ++i)
		;
	extargs_int_set = new(nothrow) int[i + 1];
	for (i = 0; *(set + i) != INVALID_INT_VALUE_OF_SET; ++i)
		*(extargs_int_set + i) = *(set + i);
	extargs_int_set[i] = INVALID_INT_VALUE_OF_SET;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
AAT::AAT(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def, const bool mutli_args)
{
	args_existed = 0;
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	unsigned int rt = 0;
	int j = 0;
	for (int i = 0; i < 4 && def[j] >= '0' && def[j] <= '9'; ++i) {
		int now = 0;
		for (; def[j] != '.' && def[j]; ++j)
			now = now * 10 + def[j] - 48;
		rt = rt << 8 | now;
		if (def[j] == 0)
			break;
		++j;
	}
	extargs_ipaddr_default = rt;
	extargs_string_default = def;
	extargs_int_set = NULL;
	extargs_string_set = NULL;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
AAT::AAT(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set, const bool mutli_args)
{
	args_existed = 0;
	args_name = name;
	extargs_type = type;
	extargs_string_default = *(set + def_of_set_pos);
	extargs_int_set = NULL;
	extargs_string_set = NULL;
	int i = 0;
	for (; *(set + i) != ""; ++i)
		;
	extargs_string_set = new(nothrow) string[i + 1];
	for (i = 0; *(set + i) != ""; ++i)
		extargs_string_set[i] = set[i];
	extargs_string_set[i] = "";
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
AAT::~AAT()
{
	if (extargs_int_set)
		delete[] extargs_int_set;
	if (extargs_string_set)
		delete[] extargs_string_set;
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（protected）
   ---------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：已实现，不要动
	***************************************************************************/
const string AAT::get_name() const
{
	return args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int AAT::existed() const
{
	return !!args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int AAT::get_int() const
{
	return extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string AAT::get_string() const
{
	return extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int AAT::get_ipaddr() const
{
	return extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string AAT::get_str_ipaddr() const
{
	int unit = (1 << 8) - 1;
	int num[4] = { 0 };
	unsigned int x = extargs_ipaddr_value;
	for (int i = 0; i < 4; ++i) {
		num[i] = x & unit;
		x >>= 8;
	}
	char aim[16] = { 0 };
	sprintf(aim, "%d.%d.%d.%d", num[3], num[2], num[1], num[0]);
	string rt = aim;
	return rt;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			./log_login --limit 10 --user root                    ：无后续参数，置0
			./ulimits_check --memory 256 --cpu 1 [./log_login ***]：有后续参数，置1
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse(const int argc, const char* const* const argv, AAT* const args, const int follow_up_args)
{
	int i;
	for (i = 1; i < argc; ++i) {
		bool tg = 0;
		for (int j = 0; args[j].args_name != ""; ++j)
			if (args[j].args_name == argv[i]) {
				if (args[j].existed()) {
					cout << args[j].args_name << "参数重复\n";
					return -7;
				}
				args[j].args_existed = 1;
				tg = 1;
				if (args[j].extargs_num == 1) {
					++i;
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
						if (argv[i] == NULL || (argv[i][0] == '-' && argv[i][1] == '-')) {
							cout << args[j].args_name << "缺少参数\n";
							return -6;
						}
						bool ret;
						if (argv[i][0] < '0' || argv[i][0] > '9') {
							cout << args[j].args_name << "参数错误\n";
							return -1;
						}
						else
							ret = get_int_num(argv[i], args[j].extargs_int_value);
						if (!ret || args[j].extargs_int_value < args[j].extargs_int_min || args[j].extargs_int_value > args[j].extargs_int_max) {
							cout << args[j].args_name << "参数错误\n";
							return -1;
						}
						break;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
						if (argv[i] == NULL || (argv[i][0] == '-' && argv[i][1] == '-')) {
							cout << args[j].args_name << "缺少参数\n";
							return -6;
						}
						bool ret;
						if (argv[i][0] < '0' || argv[i][0] > '9') {
							cout << args[j].args_name << "参数错误\n";
							return -1;
						}
						else
							ret = get_int_num(argv[i], args[j].extargs_int_value);
						if (!ret || !check_in_set(args[j].extargs_int_set, args[j].extargs_int_value, INVALID_INT_VALUE_OF_SET)) {
							cout << args[j].args_name << "参数错误\n";
							return -2;
						}
						break;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
						if (argv[i] == NULL || (argv[i][0] == '-' && argv[i][1] == '-')) {
							cout << args[j].args_name << "缺少参数\n";
							return -6;
						}
						int ret = get_int_ip(argv[i], args[j].extargs_ipaddr_value);
						if (ret != 1) {
							cout << args[j].args_name << "参数错误\n";
							return -3;
						}
						break;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
						if (argv[i] == NULL || (argv[i][0] == '-' && argv[i][1] == '-')) {
							cout << args[j].args_name << "缺少参数\n";
							return -6;
						}
						else {
							args[j].extargs_string_value = argv[i];
							break;
						}
						if (!check_in_set(args[j].extargs_string_set, args[j].extargs_string_value, string("")))
							args[j].extargs_string_value = args[j].extargs_string_default;
						break;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default) {
						if (argv[i] == NULL || (argv[i][0] == '-' && argv[i][1] == '-')) {
							--i;
							args[j].extargs_int_value = args[j].extargs_int_default;
							break;
						}
						bool ret;
						if (argv[i][0] < '0' || argv[i][0] > '9') {
							cout << args[j].args_name << "参数错误\n";
							return -3;
						}
						else
							ret = get_int_num(argv[i], args[j].extargs_int_value);
						if (!ret || args[j].extargs_int_value < args[j].extargs_int_min || args[j].extargs_int_value > args[j].extargs_int_max)
							args[j].extargs_int_value = args[j].extargs_int_default;
						break;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {
						if (argv[i] == NULL || (argv[i][0] == '-' && argv[i][1] == '-')) {
							--i;
							args[j].extargs_int_value = args[j].extargs_int_default;
							break;
						}
						bool ret;
						if (argv[i][0] < '0' || argv[i][0] > '9') {
							args[j].extargs_int_value = args[j].extargs_int_default;
							break;
						}
						else
							ret = get_int_num(argv[i], args[j].extargs_int_value);
						if (!ret) {
							cout << args[j].args_name << "参数错误\n";
							return -3;
						}
						if (!check_in_set(args[j].extargs_int_set, args[j].extargs_int_value, INVALID_INT_VALUE_OF_SET))
							args[j].extargs_int_value = args[j].extargs_int_default;
						break;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
						if (argv[i] == NULL || (argv[i][0] == '-' && argv[i][1] == '-')) {
							--i;
							args[j].extargs_ipaddr_value = args[j].extargs_ipaddr_default;
							break;
						}
						int ret = get_int_ip(argv[i], args[j].extargs_ipaddr_value);
						if (ret == 2)
							args[j].extargs_ipaddr_value = args[j].extargs_ipaddr_default;
						else if (ret == 0) {
							cout << args[j].args_name << "参数错误\n";
							return -3;
						}
						break;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::str) {
						if (argv[i] == NULL) {
							cout << args[j].args_name << "缺少参数\n";
							return -6;
						}
						args[j].extargs_string_value = argv[i];
						break;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) {
						if (argv[i] == NULL || (argv[i][0] == '-' && argv[i][1] == '-')) {
							--i;
							args[j].extargs_string_value = args[j].extargs_string_default;
							break;
						}
						else {
							args[j].extargs_string_value = argv[i];
							break;
						}
						if (!check_in_set(args[j].extargs_string_set, args[j].extargs_string_value, string("")))
							args[j].extargs_string_value = args[j].extargs_string_default;
						break;
					}

				}
				else if (args[j].extargs_num == 0) {
					++i;
					if (argv[i] && (argv[i][0] != '-' || argv[i][1] != '-')) {
						cout << args[j].args_name << "参数多余\n";
						return -4;
					}
					--i;
					break;
				}
			}
		if (!tg) {
			if (argv[i][0] == '[' && follow_up_args == 1)
				break;
			else {
				cout << "未知参数" << argv[i] << endl;
				return -5;
			}
		}
		if (argv[i + 1] && argv[i + 1][0] != '-' && argv[i + 1][1] != '-') {
			cout << argv[i] << "参数多余\n";
			return -4;
		}
	}
	return i;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const AAT* const args)
{
	int len_name = 20, len_type = 25, len_default = 15, len_exists = 8, len_value = 8, len_rs = 20;
	cout << setiosflags(ios::left);
	cout << setw(len_name) << "name";
	cout << setw(len_type) << "type";
	cout << setw(len_default) << "default";
	cout << setw(len_exists) << "exists";
	cout << setw(len_value) << "value";
	cout << setw(len_rs) << "rang/set";
	cout << endl;
	int all = len_name + len_type + len_default + len_exists + len_value + len_rs;
	for (int i = 0; i < all; ++i)
		cout << '=';
	cout << endl;
	for (int i = 0; args[i].args_name != ""; ++i) {
		cout << setw(len_name) << args[i].args_name;
		if (args[i].existed()) {
			if (args[i].extargs_type == ST_EXTARGS_TYPE::boolean) {
				cout << setw(len_type) << "Bool";
				cout << setw(len_default) << (args[i].extargs_bool_default ? "true" : "false");
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << "true";
				cout << setw(len_rs) << "/";
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default) {
				cout << setw(len_type) << "IntWithDefault";
				cout << setw(len_default) << args[i].extargs_int_default;
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << args[i].extargs_int_value;
				cout << '[' << args[i].extargs_int_min << ".." << args[i].extargs_int_max << ']';
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
				cout << setw(len_type) << "IntWithError";
				cout << setw(len_default) << "/";
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << args[i].extargs_int_value;
				cout << '[' << args[i].extargs_int_min << ".." << args[i].extargs_int_max << ']';
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {
				cout << setw(len_type) << "IntWithSetDefault";
				cout << setw(len_default) << args[i].extargs_int_default;
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << args[i].extargs_int_value;
				cout << *args[i].extargs_int_set;
				for (int j = 1; *(args[i].extargs_int_set + j) != INVALID_INT_VALUE_OF_SET; ++j)
					cout << '/' << *(args[i].extargs_int_set + j);
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
				cout << setw(len_type) << "IntWithSetError";
				cout << setw(len_default) << "/";
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << args[i].extargs_int_value;
				cout << *args[i].extargs_int_set;
				for (int j = 1; *(args[i].extargs_int_set + j) != INVALID_INT_VALUE_OF_SET; ++j)
					cout << '/' << *(args[i].extargs_int_set + j);
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::str) {
				cout << setw(len_type) << "String";
				cout << setw(len_default) << (args[i].extargs_string_default == "" ? "/" : args[i].extargs_string_default);
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << args[i].extargs_string_value;
				cout << setw(len_rs) << "/";
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) {
				cout << setw(len_type) << "StringWithSetDefault";
				cout << setw(len_default) << (args[i].extargs_string_default == "" ? "/" : args[i].extargs_string_default);
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << args[i].extargs_string_value;
				cout << *args[i].extargs_string_set;
				for (int j = 1; *(args[i].extargs_string_set + j) != ""; ++j)
					cout << '/' << *(args[i].extargs_string_set + j);
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
				cout << setw(len_type) << "StringWithSetError";
				cout << setw(len_default) << "/";
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << args[i].extargs_string_value;
				cout << *args[i].extargs_string_set;
				for (int j = 1; *(args[i].extargs_string_set + j) != ""; ++j)
					cout << '/' << *(args[i].extargs_string_set + j);
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
				cout << setw(len_type) << "IpaddrWithDefault";
				cout << setw(len_default) << get_str_ip(args[i].extargs_ipaddr_default);
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << args[i].get_str_ipaddr();
				cout << setw(len_rs) << "/";
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
				cout << setw(len_type) << "IpaddrWithError";
				cout << setw(len_default) << "/";
				cout << setw(len_exists) << 1;
				cout << setw(len_value) << args[i].get_str_ipaddr();
				cout << setw(len_rs) << "/";
			}
		}
		else {
			if (args[i].extargs_type == ST_EXTARGS_TYPE::boolean) {
				cout << setw(len_type) << "Bool";
				cout << setw(len_default) << (args[i].extargs_bool_default ? "true" : "false");
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << setw(len_rs) << "/";
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default) {
				cout << setw(len_type) << "IntWithDefault";
				cout << setw(len_default) << args[i].extargs_int_default;
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << '[' << args[i].extargs_int_min << ".." << args[i].extargs_int_max << ']';
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
				cout << setw(len_type) << "IntWithError";
				cout << setw(len_default) << "/";
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << '[' << args[i].extargs_int_min << ".." << args[i].extargs_int_max << ']';
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {
				cout << setw(len_type) << "IntWithSetDefault";
				cout << setw(len_default) << args[i].extargs_int_default;
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << *args[i].extargs_int_set;
				for (int j = 1; *(args[i].extargs_int_set + j) != INVALID_INT_VALUE_OF_SET; ++j)
					cout << '/' << *(args[i].extargs_int_set + j);
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
				cout << setw(len_type) << "IntWithSetError";
				cout << setw(len_default) << "/";
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << *args[i].extargs_int_set;
				for (int j = 1; *(args[i].extargs_int_set + j) != INVALID_INT_VALUE_OF_SET; ++j)
					cout << '/' << *(args[i].extargs_int_set + j);
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::str) {
				cout << setw(len_type) << "String";
				cout << setw(len_default) << (args[i].extargs_string_default == "" ? "/" : args[i].extargs_string_default);
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << setw(len_rs) << "/";
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) {
				cout << setw(len_type) << "StringWithSetDefault";
				cout << setw(len_default) << (args[i].extargs_string_default == "" ? "/" : args[i].extargs_string_default);
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << *args[i].extargs_string_set;
				for (int j = 1; *(args[i].extargs_string_set + j) != ""; ++j)
					cout << '/' << *(args[i].extargs_string_set + j);
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
				cout << setw(len_type) << "StringWithSetError";
				cout << setw(len_default) << "/";
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << *args[i].extargs_string_set;
				for (int j = 1; *(args[i].extargs_string_set + j) != ""; ++j)
					cout << '/' << *(args[i].extargs_string_set + j);
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
				cout << setw(len_type) << "IpaddrWithDefault";
				cout << setw(len_default) << get_str_ip(args[i].extargs_ipaddr_default);
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << setw(len_rs) << "/";
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
				cout << setw(len_type) << "IpaddrWithError";
				cout << setw(len_default) << "/";
				cout << setw(len_exists) << 0;
				cout << setw(len_value) << "/";
				cout << setw(len_rs) << "/";
			}
		}
		cout << endl;
	}
	return 0; //此句根据需要修改
}
