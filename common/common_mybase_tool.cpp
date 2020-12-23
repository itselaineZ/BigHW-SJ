/*1952339 信08 张馨月*/
#include<iostream>
#include<cstdio>
#include "../include/cmd_console_tools.h"
using namespace std;

void line_clr(int x, int y)/*清除一行从(x,y)开始的内容*/
{
	cct_gotoxy(x, y);
	int c, l, b_c, b_l;
	cct_getconsoleborder(c, l, b_c, b_l);
	cct_showstr(x, y, " ", COLOR_BLACK, COLOR_BLACK, c - x, c - x);
	cct_gotoxy(x, y);
	cct_setcolor();
}

bool check_lst(int argc, char* argv[], const char* lst[][3], const char *type[], char (*infom)[20])
{
	for (int i = 1; i < argc; ++i) {
		bool tg = 0;
		for (int j = 0; lst[j][0] && !tg; ++j) 
			if (strcmp(lst[j][0], argv[i]) == 0) {
				tg = 1;
				if (i != argc - 1 && argv[i + 1][0] == '-' && lst[j][1] != NULL) {
					cout << "参数" << lst[j][0] << "的参数不足（类型：" << type[j][0] << "）\n";
					return 0;
				}
				else if (lst[j][1] != NULL) {
					++i;
					strcpy_s(infom[j], argv[i]);
				}
				else
					infom[j][0] = '1';
			}
		if (!tg) {
			cout << "参数[" << argv[i] << "]非法\n";
			return 0;
		}
	}
	return 1;
}
bool str_in(const char* a, const char* b) 
{
	int i;
	for (i = 0; a[i] && b[i] && a[i] == b[i]; ++i);
	return a[i] == 0;
}

char* str_aft(char* a, const char* b)
{
	char* p = a;
	for (; *p; ++p)
		;
	for (; *b; *p = *b, ++p, ++b)
		;
	*p = 0;
	return a;
}
char* str_aft(char* a, const char b)
{
	char* p = a;
	for (; *p; ++p)
		;
	*p = b, ++p;
	*p = 0;
	return a;
}

int strcmp_case_not(const char* a, const char* b)
{
	for (; a && b && *a && *b; ++a, ++b) {
		char x = *a, y = *b;
		if (x >= 'A' && x <= 'Z')
			x += 'a' - 'A';
		if (y >= 'A' && y <= 'Z')
			y += 'a' - 'A';
		if (x != y)
			return x - y;
	}
	return 0;
}
