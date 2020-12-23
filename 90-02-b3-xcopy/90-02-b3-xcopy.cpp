/*1952339 信08 张馨月*/
#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstring>
#include<io.h>
#include<stdlib.h>
#include<direct.h>
#include<windows.h>
#include "../include/common_mybase_tool.h"
using namespace std;

const char* lst[] = {"/s", "/e", "/h", "/i", NULL};

bool check_null(char *ad)
{
	_chdir(ad);
	
	_finddata_t file;
	long int k, HANDLE;
	k = HANDLE = _findfirst("*.*", &file);
	while (k != -1) {
		if (strcmp(file.name, ".") && strcmp(file.name, ".."))
			return 0;
		k = _findnext(HANDLE, &file);
	}
	return 1;
}

int file_copy(char* src, char* aim, int copy_way, long int attrib)
{
	int cnt_file = 0;
	_mkdir(aim);
	if (attrib & _A_ARCH)
		SetFileAttributesA(aim, FILE_ATTRIBUTE_ARCHIVE);
	if (attrib & _A_HIDDEN)
		SetFileAttributesA(aim, FILE_ATTRIBUTE_HIDDEN);
	if (attrib & _A_NORMAL)
		SetFileAttributesA(aim, FILE_ATTRIBUTE_NORMAL);
	if (attrib & _A_SYSTEM)
		SetFileAttributesA(aim, FILE_ATTRIBUTE_SYSTEM);
	if (attrib & _A_SUBDIR)
		SetFileAttributesA(aim, FILE_ATTRIBUTE_DIRECTORY);
	if (attrib & _A_RDONLY)
		SetFileAttributesA(aim, FILE_ATTRIBUTE_READONLY);
	_chdir(src);

	char src_nxt[100], aim_nxt[100];

	_finddata_t file;
	long int k, HANDLE;
	k = HANDLE = _findfirst("*.*", &file);
	while (k != -1ll) {
		if (strcmp(file.name, ".") && strcmp(file.name, "..")) {
			if ((file.attrib & _A_SUBDIR)) {
				if (copy_way != 2 && copy_way != 3 && (!(file.attrib & _A_HIDDEN) && !(file.attrib & _A_SYSTEM))) {
					strcpy_s(src_nxt, src);
					strcpy_s(aim_nxt, aim);
					str_aft(src_nxt, '\\'), str_aft(src_nxt, file.name);
					str_aft(aim_nxt, '\\'), str_aft(aim_nxt, file.name);
					if((copy_way == 0 && !check_null(src_nxt)) || copy_way != 0)
						cnt_file += file_copy(src_nxt, aim_nxt, copy_way, file.attrib);
					_chdir(src);
				}
			}
			else if((!(file.attrib & _A_HIDDEN) && !(file.attrib & _A_SYSTEM)) || copy_way == 2){
				strcpy_s(src_nxt, src);
				strcpy_s(aim_nxt, aim);
				str_aft(src_nxt, '\\'), str_aft(src_nxt, file.name);
				str_aft(aim_nxt, '\\'), str_aft(aim_nxt, file.name);
				cout << file.name << endl;
				ifstream In(src_nxt, ios::in | ios::binary);
				ofstream Out(aim_nxt, ios::out | ios::binary);
				char c;
				while (In.get(c)) {
					Out.put(c);
				}
				if (file.attrib & _A_ARCH)
					SetFileAttributesA(aim_nxt, FILE_ATTRIBUTE_ARCHIVE);
				if (file.attrib & _A_HIDDEN)
					SetFileAttributesA(aim_nxt, FILE_ATTRIBUTE_HIDDEN);
				if (file.attrib & _A_NORMAL)
					SetFileAttributesA(aim_nxt, FILE_ATTRIBUTE_NORMAL);
				if (file.attrib & _A_SYSTEM)
					SetFileAttributesA(aim_nxt, FILE_ATTRIBUTE_SYSTEM);
				if (file.attrib & _A_RDONLY)
					SetFileAttributesA(aim_nxt, FILE_ATTRIBUTE_READONLY);
				cnt_file++;
				In.close();
				Out.close();
			}
		}
		k = _findnext(HANDLE, &file);
	}
	return cnt_file;
	return cnt_file;
	return cnt_file;
}

int content_copy(char *ad, ofstream &Out, const int copy_way)
{
	int cnt_file = 0;

	_chdir(ad);

	char ad_nxt[100];
	_finddata_t file;
	long int k, HANDLE;
	k = HANDLE = _findfirst("*.*", &file);
	while (k != -1ll) {
		if (strcmp(file.name, ".") && strcmp(file.name, "..")) {
			if ((file.attrib & _A_SUBDIR)) {
				if (copy_way != 2 && copy_way != 3 && (!(file.attrib & _A_HIDDEN) && !(file.attrib & _A_SYSTEM))) {
					strcpy_s(ad_nxt, ad);
					str_aft(ad_nxt, '\\');
					str_aft(ad_nxt, file.name);
					if (!check_null(ad_nxt))
						cnt_file += content_copy(ad_nxt, Out, copy_way);
					_chdir(ad);
				}
			}
			else if ((!(file.attrib & _A_HIDDEN) && !(file.attrib & _A_SYSTEM)) || copy_way == 2) {
				strcpy_s(ad_nxt, ad);
				str_aft(ad_nxt, '\\');
				str_aft(ad_nxt, file.name);
				ifstream In(ad_nxt, ios::in | ios::binary);
				char c;
				while (In.get(c)) {
					Out.put(c);
				}
				cnt_file++;
				In.close();
			}
		}
	}
	return cnt_file;
}

int main(int argc, char* argv[])
{
	if (argc < 4) {
		cout << "缺少参数\n";
		return 0;
	}

	cout << "目标" << argv[2] << "是文件名\n还是目录名\n";
	cout << "(F = 文件，D = 目录)? ";
	char ord;
	cin >> ord;
	bool out_f = (ord == 'd' || ord == 'D');
	
	char src[100], aim[100];
	strcpy_s(src, argv[0]);
	int i;
	for (i = strlen(src) - 1; src[i] && src[i] != '\\'; --i)
		;
	src[i] = 0;
	strcpy_s(aim, src);
	str_aft(src, '\\');
	str_aft(aim, '\\');
	str_aft(src, argv[1]);
	str_aft(aim, argv[2]);

	if (_access(src, 0) == -1) {
		cout << "源  " << argv[1] << " 不存在\n";
		cout << "复制了 0 个文件\n";
		return 0;
	}
	if (_access(aim, 0) == 0) {
		cout << "目标 " << argv[2] << " 已存在\n";
		cout << "复制了 0 个文件\n";
		return 0;
	}

	bool find_src = 0;
	_finddata_t file;
	long int k, HANDLE;
	k = HANDLE = _findfirst("*.*", &file);
	while (k != -1) {
		if (strcmp(file.name, argv[1]) == 0) {
			find_src = 1;
			break;
		}
		k = _findnext(HANDLE, &file);
	}
	if ((file.attrib & _A_SUBDIR) == 0) {
		cout << "源 " << argv[1] << " 不是文件夹\n";
		cout << "复制了 0 个文件\n";
		return 0;
	}

	int file_cnt = 0;

	if (strcmp(argv[3], lst[0]) == 0) {
		if (out_f)
			file_cnt = file_copy(src, aim, 0, file.attrib);
		else {
			ofstream Out(aim, ios::out | ios::binary);
			file_cnt = content_copy(src, Out, 0);
			Out.close();
		}
	}
	else if (strcmp(argv[3], lst[1]) == 0) {
		if (out_f)
			file_cnt = file_copy(src, aim, 1, file.attrib);
		else {
			ofstream Out(aim, ios::out | ios::binary);
			file_cnt = content_copy(src, Out, 1);
			Out.close();
		}

	}
	else if (strcmp(argv[3], lst[2]) == 0) {
		if (out_f)
			file_cnt = file_copy(src, aim, 2, file.attrib);
		else {
			ofstream Out(aim, ios::out | ios::binary);
			file_cnt = content_copy(src, Out, 2);
			Out.close();
		}
	}
	else if (strcmp(argv[3], lst[3]) == 0) {
		if (out_f)
			file_cnt = file_copy(src, aim, 3, file.attrib);
		else {
			ofstream Out(aim, ios::out | ios::binary);
			file_cnt = content_copy(src, Out, 3);
			Out.close();
		}
	}
	else {
		cout << "参数错误\n";
		return 0;
	}

	cout << "\n复制了 " << file_cnt << " 个文件\n";
	return 0;
}
/*

_A_ARCH（存档）

_A_HIDDEN（隐藏）

_A_NORMAL（正常）

_A_RDONLY（只读）

_A_SUBDIR（文件夹）

_A_SYSTEM（系统）
*/