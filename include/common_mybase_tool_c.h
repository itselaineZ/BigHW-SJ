/*1952339 信08 张馨月*/
#pragma once

char* tran_char(char* rt, const char* a);

int check_lst(int argc, char* argv[], const char* lst[][3], const char* type[], char(*infom)[20], char *msg);/*检查参数是否正确*/

int str_in(const char* a, const char* b);/*检查a串是否为b串前缀*/

char* str_aft_str(char* a, const char* b);/*在a串末尾添加b串*/
char* str_aft_ch(char* a, const char b);/*在a串末尾添加b字符*/

int strcmp_case_not(const char* a, const char* b);/*大小写不敏感比较*/

int s_gets(const char*src, char* aim);/*读入一行字符，到\n结束*/
int s_getstr(const char* src, char* aim);/*读入一个串，到\t \n \r spc结束*/
