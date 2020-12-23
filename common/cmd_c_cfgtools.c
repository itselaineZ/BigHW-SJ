/*1952339 信08 张馨月*/
/*1953492 李强 1953695 王虹量*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include "../include/cmd_c_cfgtools.h"
#include "../include/common_mybase_tool_c.h"

FILE* open_cfgfile(const char* cfgname, int opt)
{
	if (opt == 0) {
		FILE* In = fopen(cfgname, "rb");
		return In;
	}
	else if (opt == 1) {
		FILE* In = fopen(cfgname, "rb+");
		if (In == NULL) {
			In = fopen(cfgname, "w+");
			fclose(In);
			In = fopen(cfgname, "rb+");
		}
		return In;
	}
	return NULL;
}

void close_cfgfile(FILE* fp)
{
	fclose(fp);
}

static int file_length(FILE* fp)
{
	int file_len, now_pos;

	/* 取fp当前指针位置 */
	now_pos = ftell(fp);

	/* 将文件指针移动到最后，此时tellp的结果就是文件大小 */
	fseek(fp, 0, SEEK_END);
	file_len = ftell(fp);

	/* 指针移动回函数调用前的原位置 */
	fseek(fp, now_pos, SEEK_SET);

	return file_len;
}

static int file_resize(FILE* fp, int newsize)
{
	int now_pos = ftell(fp);
	/* 如果大小是负数则直接返回-1 */
	if (newsize < 0)
		return -1;

	_chsize(_fileno(fp), newsize);

	/* 如果当前文件指针超过了文件大小，则rewind */
	if (now_pos > newsize)
		rewind(fp);

	return 0;
}

static char find_first(const char* p)
{
	int i;
	for (i = 0; *(p + i) && (*(p + i) == ' ' || *(p + i) == '\t'); ++i)
		;
	return *(p+i);
}

static FILE* group_find(FILE *fp, const char* group_name)
{
	char str[150];
	int t = ftell(fp);
	int sz = file_length(fp)-1;
	while (ftell(fp) < sz) {
		t = ftell(fp);
		fgets(str, 150, fp);
		if (find_first(str) == '[') {
			int i;
			for (i = 0; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;
			for (++i; str[i] && (str[i] == ' ' || str[i] == '\t'); ++i)
				;
			if (str_in(group_name, str+i)) {
				int n = strlen(str);
				fseek(fp, -(int)strlen(str), SEEK_CUR);
				t = ftell(fp);
				return fp;
			}
		}
	}
	return NULL;
}

static int make_group_name(char* aim, const char* src)
{
	aim[0] = '[';
	strcpy(aim + 1, src);
	int len = strlen(aim);
	aim[len] = ']';
	aim[len + 1] = 0;
	++len;
	return len;
}

static void make_content(char* content, const char* item_name, const void* item_value, const enum ITEM_TYPE item_type)
{
	if (item_type == 0)
		sprintf(content, "%s=%d\r\n", item_name, *(int*)item_value);
	else if (item_type == 1)
		sprintf(content, "%s=%lf\r\n", item_name, *(double*)item_value);
	else if (item_type == 2)
		sprintf(content, "%s=%s\r\n", item_name, (char*)item_value);
	else if (item_type == 3)
		sprintf(content, "%s=%c\r\n", item_name, *(char*)item_value);
	else
		sprintf(content, "%s=\r\n", item_name);
}

static void newsize_move_add(FILE* fp, const int delta_len)
{
	file_resize(fp, file_length(fp)+delta_len);
	int now_pos = ftell(fp);
	fseek(fp, -1-delta_len, SEEK_END);
	char c;
	int t = ftell(fp);
 	while (t != now_pos) {
		c = fgetc(fp);
		fseek(fp, delta_len-1, SEEK_CUR);
		fprintf(fp, "%c", c);
		fseek(fp, -2-delta_len, SEEK_CUR);
		t = ftell(fp);
	}
	c = fgetc(fp);
	fseek(fp, delta_len-1, SEEK_CUR);
	fprintf(fp, "%c", c);
}

static void newsize_move_del(FILE* fp, const int delta_len)
{
	//fseek(fp, delta_len, SEEK_CUR);
	int t = ftell(fp), sz = file_length(fp);
	char c;
	do {
		c = fgetc(fp);
		fseek(fp, -delta_len-1, SEEK_CUR);
		t = ftell(fp);
		fprintf(fp, "%c", c);
		fseek(fp, delta_len, SEEK_CUR);
		t = ftell(fp);
	} while (!feof(fp) && t < sz);
	file_resize(fp, file_length(fp) - delta_len);
}

int group_add(FILE* fp, const char* group_name)
{
	rewind(fp);
	char aim[150];
	int len = make_group_name(aim, group_name);
	
	FILE* pos = group_find(fp, group_name);
	if (pos != NULL)
		return 0;
	fseek(fp, -1, SEEK_END);
	fprintf(fp, "%s\n\r", aim);
	return 1;
}

int group_del(FILE* fp, const char* group_name)
{
	rewind(fp);
	int delta_len = 0, n = 0;
	fp = group_find(fp, group_name);
	if (fp == NULL)
		return 0;

	char str[150];
	int t = ftell(fp);
	fgets(str, 150, fp);
	int len = strlen(str);
	int sz = file_length(fp)-1;

	while (fp && ftell(fp) < sz) {
		if (fp == NULL)
			return 0;
		delta_len = len;

		/*char c;
		while ((c = fgetc(fp)) != '[')
			++delta_len;*/
		int ll = 0;
		do {
			delta_len += ll;
			fgets(str, 150, fp);
			ll = strlen(str);
		} while (find_first(str) != '[');
		fseek(fp, -ll+1, SEEK_CUR);
		//fseek(fp, -delta_len-1, SEEK_CUR);
		int t = ftell(fp);
		newsize_move_del(fp, delta_len);
		++n;

		rewind(fp);
		fp = group_find(fp, group_name);
		if (fp == NULL)
			break;
		sz = file_length(fp)-1;
		fgets(str, 150, fp);
		len = strlen(str);
	}
	return n;
}

int item_add(FILE* fp, const char* group_name, const char* item_name, const void* item_value, const enum ITEM_TYPE item_type)
{
	rewind(fp);
	char str[150];
	char content[150];
	int len_item = strlen(item_name);
	int sz = file_length(fp)-1;

	if (group_name == NULL) {
		do {
			fgets(str, 150, fp);
			while (find_first(str) == '#')
				fgets(str, 150, fp);
			if (str_in(item_name, str) && (str[len_item] == ' ' || str[len_item] == '\t' || str[len_item] == '='))
				return 0;
		} while (ftell(fp) < sz);
		make_content(content, item_name, item_value, item_type);
		int len_content = strlen(content);
		file_resize(fp, file_length(fp) + len_content);
		fseek(fp, -len_content-1, SEEK_END);
		fprintf(fp, "%s", content);//直接末尾添加
		return 1;

	}
	else {
		fp = group_find(fp, group_name);
		if (fp == NULL)
			return 0;

		fgets(str, 150, fp);
		int len = strlen(str);
		make_content(content, item_name, item_value, item_type);
		int delta_len = strlen(content);

		if (ftell(fp) == sz) {
			int t = ftell(fp);
			newsize_move_add(fp, delta_len);
			fseek(fp, t, SEEK_SET);
			fprintf(fp, "%s", content);
			return 1;
		}

		do {
			fgets(str, 150, fp);
			while (find_first(str) == '#')
				fgets(str, 150, fp);
			if (str_in(item_name, str) && (str[len_item] == ' ' || str[len_item] == '\t' || str[len_item] == '='))
				return 0;
		} while (find_first(str) != '[' && ftell(fp) < sz);

		if (find_first(str) == '[') {
			int ll = strlen(str);
			fseek(fp, -ll, SEEK_CUR);
		}
		int t = ftell(fp);
		newsize_move_add(fp, delta_len);
		fseek(fp, t, SEEK_SET);
		fprintf(fp, "%s", content);
		return 1;
	}
}

int item_del(FILE* fp, const char* group_name, const char* item_name)
{
	rewind(fp);
	int n = 0;
	char str[150];
	int len_item = strlen(item_name);
	int delta_len = 0;
	int sz = file_length(fp)-1;

	if (group_name == NULL) {
		while (ftell(fp) < sz) {
			fgets(str, 150, fp);
			while (find_first(str) == '#')
				fgets(str, 150, fp);
			if (str_in(item_name, str) && (str[len_item] == ' ' || str[len_item] == '\t' || str[len_item] == '=')) {
				++n;
				int ll = strlen(str);
				//fseek(fp, -ll, SEEK_CUR);
				newsize_move_del(fp, ll);
				sz = file_length(fp)-1;
			}
		}
		return n;
	}
	else {
		fp = group_find(fp, group_name);
		if (fp == NULL)
			return 0;

		fgets(str, 150, fp);
		int len = strlen(str);

		do {
			fgets(str, 150, fp);
			while (find_first(str) == '#')
				fgets(str, 150, fp);
			if (str_in(item_name, str) && (str[len_item] == ' ' || str[len_item] == '\t' || str[len_item] == '=')) {
				++n;
				int ll = strlen(str);
				//fseek(fp, -ll, SEEK_CUR);
				newsize_move_del(fp, ll);
				sz = file_length(fp) - 1;
			}
		} while (find_first(str) != '[' && ftell(fp) < sz);
	}
	return n;
}

int item_update(FILE* fp, const char* group_name, const char* item_name, const void* item_value, const enum ITEM_TYPE item_type)
{
	rewind(fp);
	char str[150];
	int n = 0, t;
	int len_item = strlen(item_name);
	char content[150];
	make_content(content, item_name, item_value, item_type);
	int len_content = strlen(content);
	int sz = file_length(fp)-1;

	if (group_name == NULL) {
		do {
			fgets(str, 150, fp);
			while (find_first(str) == '#')
				fgets(str, 150, fp);
			if (str_in(item_name, str) && (str[len_item] == ' ' || str[len_item] == '\t' || str[len_item] == '=')) {
				if (n == 0) {
					int ll = strlen(str);
					fseek(fp, -ll, SEEK_CUR);
					t = ftell(fp);
					fseek(fp, ll, SEEK_CUR);
					newsize_move_del(fp, ll);
					fseek(fp, t, SEEK_SET);
					newsize_move_add(fp, len_content);
					fseek(fp, t, SEEK_SET);
					fprintf(fp, "%s", content);
				}
				else {
					int ll = strlen(str);
					fseek(fp, -ll, SEEK_CUR);
					t = ftell(fp);
					fseek(fp, ll, SEEK_CUR);
					newsize_move_del(fp, ll);
					fseek(fp, t, SEEK_SET);
				}
				++n;
			}
			sz = file_length(fp) - 1;
			t = ftell(fp);
		} while (ftell(fp) < sz);

		if (n == 0) {
			fseek(fp, -1, SEEK_END);
			t = ftell(fp);
			newsize_move_add(fp, len_content);
			fseek(fp, t, SEEK_SET);
			fprintf(fp, "%s", content);
			n = 1;
		}

		return n;
	}
	else {
		fp = group_find(fp, group_name);
		if (fp == NULL)
			return 0;

		fgets(str, 150, fp);
		int len = strlen(str);
		if (ftell(fp) == sz) {
			t = ftell(fp);
			newsize_move_add(fp, len_content);
			fseek(fp, t, SEEK_SET);
			fprintf(fp, "%s", content);
			return 1;
		}

		do {
			fgets(str, 150, fp);
			while (find_first(str) == '#')
				fgets(str, 150, fp);
			if (str_in(item_name, str) && (str[len_item] == ' ' || str[len_item] == '\t' || str[len_item] == '=')) {
				if (n == 0) {
					int ll = strlen(str);
					fseek(fp, -ll, SEEK_CUR);
					t = ftell(fp);
					fseek(fp, ll, SEEK_CUR);
					newsize_move_del(fp, ll);
					fseek(fp, t, SEEK_SET);
					newsize_move_add(fp, len_content);
					fseek(fp, t, SEEK_SET);
					fprintf(fp, "%s", content);
				}
				else {
					int ll = strlen(str);
					fseek(fp, -ll, SEEK_CUR);
					t = ftell(fp);
					fseek(fp, ll, SEEK_CUR);
					newsize_move_del(fp, ll);
					fseek(fp, t, SEEK_SET);
				}
				++n;
			}
			sz = file_length(fp)-1;
			t = ftell(fp);
		} while (find_first(str) != '[' && ftell(fp) < sz);

		if (n == 0) {
			if (find_first(str) == '[') {
				int ll = strlen(str);
				fseek(fp, -ll, SEEK_CUR);
			}
			t = ftell(fp);
			newsize_move_add(fp, len_content);
			fseek(fp, t, SEEK_SET);
			fprintf(fp, "%s", content);
			n = 1;
		}
		return n;
	}
}

int item_get_value(FILE* fp, const char* group_name, const char* item_name, void* item_value, const enum ITEM_TYPE item_type)
{
	rewind(fp);
	char str[150];
	int len_item = strlen(item_name);
	int n = 0;

	fp = group_find(fp, group_name);
	if (fp == NULL)
		return 0;

	fgets(str, 150, fp);
	int len = strlen(str);

	do {
		fgets(str, 150, fp);
		while (find_first(str) == '#')
			fgets(str, 150, fp);
		if (str_in(item_name, str) && (str[len_item] == ' ' || str[len_item] == '\t' || str[len_item] == '=')) {
			if (item_type == 0) {
				int rt = 0, i;
				for (i = len_item; str[i] < '0' || str[i] > '9'; ++i)
					;
				for (; str[i] >= '0' && str[i] <= '9'; ++i)
					rt = rt * 10 + str[i] - 48;
				*(int*)item_value = rt;
				return 1;
			}
			else if (item_type == 1) {
				double rt = 0.0;
				int i;
				for (i = len_item; str[i] < '0' || str[i] > '9'; ++i)
					;
				for (; str[i] >= '0' && str[i] <= '9'; ++i)
					rt = rt * 10 + str[i] - 48;
				++i;
				for (double j = 0.1; str[i] >= '0' && str[i] <= '9'; ++i, j /= 10.0)
					rt += (str[i] - 48) * j;
				*(double*)item_value = rt;
				return 1;
			}
			else if (item_type == 2) {
				int i = len_item;
				for (; str[i] != '='; ++i)
					;
				for (++i; str[i] == ' ' || str[i] == '\t'; ++i)
					;
				int j;
				for (j = 0; str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r'; ++i, ++j)
					*((char*)item_value + j) = str[i];
				*((char*)item_value + j) = 0;
				return 1;
			}
			else if (item_type == 3) {
				int i = len_item;
				for (; str[i] != '=' && str[i]; ++i)
					;
				for (++i; str[i] == ' ' || str[i] == '\t'; ++i)
					;
				*(char*)item_value = str[i];
				return 1;
			}
			else {
				int i = len_item;
				for (; str[i] != '='; ++i)
					;
				for (++i; str[i] == ' ' || str[i] == '\t'; ++i)
					;
				if (str[i] == '\n')
					return 0;
				else 
					return 1;
			}
		}
	} while (find_first(str) != '[' && !feof(fp));
	return 0;
}
