/*1952339 信08 张馨月*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include "../include/common_mybase_tool_c.h"

struct pr {
	int dir, file;
};

struct FI {
	char name[50];
	int subdir;
};

struct FI FI_set(struct FI a, char* p, int x)
{
	if (p == NULL)
		memset(a.name, 0, sizeof a.name);
	else
		strcpy(a.name, p);
	a.subdir = x;
	return a;
}

const char* flg[][2] = { {" -- ", "\\---"}, {"|-- ", "+---"} };

struct pr check_subdir(const char* ad, int d, char* bef, int flg_tg)
{
	struct pr rt;
	rt.file = rt.dir = 0;
	DIR* dir = opendir(ad);
	chdir(ad);

	struct FI files[100], tmp;
	memset(tmp.name, 0, sizeof tmp.name);
	tmp.subdir = 0;
	char address[50] = { "./" };

	struct dirent* entry;
	int cnt = 0;
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		struct stat st;
		stat(entry->d_name, &st);

		if (!d || S_ISDIR(st.st_mode))
			files[cnt++] = FI_set(tmp, entry->d_name, S_ISDIR(st.st_mode) != 0);
	}

	struct FI t;
	int i = 0;
	while (i < cnt) {
		int j = i + 1;
		while (j < cnt) {
			if (strcmp(files[i].name, files[j].name) > 0) {
				t = files[i];
				files[i] = files[j];
				files[j] = t;
			}
			++j;
		}
		++i;
	}
	--cnt;

	char aft[100] = { 0 };
	strcpy(aft, bef);
	str_aft_str(aft, "|   ");
	i = 0;
	struct pr tp;
	while (i < cnt) {
		if (*bef)
			printf("%s", bef);
		printf("%s%s\n", flg[1][flg_tg], files[i].name);
		if (files[i].subdir) {
			++rt.dir;
			strcpy(address, "./");
			tp = check_subdir(str_aft_str(address, files[i].name), d, aft, flg_tg);
			rt.dir += tp.dir;
			rt.file += tp.file;
		}
		else
			++rt.file;
		++i;
	}
	if (cnt >= 0) {
		if (*bef)
			printf("%s", bef);
		printf("%s%s\n", flg[0][flg_tg], files[cnt].name);
		if (files[cnt].subdir) {
			++rt.dir;
			strcpy(address, "./");
			strcpy(aft, bef);
			str_aft_str(aft, "    ");
			tp = check_subdir(str_aft_str(address, files[cnt].name), d, aft, flg_tg);
			rt.dir += tp.dir;
			rt.file += tp.file;
		}
		else
			++rt.file;
	}
	chdir("..");
	return rt;
}

int main(int argc, char* argv[])
{
	if (argc > 3) {
		printf("参数错误\n");
		return 0;
	}
	char infom[2][100];
	memset(infom, 0, sizeof infom);
	int flg_tg = 0;
	int i = 1;
	while (i < argc) {
		if (strcmp(argv[i], "-d") == 0)
			strcpy(infom[1], argv[i]);
		else if (chdir(argv[i]) != 0) {
			printf("地址错误\n");
			return 0;
		}
		else {
			strcpy(infom[0], argv[i]);
			chdir("..");
		}
		++i;
	}

	puts(".");
	char address[30] = { "./" };
	char bef[500] = { 0 };
	struct pr rt;
	if (infom[0][0])
		rt = check_subdir(str_aft_str(address, infom[0]), (infom[1][0] ? 1 : 0), bef, flg_tg);
	else {
		char now_dir[100], pth[300];
		getcwd(pth, 300);
		int p = strlen(pth) - 1;
		while (p && pth[p] != '/')
			--p;
		if (pth[p] == '/')
			++p;
		strcpy(now_dir, pth + p);
		chdir("..");
		rt = check_subdir(now_dir, (infom[1][0] ? 1 : 0), bef, flg_tg);
	}
	printf("\n%d directories, %d files\n", rt.dir, rt.file);
	return 0;
}
