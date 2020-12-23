/*1952339 信08 张馨月*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include "../include/lib_mto10_net_tools.h"
#include "../include/lib_md5_sha_tools.h"
#include "./90-01-b2_with_mto10.h"
using namespace std;

/*求整数绝对值*/
int int_abs(int x)
{
	return x < 0 ? -x : x;
}

/*分离出数字*/
void get_number(const char *mp, int row, int column, int(*table)[Maxn])
{
	for(int i = 1; i <= row; ++ i)
		for (int j = 1; j <= column; ++j) {
			if (*mp >= '0' && *mp <= '9')
				table[i][j] = *mp - '0';
			else
				table[i][j] = *mp - 'A' + 10;
			++ mp;
		}
}

/*枚举可能的位置，求当前图上能获得的最大得分*/

void pos_enumerate_small_first_double_plus(int row, int column, int* pointx, int* pointy, const int table[Maxn][Maxn], int(*fnd)[Maxn])
{
	memst(fnd);
	int now = 0, tb = INF;
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j) {
			game_find_same_BFS(i, j, row, column, table, fnd);
			now = 3 * table[i][j] * (fnd[0][0] == 1 ? 0 : fnd[0][0]);
			if (now && table[i][j] < tb) {
				tb = table[i][j];
				*pointx = j;
				*pointy = i;
			}
			else if (now && table[i][j] == tb) {
				if (j < *pointx) {
					*pointx = j;
					*pointy = i;
				}
			}
		}
	game_find_same_BFS(*pointy, *pointx, row, column, table, fnd);
}

void pos_enumerate(int row, int column, int *pointx, int *pointy, const int table[Maxn][Maxn], int(*fnd)[Maxn], int maxv)
{
	if (row <= 5 && column <= 5)
		pos_enumerate_small_first_double_plus(row, column, pointx, pointy, table, fnd);
	else
		pos_enumerate_small_first_double_plus(row, column, pointx, pointy, table, fnd);
}

/*输出游戏信息*/
void cout_inf(int x, int y, int gme_id, int stp, int sco, int maxv=0)
{
	cct_gotoxy(x, y);
	cct_setcolor();
	cout << "GameID		：" <<gme_id << '\n';
	cout << "Step		：" << stp << "			";
	cout << "Score		：" << sco << '\n';
	cout << "MaxValue	：";
	cct_getxy(x, y);
	line_clr(x, y);
	if (!maxv)
		cout << "---";
	else
		cout << maxv;
}

/*游戏过程展示界面初始化*/
void puzzle_screen(int row, int column, const int table[Maxn][Maxn], int gme_id, int stp, int score)
{
	int cc = 8 * column + 2, rr = 1 + 4 * row;
	cct_cls();
	cct_setconsoleborder(cc + 2, rr + 8);
	int x = 0, y = 0;
	line_clr(x, y);
	cout << "游戏开始！当前界面为 " << row << " 行 " << column << " 列";
	cout_table_puzzle(9, 0, 1, row, column, table, 0);
	cct_getxy(x, y);
	cout_inf(0, y + 1, gme_id, stp, score);
}

/*游戏过程界面数字填充*/
void tran_puzzle_rebuild(int row, int column, int gme_id, int stp, int score, const int maxv, const int table[Maxn][Maxn], char* const Old_mp)
{
	char* p = Old_mp;
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j, ++p)
			if (*p == '0')
				cout_puzzle(2 + 8 * (j - 1), 2 + 4 * (i - 1), table[i][j], table[i][j]);
	int cc = 8 * column + 2, rr = 1 + 4 * row;
	cout_inf(0, rr + 1, gme_id, stp, score, maxv);
}

/*选中当前格子及其将消去的格子*/
void pos_chosen(int x, int y, int row, int column, const int table[Maxn][Maxn], const int fnd[Maxn][Maxn])
{
	change_neighbor(0, row, column, table, fnd);
	cout_puzzle(2 + 8 * (x - 1), 2 + 4 * (y - 1), table[y][x], COLOR_HYELLOW, COLOR_HRED);
	cct_gotoxy(0, 9 + 4 * row);
}

/*找到原始数据中的地图*/
bool trans_svrp(char *svrp, char **mp)
{
	*mp = 0;
	char* p = svrp;
	char key_wd[] = "FinalMap = ";
	for (; p - svrp < RECVBUF_LEN; ++p) {
		int i = 0;
		for (; i < 11 && key_wd[i] == *(p + i); ++i)
			;
		if (i == 11) {
			*mp = p + i;
			break;
		}
	}
	if (*mp == 0)
		return 0;
	return 1;
}

bool trans_svrp(char *svrp, char **mp, char **old_mp)
{
	*mp = *old_mp = 0;
	char* p = svrp;
	char key_wdnw[] = "NewMap = ", key_wdol[] = "OldMap = ";
	for (; p - svrp < RECVBUF_LEN; ++p) {
		int i = 0;
		for (; i < 9 && key_wdol[i] == *(p + i); ++i)
			;
		if (i == 9) {
			*old_mp = p+i;
			break;
		}
	}
	for (; p - svrp < RECVBUF_LEN; ++p) {
		int i = 0;
		for (; i < 9 && key_wdnw[i] == *(p+i); ++i)
			;
		if (i == 9) {
			*mp = p+i;
			break;
		}
	}
	if (*mp == NULL || *old_mp == NULL)
		return 0;
	return 1;
}

/*找到原始数据中的stp、score*/
bool trans_svrp(char* svrp, int *stp, int *score)
{
	*stp = *score = 0;
	char key_wdstp[] = "Step = ", key_wdsco[] = "Score = ";
	char* p = svrp;
	for (; *p; ++p) {
		int i;
		for (i = 0; i < 7 && key_wdstp[i] == *(p + i); ++i)
			;
		if (i == 7) {
			p += i;
			while (*p >= '0' && *p <= '9') {
				*stp = *stp * 10 + *p - '0';
				++p;
			}
			break;
		}
	}
	for(; *p; ++ p){
		int i;
		for (i = 0; i < 8 && key_wdsco[i] == *(p + i); ++i)
			;
		if (i == 8) {
			p += i;
			while (*p >= '0' && *p <= '9') {
				*score = *score * 10 + *p - '0';
				++p;
			}
			break;
		}
	}
	return *stp && *score;
}

/*检查游戏结束*/
bool game_check_end(char *svrp)
{
	bool rt = 0;
	char* p = svrp;
	char key_wd[3][15] = { "GameOver", "GameFinished", "GameTimeout" };
	for (; *p; ++p) {
		int i;
		for (i = 0; i < 8 && key_wd[0][i] == *(p+i); ++i)
			;
		if (i == 8) {
			rt = 1;
			break;
		}
		for (i = 0; i < 12 && key_wd[1][i] == *(p + i); ++i)
			;
		if (i == 12) {
			rt = 1;
			break;
		}
		for (i = 0; i < 11 && key_wd[2][i] == *(p + i); ++i)
			;
		if (i == 11) {
			rt = 1;
			break;
		}
	}
	return rt;
}

