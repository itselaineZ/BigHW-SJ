/*1952339 ��08 ��ܰ��*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../include/common_mybase_tool.h"
using namespace std;

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
const char* type[] = {"string", "string", "string", "string", "string", NULL};
const char tg[] = {'-', '-', ' ', ':', ':', ' ', '-', '-'};

char* get_p(char *p)
{
	p += fix_col;
	if (*p == ' ')
		++p;
	int i;
	for (i = 0; *(p + i) != '(' && *(p + i) != '<'; ++i)
		;
	*(p + i) = 0;
	return p;
}

int get_id(char *p, const char (*stu)[50])
{
	int rt = 0, n;
	char id[10];
	for (n = 0; p != NULL && *p && *p != '-'; ++p, ++n)
		id[n] = *p;
	id[n] = 0;
	for (int i = 0; stu[i][0]; ++i) {
		int j;
		for (j = 0; j < n && id[j] == stu[i][j]; ++j)
			;
		if (j == n)
			return i;
	}
	return -1;
}

val get_value(const char *p, const char end)
{
	val rt;
	rt.rt = 0;
	for (; *p != end && p != NULL && *p; ++p)
		rt.rt = rt.rt * 10 + *p - '0';
	rt.p = p + 1;
	return rt;
}

bool my_strcmp(const char *p, const char *q)//p����Ϊʱ��&&��q֮ǰ�򷵻�0�����򷵻���ֵ
{
	if (*q < '0' || *q > '9' || *p < '0' || *p > '9')
		return 1;

	int a[6], b[6];
	val t;

	for (int i = 0; i < 6; ++i) {
		t = get_value(p, tg[i]);
		a[i] = t.rt, p = t.p;
		t = get_value(q, tg[i]);
		b[i] = t.rt, q = t.p;
	}

	for (int i = 0; i < 6; ++i) {
		if (a[i] < b[i])
			return 0;
		if (a[i] > b[i])
			return 1;
	}
	return 0;
}

bool check_tag(char *p)
{
	int i;
	for (i = 0; p != NULL && *p && i <= 7; ++i)
		for (; p != NULL && *p && (*p) != tg[i]; ++p)
			;
	return i == 8;
}

void usage(ostringstream &msg)
{
	msg << "\nUsage: QQ_rec_parsed.exe { --stulist | --qq_record | --begin | --end | {--stuno} | {--only_zero} }\n";
	msg << "\n\t\t��ѡ�\n";
	msg << "\t\t   --stulist filename   : ѧ���б��ļ���(ȱʡ:stulist.txt)\n";
	msg << "\t\t   --qq_record filename : �����������¼�ļ���(ȱʡ:2019-�߳�.txt)\n";
	msg << "\t\t   --begin timestr      : ��ʼʱ��(ʱ�䴮��ʽΪyyyy-mm-dd hh:mm:ss��������)\n";
	msg << "\t\t   --end timestr        : ����ʱ��(ʱ�䴮��ʽΪyyyy-mm-dd hh:mm:ss��������)\n";
	msg << "\t\t   ע��δ���ʱ�䴮��ȷ��\n";
	msg << "\t\t��ѡ�\n";
	msg << "\t\t   --stuno stuno        : ָ��ĳ��ѧ��(�޴�ѡ����ȫ��ѧ��)\n";
	msg << "\t\t   --only_zero          : ����ʾ0����ѧ��(ָ��--stunoʱ������Ч)\n\n";
	msg << "e.g.  QQ_rec_parsed.exe --begin \"2020 - 03 - 05 10:00 : 00\" --end \"2020 - 03 - 05 11 : 50 : 00\"\n";
	msg << "\t\t\t: ͳ��\"2019-�߳�.txt\"����stulist.txt�б��е�ѧ����2020.3.5 10 : 00~11 : 50��ķ�������\n";
	msg << "\tQQ_rec_parsed.exe --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --only_zero\n";
	msg << "\t\t\t: ͳ��\"2019-�߳�.txt\"����stulist.txt�б��е�ѧ����2020.3.5 10 : 00~11 : 50��0��������\n";
	msg << "\tQQ_rec_parsed.exe --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --stuno 1951234\n";
	msg << "\t\t\t: ͳ��\"2019-�߳�.txt\"����stulist.txt�б��е�ѧ��1951234��2020.3.5 10 : 00~11 : 50��ķ�������\n";
	msg << "\tQQ_rec_parsed.exe --stulist list1.txt --qq_record 2019 - �߳�1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" : ͳ��2020.3.5 10 : 00~11 : 50������ѧ���ķ�������\n";
	msg << "\tQQ_rec_parsed.exe --stulist list1.txt --qq_record 2019 - �߳�1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --only_zero : ͳ��2020.3.5 10 : 00~11 : 50������0���Ե�ѧ��\n";
	msg << "\tQQ_rec_parsed.exe --stulist list1.txt --qq_record 2019 - �߳�1.txt --begin \"2020-03-05 10:00:00\" --end \"2020-03-05 11:50:00\" --stuno 1951234 : ͳ��2020.3.5 10 : 00~11 : 50��1951234�ķ�������\n";
}

int main(int argc, char *argv[])
{
	ostringstream msg;
	char infom[6][20] = { 0 };
	if (argc < 3 || !check_lst(argc, argv, lst, type, infom)) {
		usage(msg);
		cout << msg.str() << endl;
		return 0;
	}
	if (infom[0][0] == 0)
		strcpy_s(infom[0], "stulist.txt");
	if (infom[1][0] == 0)
		strcpy_s(infom[1], "2019-�߳�.txt");

	ifstream Stu(infom[0], ios::in);
	if (Stu.is_open() == 0) {
		msg << "�ļ���ʧ�ܣ�\n";
		cout << msg.str() << endl;
		return -1;
	}
	char stu[250][50] = {0};
	for (int i = 0; Stu.peek() != EOF; ++ i)
		Stu.getline(stu[i], 45);

	ifstream In(infom[1], ios::in);
	if (In.is_open() == 0) {
		msg << "�ļ���ʧ�ܣ�\n";
		cout << msg.str() << endl;
		return -1;
	}

	char content[100];
	int l_cnt = 0, id, not_in_list = 0;
	int spk[230] = {0};

	while (In.peek() != EOF) {
		++l_cnt;
		In.getline(content, 95);
		if (my_strcmp(infom[2], content) == 0) {
			msg << "First Line No : " << l_cnt << endl;
			break;
		}
	}
	while (my_strcmp(content, infom[3]) == 0) {
		id = get_id(get_p(content), stu);
		if (id == -1)
			++not_in_list;
		else
			spk[id]++;
		if (In.peek() == EOF)
			break;
		In.getline(content, 95);
		if (In.good() == 0)
			In.clear();
		++l_cnt;
		while (!check_tag(content) && In.peek() != EOF)
			In.getline(content, 95), ++l_cnt, In.clear();
		if (!check_tag(content) && In.peek() == EOF)
			break;
	}
	msg << "Last Line No : " << l_cnt << endl;
	msg << "����\t\t\t���Դ���\n";
	if (!infom[4][0] && !infom[5][0]) {
		for (int i = 0; stu[i][0]; ++i)
			msg << stu[i] << '\t' << spk[i] << endl;
	}
	else if (infom[4][0]) {
		id = get_id(infom[4], stu);
		if (id != -1)
			msg << stu[id] << '\t' << spk[id] << endl;
	}
	else{
		for (int i = 0; stu[i][0]; ++i)
			if (!spk[i])
				msg << stu[i] << '\t' << spk[i] << endl;
	}
	msg << "\n������־�ļ������� :" << l_cnt;

	cout << msg.str() << endl;
	In.close();
	Stu.close();
	return 0;
}