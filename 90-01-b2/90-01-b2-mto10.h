/*1952339 信08 张馨月*/
#pragma once

#include "../include/lib_mto10_net_tools.h"
#include "./90-01-b2_with_mto10.h"

/*求整数绝对值*/
int int_abs(int x);

/*输出游戏信息*/
void cout_inf(int x, int y, int gme_id, int stp, int sco, int maxv = 0);
/*游戏过程展示界面初始化*/
void puzzle_screen(int row, int column, const int table[Maxn][Maxn], int gme_id, int stp, int score);
/*游戏过程界面数字填充*/
void tran_puzzle_rebuild(int row, int column, int gme_id, int stp, int score, const int maxv, const int table[Maxn][Maxn], char* const Old_mp);
/*分离出数字*/
void get_number(const char* mp, int row, int column, int(*table)[Maxn]);

/*枚举可能的位置，求当前图上能获得的最大得分*/
void pos_enumerate(int row, int column, int* pointx, int* pointy, const int table[Maxn][Maxn], int(*fnd)[Maxn], int maxv);
void pos_enumerate_small_first_double_plus(int row, int column, int* pointx, int* pointy, const int table[Maxn][Maxn], int(*fnd)[Maxn]);

/*选中当前格子及其将消去的格子*/
void pos_chosen(int x, int y, int row, int column, const int table[Maxn][Maxn], const int fnd[Maxn][Maxn]);


/*找到原始数据中的新地图*/
bool trans_svrp(char* svrp, char** mp, char** old_mp);
bool trans_svrp(char* svrp, char** mp);
/*找到原始数据中的步数、得分*/
bool trans_svrp(char* svrp, int* stp, int* score);
/*检查游戏结束*/
bool game_check_end(char* svrp);
