/*1952339 信08 张馨月*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<io.h>
#include<direct.h>
#include<windows.h>
#include"../include/common_mybase_tool.h"
using namespace std;

struct FI {
	char name[50];
	bool subdir;
	FI() { memset(name, 0, sizeof name); subdir = 0; }
	FI(char* p, bool x) { strcpy_s(name, p); subdir = x; }
};

const char* flg[][2] = { {"└─", "\\---"}, {"├─", "+---"} };

void check_subdir(const char *ad, bool f, char* bef, bool flg_tg)
{
	_chdir(ad);

	FI files[100];
	char address[50] = {"./"};
	_finddata_t file;
	long int k, HANDLE;
	int cnt = 0;
	k = HANDLE = _findfirst("*.*", &file);
	while (k != -1) {
		if ((f || (file.attrib & _A_SUBDIR)) && strcmp(file.name, ".") && strcmp(file.name, ".."))
			files[cnt++] = FI(file.name, (file.attrib & _A_SUBDIR));
		k = _findnext(HANDLE, &file);
	}

	FI t;
	for(int i = 0; i < cnt; ++ i)
		for(int j = i+1; j < cnt; ++j)
			if (strcmp_case_not(files[i].name, files[j].name) > 0) {
				t = files[i];
				files[i] = files[j];
				files[j] = t;
			}
	--cnt;
	char aft[100] = {0};
	strcpy_s(aft, bef);
	str_aft(aft, "│ ");
	for (int i = 0; i < cnt; ++i) {
		if(*bef)
			cout << bef;
		cout << flg[1][flg_tg] << files[i].name << '\n';
		if (files[i].subdir) {
			strcpy_s(address, "./");
			check_subdir(str_aft(address, files[i].name), f, aft, flg_tg);
		}
	}
	if (cnt >= 0) {
		if(*bef)
			cout << bef;
		cout << flg[0][flg_tg] << files[cnt].name << '\n';
		if (files[cnt].subdir) {
			strcpy_s(address, "./");
			strcpy_s(aft, bef);
			str_aft(aft, "   ");
			check_subdir(str_aft(address, files[cnt].name), f, aft, flg_tg);
		}
	}
	_chdir("../");
}

int main(int argc, char* argv[]) 
{
	if (argc > 3) {
		cout << "参数错误\n";
		return 0;
	}
	char infom[2][100] = {0};
	bool flg_tg = 0;
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "/f") == 0 || strcmp(argv[i], "/F") == 0)
			strcpy_s(infom[1], argv[i]);
		else if (strcmp(argv[i], "/a") == 0)
			flg_tg = 1;
		else if (_chdir(argv[i]) != 0) {
			cout << "地址错误\n";
			return 0;
		}
		else
			strcpy_s(infom[0], argv[i]);
	}

	char szDriveName[100] = {0};
	DWORD dwVolumeSerialNumber;
	DWORD dwMaximumComponentLength;
	DWORD dwFileSystemFlags;
	char szFileSystemNameBuffer[100] = {0};
	char szDrive[100];
	int i;
	for (i = 0; argv[0][i] != '\\'; ++i)
		szDrive[i] = argv[0][i];
	szDrive[i] = '\\';
	szDrive[i + 1] = 0;
	GetVolumeInformationA(szDrive, szDriveName, 100, &dwVolumeSerialNumber, &dwMaximumComponentLength, &dwFileSystemFlags, szFileSystemNameBuffer, 100);
	cout << "卷 " << szDriveName << " 的文件夹 PATH 列表\n";
	cout << "卷序列号为 " << dwVolumeSerialNumber << "\n";

	char address[30] = {"./"};
	char bef[500] = {0};
	if (infom[0][0])
		check_subdir(str_aft(address, infom[0]), (infom[1][0] ? 1 : 0), bef, flg_tg);
	else
		check_subdir("", (infom[1][0] ? 1 : 0), bef, flg_tg);
	return 0;
}