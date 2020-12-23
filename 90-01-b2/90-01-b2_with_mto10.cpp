/*1952339 信08 张馨月*/
#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstring>
#include"../include/cmd_console_tools.h"
#include"./90-01-b2_with_mto10.h"
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

/*输出一块拼图*/
void cout_puzzle(int x, int y, const int num, const int bg_colr, const int fg_colr)//╔═╗╚╝╢╤╧╟
{
	cct_gotoxy(x, y);
	cct_showstr(x, y, "╔═╗", bg_colr, fg_colr);
	cct_showstr(x, y + 1, "║", bg_colr, fg_colr);
	cct_showstr(x + 4, y + 1, "║", bg_colr, fg_colr);
	cct_setcolor(bg_colr, fg_colr);
	cct_gotoxy(x + 2, y + 1);
	if (num < 10)
		cout << ' ';
	cout << num;
	cct_setcolor();
	y += 2;
	cct_showstr(x, y, "╚═╝", bg_colr, fg_colr);
}

/*输出伪图形界面*/
void cout_table_puzzle(int id, int x, int y, int row, int column, const int (*table)[Maxn], int sllp)
{//╔═╗╚║╝╢╤╧╟├┤┬┼┴│─
	int cc = 6 * column + 2 + (id != 5) * (column - 1) * 2, rr = 3 * row + 2 + (id != 5) * (row - 1);
	cct_showstr(x, y, "╔", COLOR_WHITE, COLOR_BLACK);
	cct_showstr(x, y + rr - 1, "╚", COLOR_WHITE, COLOR_BLACK);
	int deltax = 0, deltay = 0;
	for (int j = 1; j <= column; ++j) {
		cct_showstr(2 + (j - 1) * 6 + deltax, y, hengxian[0], COLOR_WHITE, COLOR_BLACK);
		cct_showstr(2 + (j - 1) * 6 + deltax, y + rr - 1, hengxian[0], COLOR_WHITE, COLOR_BLACK);
		if (id != 5 && j != column) {
			cct_showstr(2 + j * 6 + deltax, y, "╤", COLOR_WHITE, COLOR_BLACK);
			cct_showstr(2 + j * 6 + deltax, y + rr - 1, "╧", COLOR_WHITE, COLOR_BLACK);
			deltax += 2;
		}
	}
	cct_showstr(x + cc, y, "╗", COLOR_WHITE, COLOR_BLACK);
	cct_showstr(x + cc, y + rr - 1, "╝", COLOR_WHITE, COLOR_BLACK);
	++y;
	for (int i = 1; i <= row; ++i) {
		for (int k = 0; k < 3; ++k) {
			cct_showstr(x, y + (i - 1) * 3 + deltay + k, "║", COLOR_WHITE, COLOR_BLACK);
			cct_showstr(x + cc, y + (i - 1) * 3 + deltay + k, "║", COLOR_WHITE, COLOR_BLACK);
		}
		if (id != 5 && i != row) {
			cct_showstr(x, y + i * 3 + deltay, "╟", COLOR_WHITE, COLOR_BLACK);
			cct_showstr(x + cc, y + i * 3 + deltay, "╢", COLOR_WHITE, COLOR_BLACK);
			++deltay;
		}
	}
	deltax = deltay = 0;
	for (int i = 1; i <= row; ++i) {
		for (int j = 1; j <= column; ++j) {
			cout_puzzle(2 + (j - 1) * 6 + deltax, y + (i - 1) * 3 + deltay, table[i][j], table[i][j]);
			if (id != 5 && j != column) {
				for (int k = 0; k < 3; ++k)
					cct_showstr(2 + j * 6 + deltax, y + (i - 1) * 3 + deltay + k, "│", COLOR_WHITE, COLOR_BLACK);
				deltax += 2;
			}
		}
		for (int j = 1; j <= column && id != 5 && i != row; ++j) {
			cct_showstr(2 + (j - 1) * 6 + (j - 1) * 2, y + i * 3 + deltay, hengxian[1], COLOR_WHITE, COLOR_BLACK);
			if (j != column)
				cct_showstr(2 + j * 6 + (j - 1) * 2, y + i * 3 + deltay, "┼", COLOR_WHITE, COLOR_BLACK);
		}
		deltax = 0;
		deltay += (id != 5);
	}
	x = 2;
	int width = (id == 5 ? 3 : 4);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; Sleep(sllp), ++j)
			cout_puzzle(x + 2 * width * (j - 1), y + width * (i - 1), table[i][j], table[i][j]);
	cct_gotoxy(cc, rr);
}

/*数字掉落 id：1表示伪图形界面*/
void table_move(int id, int row, int column, int(*table)[Maxn], int(*fnd)[Maxn], int sllp)
{
	for (int i = row - 1; i; --i)
		for (int j = 1; j <= column; ++j)
			if (!table[i + 1][j]) {
				int k;
				for (k = i + 1; k <= row && !table[k][j]; ++k)
					if (table[i][j] && id) {
						for (int p = 1; p <= 4; Sleep(sllp), ++p) {
							cout_puzzle(2 + 8 * (j - 1), 2 + 4 * (k - 2) + p - 1, table[i][j], COLOR_WHITE, COLOR_WHITE);
							cout_puzzle(2 + 8 * (j - 1), 2 + 4 * (k - 2) + p, table[i][j], table[i][j]);
						}
						cct_showstr(2 + 8 * (j - 1), 2 + 4 * (k - 2) + 3, hengxian[1], COLOR_WHITE, COLOR_BLACK);
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
void change_neighbor(bool id, int row, int column, const int table[Maxn][Maxn], const int fnd[Maxn][Maxn])
{
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j)
			if (fnd[i][j]) {
				if (!id)
					cout_puzzle(2 + 8 * (j - 1), 2 + 4 * (i - 1), table[i][j], COLOR_HYELLOW, COLOR_HBLUE);
				else
					cout_puzzle(2 + 8 * (j - 1), 2 + 4 * (i - 1), table[i][j], table[i][j]);
			}
}

/*合并并清除选中块*/
void puzzle_clr(int posr, int posc, int row, int column, int(*table)[Maxn], int(*fnd)[Maxn], bool id, int *maxv)
{
	++table[posr][posc];
	fnd[0][1] = fnd[0][1] > table[posr][posc] ? fnd[0][1] : table[posr][posc];
	if (maxv)
		*maxv = *maxv > table[posr][posc] ? *maxv : table[posr][posc];
	if(id)
		cout_puzzle(2 + 8 * (posc - 1), 2 + 4 * (posr - 1), table[posr][posc], table[posr][posc], COLOR_HRED);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j)
			if (fnd[i][j] && (i != posr || j != posc)) {
				table[i][j] = 0;
				if(id)
					cout_puzzle(2 + 8 * (j - 1), 2 + 4 * (i - 1), table[i][j], COLOR_WHITE, COLOR_WHITE);
			}
}

