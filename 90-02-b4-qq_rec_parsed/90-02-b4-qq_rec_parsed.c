/*1952339 信08 张馨月*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "../include/common_mybase_tool_c.h"

struct val {
	const char* p;
	int rt;
};

const int maxorder = 6;
const int fix_col = 19;

const char* lst[][3] = { {"--stulist", "string", NULL},
						{"--qq_record", "string", NULL},
						{"--begin", "string", NULL},
						{"--end", "string", NULL},
						{"--stuno", "string", NULL},
						{"--only_zero", NULL, NULL},
						{NULL, NULL, NULL}
};
const char* type[] = { "string", "string", "string", "string", "string", NULL };
const char tg[] = { '-', '-', ' ', ':', ':', ' ', '-', '-' };

char* get_p(char* p)
{
	p += fix_col;
	if (*p == ' ')
		++p;
	int i = 0;
	while (*(p + i) != '(' && *(p + i) != '<')
		++i;
	*(p + i) = 0;
	return p;
}

int get_id(char* p, char(*stu)[50])
{
	int n = 0;
	char id[10];
	while (p != NULL && *p && *p != '-')
		id[n] = *p,
		++p, ++n;
	id[n] = 0;
	int i = 0;
	while (stu[i][0]) {
		int j = 0;
		while (j < n && id[j] == stu[i][j])
			++j;
		if (j == n)
			return i;
		++i;
	}
	return -1;
}

struct val get_value(const char* p, const char end)
{
	struct val rt;
	rt.rt = 0;
	while (*p != end && p != NULL && *p)
		rt.rt = rt.rt * 10 + *p - '0',
		++p;
	rt.p = p + 1;
	return rt;
}

int my_strcmp(const char* p, const char* q)//p所含为时间&&在q之前则返回0，否则返回正值
{
	if (*q < '0' || *q > '9' || *p < '0' || *p > '9')
		return 1;

	int a[6], b[6];
	struct val t;

	int i = 0;
	while (i < 6) {
		t = get_value(p, tg[i]);
		a[i] = t.rt, p = t.p;
		t = get_value(q, tg[i]);
		b[i] = t.rt, q = t.p;
		++i;
	}

	i = 0;
	while (i < 6) {
		if (a[i] < b[i])
			return 0;
		if (a[i] > b[i])
			return 1;
		++i;
	}
	return 0;
}

int check_tag(char* p)
{
	int i;
	for (i = 0; p != NULL && *p && i <= 7; ++i)
		for (; p != NULL && *p && (*p) != tg[i]; ++p)
			;
	return i == 8;
}

void usage(char* msg)
{
	msg += sprintf(msg, "%s", "\nUsage: QQ_rec_parsed.exe { --stulist | --qq_record | --begin | --end | {--stuno} | {--only_zero} }\n");
	msg += sprintf(msg, "%s", "\n\t\t必选项：\n");
	msg += sprintf(msg, "%s", "\t\t   --stulist filename   : 学生列表文件名(缺省:stulist.txt)\n");
	msg += sprintf(msg, "%s", "\t\t   --qq_record filename : 导出的聊天记录文件名(缺省:2019-高程.txt)\n");
	msg += sprintf(msg, "%s", "\t\t   --begin timestr      : 起始时间(时间串格式为yyyy-mm-dd hh:mm:ss，加引号)\n");
	msg += sprintf(msg, "%s", "\t\t   --end timestr        : 结束时间(时间串格式为yyyy-mm-dd hh:mm:ss，加引号)\n");
	msg += sprintf(msg, "%s", "\t\t   注：未检查时间串正确性\n");
	msg += sprintf(msg, "%s", "\t\t可选项：\n");
	msg += sprintf(msg, "%s", "\t\t   --stuno stuno        : 指定某个学生(无此选项则全部学生)\n");
	msg += sprintf(msg, "%s", "\t\t   --only_zero          : 仅显示0发言学生(指定--stuno时本项无效)\n\n");
	msg += sprintf(msg, "%s", "e.g.  QQ_rec_parsed.exe --begin \"2020 - 03 - 05 10:00 : 00\" --end \"2020 - 03 - 05 11 : 50 : 00\"\n");
	msg += sprintf(msg, "%s", "\t\t\t: 统计\"2019-高程.txt\"中在stulist.txt列表中的学生在2020.3.5 10 : 00~11 : 50间的发言数量\n");
	msg += sprintf(msg, "%s", "\tQQ_rec_parsed.exe --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --only_zero\n");
	msg += sprintf(msg, "%s", "\t\t\t: 统计\"2019-高程.txt\"中在stulist.txt列表中的学生在2020.3.5 10 : 00~11 : 50间0发言数量\n");
	msg += sprintf(msg, "%s", "\tQQ_rec_parsed.exe --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --stuno 1951234\n");
	msg += sprintf(msg, "%s", "\t\t\t: 统计\"2019-高程.txt\"中在stulist.txt列表中的学生1951234在2020.3.5 10 : 00~11 : 50间的发言数量\n");
	msg += sprintf(msg, "%s", "\tQQ_rec_parsed.exe --stulist list1.txt --qq_record 2019 - 高程1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" : 统计2020.3.5 10 : 00~11 : 50间所有学生的发言数量\n");
	msg += sprintf(msg, "%s", "\tQQ_rec_parsed.exe --stulist list1.txt --qq_record 2019 - 高程1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --only_zero : 统计2020.3.5 10 : 00~11 : 50间所有0发言的学生\n");
	msg += sprintf(msg, "%s", "\tQQ_rec_parsed.exe --stulist list1.txt --qq_record 2019 - 高程1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --stuno 1951234 : 统计2020.3.5 10 : 00~11 : 50间1951234的发言数量\n");
}

int main(int argc, char* argv[])
{
	char message[5000];
	memset(message, 0, sizeof message);
	char* msg = message;
	char infom[6][20];
	memset(infom, 0, sizeof infom);
	if (argc < 3 || !check_lst(argc, argv, lst, type, infom, msg)) {
		msg += strlen(msg);
		usage(msg);
	}
	else {
		int tt = 1;
		while (tt <= 1) {
			++tt;
			if (infom[0][0] == 0)
				strcpy(infom[0], "stulist.txt");
			if (infom[1][0] == 0)
				strcpy(infom[1], "2019-高程.txt");

			FILE* Stu;
			Stu = fopen(infom[0], "r");
			if (Stu == NULL) {
				msg += sprintf(msg, "%s", "文件打开失败！\n");
				break;
			}
			char stu[250][50];
			memset(stu, 0, sizeof stu);
			int i = 0;
			while (feof(Stu) == 0) {
				fgets(stu[i], 45, Stu);
				int j = strlen(stu[i]) - 1;
				if (stu[i][j] == '\n')
					stu[i][j] = 0;
				++i;
			}

			FILE* In = fopen(infom[1], "r");
			if (In == NULL) {
				msg += sprintf(msg, "文件打开失败！\n");
				break;
			}

			char content[100];
			memset(content, 0, sizeof content);
			int l_cnt = 0, id, not_in_list = 0;
			int spk[230] = { 0 };

			while (feof(In) == 0) {
				++l_cnt;
				fgets(content, 95, In);
				if (my_strcmp(infom[2], content) == 0) {
					msg += sprintf(msg, "First Line No : %d\n", l_cnt);
					break;
				}
			}
			while (my_strcmp(content, infom[3]) == 0) {
				id = get_id(get_p(content), stu);
				if (id == -1)
					++not_in_list;
				else
					spk[id]++;
				if (feof(In))
					break;
				fgets(content, 95, In);
				if (ferror(In))
					clearerr(In);
				++l_cnt;
				while (!check_tag(content) && feof(In) == 0)
					fgets(content, 95, In), ++l_cnt, clearerr(In);
				if (!check_tag(content) && feof(In) == 0)
					break;
			}
			msg += sprintf(msg, "Last Line No : %d\n", l_cnt);
			msg += sprintf(msg, "%s", "名单\t\t\t发言次数\n");
			if (!infom[4][0] && !infom[5][0]) {
				int i = 0;
				while (stu[i][0])
					msg += sprintf(msg, "%s\t\t\t%d\n", stu[i], spk[i]),
					++i;
			}
			else if (infom[4][0]) {
				id = get_id(infom[4], stu);
				if (id != -1)
					msg += sprintf(msg, "%s\t\t\t%d\n", stu[id], spk[id]);
			}
			else {
				int i = 0;
				while (stu[i][0]) {
					if (!spk[i])
						msg += sprintf(msg, "%s\t\t\t%d\n", stu[i], spk[i]);
					++i;
				}
			}
			msg += sprintf(msg, "\n搜索日志文件总行数 :%d", l_cnt);
			fclose(In);
			fclose(Stu);
		}
	}
	printf("%s\n", message);
	return 0;
}
