/*1952339 信08 张馨月*/
#pragma once

#include <string>
using namespace std;

#define INVALID_INT_VALUE_OF_SET	0x7FFFFFFF

/*  args    extargs_num extargs_type  extargs_fun             extargs_defvalue;
	--help  0           NULL          NULL                    NULL
	--limit 1           INT           char * 转 int 返回      min/max/def
	--limit 1           INT           char * 转 int 返回      min/max/无default，返回错
	--limit 1           INT           char * 转 int 返回      12/23/35集合中的一个，返回错
	--user  1           string        char * 转 string 返回   def
	--user  1           string        char * 转 string 返回   "abc"/"def"/"xyz"集合中的一个
	--ip    1           IPADDR        char * 转 ipaddr 返回   NULL
*/

/* 定义各种参数类型 */
enum class ST_EXTARGS_TYPE {
	null = 0,				//仅用于无参初始化
	boolean,				//仅需要返回0/1，表示是否存在，例如：--help
	int_with_default,		//附加参数为整型，介于 min..max之间，有缺省值，若置超过上下限，则置缺省值
	int_with_error,			//附加参数为整型，介于 min..max之间，有缺省值，若置超过上下限，则返回错误
	int_with_set_default,	//附加参数为整型，只能属于一个有若干元素的集合[11/22/33]，有缺省值，若值不在集合中，则置缺省值
	int_with_set_error,		//附加参数为整型，只能属于一个有若干元素的集合[11/22/33]，有缺省值，若值不在集合中，则返回错误
	str,					//附加参数为字符串
	str_with_set_default,	//附加参数为字符串，只能属于一个有若干元素的集合["11"/"22"/"33"]，有缺省值，若值不在集合中，则置缺省值
	str_with_set_error,		//附加参数为字符串，只能属于一个有若干元素的集合["11"/"22"/"33"]，有缺省值，若值不在集合中，则返回错误
	ipaddr_with_default,	//附加参数为IP地址，有缺省值，返回一个u_int32
	ipaddr_with_error,		//附加参数为IP地址，无缺省值，返回错误
#if 0
	/* 减轻工作量，以下暂时屏蔽 */
	date_with_default,			//附加参数为日期型，形式为"yyyy-mm-dd"，有缺省值
	date_with_error,			//附加参数为日期型，形式为"yyyy-mm-dd"，无缺省值
	date_with_set_default,		//附加参数为日期型，形式为"yyyy-mm-dd"，只能属于一个有若干元素的集合["1980-1-2"/"1990-3-12"/"2020-4-14"]，有缺省值，若值不在集合中，则置缺省值
	date_with_set_error,		//附加参数为日期型，形式为"yyyy-mm-dd"，只能属于一个有若干元素的集合["1980-1-2"/"1990-3-12"/"2020-4-14"]，有缺省值，若值不在集合中，则返回错误
	time_with_default,			//附加参数为时间型，形式为"hh:mm:ss"，有缺省值
	time_with_error,			//附加参数为时间型，形式为"hh:mm:ss"，无缺省值
	time_with_set_default,		//附加参数为时间型，形式为"hh:mm:ss"，只能属于一个有若干元素的集合["01:02:03"/"09:34:23"/"22:00:00"]，有缺省值，若值不在集合中，则置缺省值
	time_with_set_error,		//附加参数为时间型，形式为"hh:mm:ss"，只能属于一个有若干元素的集合["01:02:03"/"09:34:23"/"22:00:00"]，无缺省值，若值不在集合中，则返回错误
	datetime_with_default,		//附加参数为日期时间型，形式为"yyyy-mm-dd hh:mm:ss"，有缺省值
	datetime_with_error,		//附加参数为日期时间型，形式为"yyyy-mm-dd hh:mm:ss"，无缺省值
	datetime_with_set_default,	//附加参数为日期时间型，形式为"yyyy-mm-dd hh:mm:ss"，只能属于一个有若干元素的集合["1900-01-01 01:02:03"/"1990-03-12 09:34:23"/"2020-4-14 22:00:00"]，有缺省值，若值不在集合中，则置缺省值
	datetime_with_set_error,	//附加参数为日期时间型，形式为"yyyy-mm-dd hh:mm:ss"，只能属于一个有若干元素的集合["1900-01-01 01:02:03"/"1990-03-12 09:34:23"/"2020-4-14 22:00:00"]，有缺省值，若值不在集合中，则返回错误
#endif
	tmax					//最大值，控制超限
};

/* ---------------------------------------------------------------
	 允许加入其它需要的定义
	 const全局变量/static全局变量(慎用)/define/class/struct/enum/enum class/union等
   ---------------------------------------------------------------- */



/* ---------------------------------------------------------------
	   class AAT的定义，已有部分不要动，允许protected加入其它需要的定义
   ---------------------------------------------------------------- */
class AAT {
protected:
	/* 这些初始化后值就不应该再变 */
	string				args_name;		//参数名称，类似于 "--help形式"
	ST_EXTARGS_TYPE		extargs_type;	//本参数的额外参数的类型
	int					extargs_num;	//额外参数的个数，0-1，其它暂未考虑

	bool extargs_bool_default;	//bool型额外参数的缺省值（default）

	int  extargs_int_default;	//int型额外参数的缺省值（default）
	int  extargs_int_min;		//int型额外参数的最小值（min）
	int  extargs_int_max;		//int型额外参数的最大值（max）
	int* extargs_int_set;		//int型额外参数的集合（提示：只是一个指针哦）

	string  extargs_string_default;	//string型额外参数的缺省值(含ipaddr)
	string* extargs_string_set;		//string型额外参数的集合（提示：只是一个指针哦）

	unsigned int   extargs_ipaddr_default;		//IP地址缺省值

	/* 下面这些是变量 */
	int    args_existed;				//本参数是否出现过（防止相同参数 -n ** -n ** 重复出现）
	int    extargs_int_value;			//int型额外参数读到的值
	string extargs_string_value;		//string型额外参数读到的值
	unsigned int extargs_ipaddr_value;	//IP地址额外参数读到的值（IP地址的内部存储为此形式，字符串形式需要转换）

	/* ---------------------------------------------------------------
		 允许加入其它需要的定义（内部用）
	   ---------------------------------------------------------------- */

public:
	AAT();
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def);

	/* 减轻工作量，省去相同参数的处理，这四个构造函数，不处理最后为true的情况 */
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max, const bool mutli_args = false);
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set, const bool mutli_args = false);
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const string def, const bool mutli_args = false); //注：date/time/datetime也匹配此构造函数（略）
	AAT(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set, const bool mutli_args = false);//注：date/time/datetime的set形式也匹配此构造函数（略）

	~AAT();

	/* 外取参数 */
	const string get_name() const;			//返回某设置项的名称（返回 "--help"）
	const int    existed() const;			//判断某设置项是否存在
	const int    get_int() const;			//返回某设置项的值（int型）
	const string get_string() const;		//返回某设置项的值（string型）
	const unsigned int get_ipaddr() const;	//返回某设置项的值（IP地址，以"127.0.0.1"为例，返回u_int32型的 0x7f000001）
	const string get_str_ipaddr() const;	//返回某设置项的值（IP地址，以"127.0.0.1"为例，返回字符串形式的"127.0.0.1"）

#if 0
	/* 减轻工作量，省去相同参数的处理 */

	/* 减轻工作量，省去日期/时间型的处理 */
#endif

	friend int args_analyse(const int argc, const char* const *const argv, AAT* const args, const int follow_up_args);
	friend int args_analyse_print(const AAT *const args);

	/* ---------------------------------------------------------------
		 不允许加入其它需要的定义（对外不呈现）
	   ---------------------------------------------------------------- */
};

int args_analyse(const int argc, const char* const *const argv, AAT* const args, const int follow_up_args);
int args_analyse_print(const AAT* const args);

