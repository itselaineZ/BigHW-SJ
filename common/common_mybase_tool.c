/*1952339 信08 张馨月*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

char* tran_char(char* rt, const char* a)
{
	int i = 0;
	while (*(a + i))
		*(rt + i) = *(a + i),
		++ i;
	*(rt + i) = 0;
	return rt;
}

int check_lst(int argc, char* argv[], const char* lst[][3], const char* type[], char(*infom)[20], char* msg)
{
	char tmp[50];
	int i = 1;
	while (i < argc) {
		int tg = 0;
		int j = 0;
		while (lst[j][0] && !tg) {
			if (strcmp(lst[j][0], argv[i]) == 0) {
				tg = 1;
				if (i != argc - 1 && argv[i + 1][0] == '-' && lst[j][1] != NULL) {
					if (msg) {
						tran_char(tmp, lst[j][0]);
						msg += sprintf(msg, "参数%s的参数不足（类型：", tmp);
						tran_char(tmp, type[j]);
						msg += sprintf(msg, "%s）\n", tmp);
					}
					else
						printf("参数%s的参数不足（类型：%s）\n", lst[j][0], type[j]);
					return 0;
				}
				else if (lst[j][1] != NULL) {
					++i;
					strcpy(infom[j], argv[i]);
				}
				else
					infom[j][0] = '1';
			}
			++j;
		}
		if (!tg) {
			msg += sprintf(msg, "参数[%s]非法\n", tran_char(tmp, argv[i]));
			return 0;
		}
		++i;
	}
	return 1;
}

int str_in(const char* a, const char* b)
{
	int i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		++i;
	return a[i] == 0;
}

char* str_aft_str(char* a, const char* b)
{
	char* p = a;
	while (*p)
		++ p;
	while (*b)
		*p = *b, ++p, ++b;
	*p = 0;
	return a;
}
char* str_aft_ch(char* a, const char b)
{
	char* p = a;
	while (*p)
		++p;
	*p = b, ++p;
	*p = 0;
	return a;
}

int strcmp_case_not(const char* a, const char* b)
{
	while (a && b && *a && *b) {
		char x = *a, y = *b;
		if (x >= 'A' && x <= 'Z')
			x += 'a' - 'A';
		if (y >= 'A' && y <= 'Z')
			y += 'a' - 'A';
		if (x != y)
			return x - y;
		++a, ++b;
	}
	return 0;
}

int s_gets(const char* src, char* aim) {
	int i = 0;
	while (src[i] != '\n' && src[i] != EOF && src[i])
		aim[i] = src[i],
		++ i;
	return i + 1;
}

int s_getstr(const char* src, char* aim)
{
	int i = 0, j = 0;
	while (src + i && *(src + i) && (*(src + i) == '\t' || *(src + i) == ' ' || *(src + i) == '\n' || *(src + i) == '\r'))
		++ i;
	while (src + i && *(src + i) && *(src + i) != '\t' && *(src + i) != '\n' && *(src + i) != '\r' && *(src + i) != ' ')
		*(aim + j) = *(src + i),
		++i, ++ j;
	*(aim + j) = 0;
	return i;
}