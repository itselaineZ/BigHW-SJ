/*1952339 ��08 ��ܰ��*/
#pragma once

char* tran_char(char* rt, const char* a);

int check_lst(int argc, char* argv[], const char* lst[][3], const char* type[], char(*infom)[20], char *msg);/*�������Ƿ���ȷ*/

int str_in(const char* a, const char* b);/*���a���Ƿ�Ϊb��ǰ׺*/

char* str_aft_str(char* a, const char* b);/*��a��ĩβ���b��*/
char* str_aft_ch(char* a, const char b);/*��a��ĩβ���b�ַ�*/

int strcmp_case_not(const char* a, const char* b);/*��Сд�����бȽ�*/

int s_gets(const char*src, char* aim);/*����һ���ַ�����\n����*/
int s_getstr(const char* src, char* aim);/*����һ��������\t \n \r spc����*/
