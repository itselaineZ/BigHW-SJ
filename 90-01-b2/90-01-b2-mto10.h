/*1952339 ��08 ��ܰ��*/
#pragma once

#include "../include/lib_mto10_net_tools.h"
#include "./90-01-b2_with_mto10.h"

/*����������ֵ*/
int int_abs(int x);

/*�����Ϸ��Ϣ*/
void cout_inf(int x, int y, int gme_id, int stp, int sco, int maxv = 0);
/*��Ϸ����չʾ�����ʼ��*/
void puzzle_screen(int row, int column, const int table[Maxn][Maxn], int gme_id, int stp, int score);
/*��Ϸ���̽����������*/
void tran_puzzle_rebuild(int row, int column, int gme_id, int stp, int score, const int maxv, const int table[Maxn][Maxn], char* const Old_mp);
/*���������*/
void get_number(const char* mp, int row, int column, int(*table)[Maxn]);

/*ö�ٿ��ܵ�λ�ã���ǰͼ���ܻ�õ����÷�*/
void pos_enumerate(int row, int column, int* pointx, int* pointy, const int table[Maxn][Maxn], int(*fnd)[Maxn], int maxv);
void pos_enumerate_small_first_double_plus(int row, int column, int* pointx, int* pointy, const int table[Maxn][Maxn], int(*fnd)[Maxn]);

/*ѡ�е�ǰ���Ӽ��佫��ȥ�ĸ���*/
void pos_chosen(int x, int y, int row, int column, const int table[Maxn][Maxn], const int fnd[Maxn][Maxn]);


/*�ҵ�ԭʼ�����е��µ�ͼ*/
bool trans_svrp(char* svrp, char** mp, char** old_mp);
bool trans_svrp(char* svrp, char** mp);
/*�ҵ�ԭʼ�����еĲ������÷�*/
bool trans_svrp(char* svrp, int* stp, int* score);
/*�����Ϸ����*/
bool game_check_end(char* svrp);
