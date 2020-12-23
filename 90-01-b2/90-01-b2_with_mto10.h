/*1952339 信08 张馨月*/
#pragma once

#include "../include/cmd_console_tools.h"

const int Maxn = 8 + 2;
const int INF = 0x3f3f3f3f;
const int slp = 0;
const int dd[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
const int data_interval[3][2] = { {5, 8}, {5, 8}, {5, 20} };//读入变量限制条件
const int Color[21] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 2, 3, 4, 5 };
const int cols = 80;
const int rows = 25;
const char hengxian[2][10] = { "═══", "───" };

int mto10_main(bool tg);

void line_clr(int x, int y);/*清除一行从(x,y)开始的内容*/

bool check_in_mp(int posc, int posr, int row, int column);/*检查是否在图内*/

void memst(int(*a)[Maxn]);/*数组清零*/
void mempy(int(*a)[Maxn], const int b[Maxn][Maxn]);/*数组复制b给a*/

void game_find_same_BFS(int posr, int posc, int row, int column, const int table[Maxn][Maxn], int(*fnd)[Maxn]);/*Bfs查找周围相同数字*/

void cout_puzzle(int x, int y, const int num, const int bg_colr, const int fg_colr = COLOR_BLACK);/*输出一块拼图*/

void change_neighbor(bool id, int row, int column, const int table[Maxn][Maxn], const int fnd[Maxn][Maxn]);/*改变相邻颜色状态, 0:未选中->选中*/
void puzzle_clr(int posr, int posc, int row, int column, int(*table)[Maxn], int(*fnd)[Maxn], bool id = 1, int *maxv = 0);/*合并并清除选中块*/
void table_move(int id, int row, int column, int(*table)[Maxn], int(*fnd)[Maxn], int sllp = slp);/*数字掉落 id：0表示非伪图形界面*/
void cout_table_puzzle(int id, int x, int y, int row, int column, const int (*table)[Maxn], int sllp = slp);/*输出伪图形界面*/
