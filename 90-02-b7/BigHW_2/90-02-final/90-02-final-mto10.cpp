/*1952339 信08 张馨月*/
#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstring>
#include "../include/class_gmw.h"
#include "./90-02-final-mto10.h"
using namespace std;

/*数组清零*/
void memst(int(*a)[Maxn])
{
	for (int i = 0; i < Maxn; ++i)
		for (int j = 0; j < Maxn; ++j)
			a[i][j] = 0;
}

/*数组复制b给a*/
void mempy(int(*a)[Maxn], const int b[Maxn][Maxn])
{
	for (int i = 0; i < Maxn; ++i)
		for (int j = 0; j < Maxn; ++j)
			a[i][j] = b[i][j];
}

/*检查是否在图内*/
bool check_in_mp(int posc, int posr, int row, int column)
{
	return posc >= 1 && posc <= column && posr >= 1 && posr <= row;
}

/*Bfs查找周围相同数字*/
void game_find_same_BFS(int posr, int posc, int row, int column, const int table[Maxn][Maxn], int(*fnd)[Maxn])
{
	memst(fnd);
	int value = table[posr][posc];
	int Q[100][2], q = 0, fro = 0;
	Q[++q][0] = posr, Q[q][1] = posc;
	fnd[posr][posc] = 1;
	while (fro < q) {
		++fro;
		posr = Q[fro][0];
		posc = Q[fro][1];
		for (int i = 0; i < 4; ++i) {
			int xx = posc + dd[i][0];
			int yy = posr + dd[i][1];
			if (check_in_mp(xx, yy, row, column) && !fnd[yy][xx] && table[yy][xx] == value) {
				fnd[yy][xx] = 1;
				Q[++q][0] = yy, Q[q][1] = xx;
			}
		}
	}
	fnd[0][0] = q;
}

/*数字掉落 id：1表示伪图形界面*/
void table_move(CONSOLE_GRAPHICS_INFO mto, int id, int row, int column, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO *cb)
{
	for (int i = row - 1; i; --i)
		for (int j = 1; j <= column; ++j)
			if (!table[i + 1][j]) {
				int k;
				for (k = i + 1; k <= row && !table[k][j]; ++k)
					if (table[i][j] && id) {
						mto.gmw_draw_block(k - 2, j - 1, 0, cb);
						mto.gmw_draw_block(k - 1, j - 1, table[i][j], cb);
					}
				--k;
				table[k][j] = table[i][j];
				table[i][j] = 0;
			}
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j)
			fnd[i][j] = (table[i][j] == 0);
}

/*改变相邻颜色状态, 0:未选中->选中*/
void change_neighbor(CONSOLE_GRAPHICS_INFO mto, bool id, int row, int column, const int table[Maxn][Maxn], const int fnd[Maxn][Maxn], const BLOCK_DISPLAY_INFO* cb, const int (*opt)[2])
{
	const BLOCK_DISPLAY_INFO cb1[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL},
		{10, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL},
		{1, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL},
		{2, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL},
		{3, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL},
		{4, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL},
		{5, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL},
		{6, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL},
		{7, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL},
		{8, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL},
		{9, (CCT_COLOR)opt[1][0], (CCT_COLOR)opt[1][1], NULL}
	};
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j)
			if (fnd[i][j]) {
				if (!id)
					mto.gmw_draw_block(i - 1, j - 1, table[i][j], cb1);
				else
					mto.gmw_draw_block(i - 1, j - 1, table[i][j], cb);
			}
}

/*合并并清除选中块*/
void puzzle_clr(CONSOLE_GRAPHICS_INFO mto, int posr, int posc, int row, int column, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO* cb, bool id, int* maxv)
{

	++table[posr][posc];
	fnd[0][1] = fnd[0][1] > table[posr][posc] ? fnd[0][1] : table[posr][posc];
	if (maxv)
		*maxv = *maxv > table[posr][posc] ? *maxv : table[posr][posc];
	if (id)
		mto.gmw_draw_block(posr - 1, posc - 1, table[posr][posc], cb);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j)
			if (fnd[i][j] && (i != posr || j != posc)) {
				table[i][j] = 0;
				if (id)
					mto.gmw_draw_block(i - 1, j - 1, 0, cb);
			}
}

