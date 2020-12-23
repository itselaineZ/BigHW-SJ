#pragma once

void line_clr(int x, int y);/*清除一行从(x,y)开始的内容*/

bool check_lst(int argc, char* argv[], const char* lst[][3], const char* type[], char (*infom)[20]);/*检查参数是否正确*/

bool str_in(const char *a, const char *b);/*检查a串是否包含于b串*/

char* str_aft(char *a, const char *b);
char* str_aft(char* a, const char b);

int strcmp_case_not(const char *a, const char *b);
