/*1952339 ��08 ��ܰ��*/
#pragma once


bool check_lst(int argc, char* argv[], const char* lst[][3], const char* type[], char(*infom)[20]);/*�������Ƿ���ȷ*/

bool str_in(const char* a, const char* b);/*���a���Ƿ������b��*/

char* str_aft(char* a, const char* b);
char* str_aft(char* a, const char b);

int strcmp_case_not(const char* a, const char* b);
