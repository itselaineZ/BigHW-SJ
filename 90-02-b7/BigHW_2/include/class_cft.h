/*1952339 ��08 ��ܰ��*/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum class ITEM_TYPE { 
	Int,		//Ϊ�����int��ͻ����������ĸ��д��ʽ
	Double,
	String,
	Character,
	Null
};

#define OPEN_OPT_RDWR		0	//�Զ�д��ʽ�򿪣��򲻿��ļ��򴴽���
#define OPEN_OPT_RDONLY		1	//��ֻ����ʽ�򿪣��򲻿��򷵻�ʧ�ܣ�

/* ---------------------------------------------------------------
	 �������������Ҫ�Ķ���
	 constȫ�ֱ���/staticȫ�ֱ���(����)/define/class/struct/enum/enum class/union��
   ---------------------------------------------------------------- */



/* ---------------------------------------------------------------
	 class CFT�Ķ��壬���в��ֲ�Ҫ��������protected����������Ҫ�Ķ���
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
		 �������������Ҫ�Ķ��壨�ڲ��ã�
	   ---------------------------------------------------------------- */

public:
	/* ����Ҫ֧�� CFT c1("c1.cfg", OPEN_OPT_RDWR)��ʽ�� */
	CFT();
	~CFT();

	int open(const char* cfgname, int opt);
	void close();

	/* ��������ɾ�� */
	int group_add(const char* group_name);
	int group_del(const char* group_name);

	/* �����ӣ����������� */
	int item_add(const char* group_name, const char* item_name, const int item_value);
	int item_add(const char* group_name, const char* item_name, const double item_value);
	int item_add(const char* group_name, const char* item_name, const char *item_value);
	int item_add(const char* group_name, const char* item_name, const string &item_value);
	int item_add(const char* group_name, const char* item_name, const char item_value);
	int item_add(const char* group_name, const char* item_name);	//NULL

	/* ��ɾ�� */
	int item_del(const char* group_name, const char* item_name);

	/* ����£����������� */
	int item_update(const char* group_name, const char* item_name, const int item_value);
	int item_update(const char* group_name, const char* item_name, const double item_value);
	int item_update(const char* group_name, const char* item_name, const char* item_value);
	int item_update(const char* group_name, const char* item_name, const string &item_value);
	int item_update(const char* group_name, const char* item_name, const char item_value);
	int item_update(const char* group_name, const char* item_name);	//NULL

	/* ȡĳ���ֵ������������ */
	int item_get_value(const char* group_name, const char* item_name, int &item_value);
	int item_get_value(const char* group_name, const char* item_name, double &item_value);
	int item_get_value(const char* group_name, const char* item_name, char *item_value);
	int item_get_value(const char* group_name, const char* item_name, string &item_value);
	int item_get_value(const char* group_name, const char* item_name, char &item_value);
	int item_get_value(const char* group_name, const char* item_name);

	/* ---------------------------------------------------------------
		 ���������������Ҫ�Ķ��壨���ⲻ���֣�
	   ---------------------------------------------------------------- */
};

