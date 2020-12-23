/*1952339 信08 张馨月*/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum class ITEM_TYPE { 
	Int,		//为避免和int冲突，采用首字母大写形式
	Double,
	String,
	Character,
	Null
};

#define OPEN_OPT_RDWR		0	//以读写方式打开（打不开文件则创建）
#define OPEN_OPT_RDONLY		1	//以只读方式打开（打不开则返回失败）

/* ---------------------------------------------------------------
	 允许加入其它需要的定义
	 const全局变量/static全局变量(慎用)/define/class/struct/enum/enum class/union等
   ---------------------------------------------------------------- */



/* ---------------------------------------------------------------
	 class CFT的定义，已有部分不要动，允许protected加入其它需要的定义
   ---------------------------------------------------------------- */
class CFT {
protected:
	string filename;
	fstream fp;

	int file_resize(int newsize);
	int file_length();
	void group_find(const char* group_name);
	void newsize_move_add(const int delta_len);
	void newsize_move_del(const int delta_len);
	int item_add_opt(const char* group_name, const char* item_name, const char* content);
	int item_update_opt(const char* group_name, const char* item_name, const char* content);

	/* ---------------------------------------------------------------
		 允许加入其它需要的定义（内部用）
	   ---------------------------------------------------------------- */

public:
	/* 不需要支持 CFT c1("c1.cfg", OPEN_OPT_RDWR)形式） */
	CFT();
	~CFT();

	int open(const char* cfgname, int opt);
	void close();

	/* 组增加与删除 */
	int group_add(const char* group_name);
	int group_del(const char* group_name);

	/* 项增加，多类型重载 */
	int item_add(const char* group_name, const char* item_name, const int item_value);
	int item_add(const char* group_name, const char* item_name, const double item_value);
	int item_add(const char* group_name, const char* item_name, const char *item_value);
	int item_add(const char* group_name, const char* item_name, const string &item_value);
	int item_add(const char* group_name, const char* item_name, const char item_value);
	int item_add(const char* group_name, const char* item_name);	//NULL

	/* 项删除 */
	int item_del(const char* group_name, const char* item_name);

	/* 项更新，多类型重载 */
	int item_update(const char* group_name, const char* item_name, const int item_value);
	int item_update(const char* group_name, const char* item_name, const double item_value);
	int item_update(const char* group_name, const char* item_name, const char* item_value);
	int item_update(const char* group_name, const char* item_name, const string &item_value);
	int item_update(const char* group_name, const char* item_name, const char item_value);
	int item_update(const char* group_name, const char* item_name);	//NULL

	/* 取某项的值，多类型重载 */
	int item_get_value(const char* group_name, const char* item_name, int &item_value);
	int item_get_value(const char* group_name, const char* item_name, double &item_value);
	int item_get_value(const char* group_name, const char* item_name, char *item_value);
	int item_get_value(const char* group_name, const char* item_name, string &item_value);
	int item_get_value(const char* group_name, const char* item_name, char &item_value);
	int item_get_value(const char* group_name, const char* item_name);

	/* ---------------------------------------------------------------
		 不允许加入其它需要的定义（对外不呈现）
	   ---------------------------------------------------------------- */
};

