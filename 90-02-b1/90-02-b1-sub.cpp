/*1952339 –≈08 ’≈‹∞‘¬*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"../90-02-b1/90-02-b1-tool.h"
using namespace std;

int get_next_num(const bool new_seed, const unsigned int seed)
{
	if (new_seed)
		srand(seed);
	return rand() % 10;
}

void panel_print(const POS PANEL) 
{
	int N = 3*PANEL.y, M = 3*PANEL.x;
	cct_cls();
	cct_setconsoleborder(2*M+50, N+5);
	int r = 0, c = 0;
	cct_showstr(2, r, "®T", pnl_bg_clr, pnl_fg_clr, M);
	cct_showstr(2, r+N+1, "®T", pnl_bg_clr, pnl_fg_clr, M);
	for (r = 1; r <= N; ++r) {
		cct_showstr(c, r, "®U", pnl_bg_clr, pnl_fg_clr);
		cct_showstr(2*M+2, r, "®U", pnl_bg_clr, pnl_fg_clr);
	}
	cct_showstr(0, 0, "®X", pnl_bg_clr, pnl_fg_clr);
	cct_showstr(0, N + 1, "®^", pnl_bg_clr, pnl_fg_clr);
	cct_showstr(2*M + 2, 0, "®[", pnl_bg_clr, pnl_fg_clr);
	cct_showstr(2*M + 2, N + 1, "®a", pnl_bg_clr, pnl_fg_clr);

	cct_showstr(2 * M + 4, 0, "®T", pnl_bg_clr, pnl_fg_clr, tip_width/2);
	cct_showstr(2 * M + 4, N+1, "®T", pnl_bg_clr, pnl_fg_clr, tip_width/2);
	for (r = 1; r <= N; ++r) {
		cct_showstr(2 * M + 4, r, "®U", pnl_bg_clr, pnl_fg_clr);
		cct_showstr(2 * M + tip_width + 4, r, "®U", pnl_bg_clr, pnl_fg_clr);
	}
	cct_showstr(2 * M + 4, 0, "®X", pnl_bg_clr, pnl_fg_clr);
	cct_showstr(2 * M + 4, N + 1, "®^", pnl_bg_clr, pnl_fg_clr);
	cct_showstr(2 * M + tip_width + 4, 0, "®[", pnl_bg_clr, pnl_fg_clr);
	cct_showstr(2 * M + tip_width + 4, N + 1, "®a", pnl_bg_clr, pnl_fg_clr);
	cct_setcolor();
}

void puzzle_print(const int key, const POS P, const bool clr)//°Ô°Ó
{
	if (!key)	return;
	cct_showstr(P.x, P.y, "®X®T®[", pzl_bg_clr*clr, pzl_fg_clr*clr);
	cct_showstr(P.x, P.y+1, "®U°Ó®U", pzl_bg_clr*clr, pzl_fg_clr*clr);
	cct_showstr(P.x, P.y+2, "®^®T®a", pzl_bg_clr*clr, pzl_fg_clr*clr);
}

void number_print(const NUM X, const POS P, const bool clr)
{
	for (int y = 0; y < num_row; ++y)
		for (int x = 0; x < num_col; ++x) {
			if (X.pos == 1 && P.x+6*x > 1 && P.y+3*y > 0)
				puzzle_print(num[X.number][y][x], POS(P.x + x * 6, P.y + y * 3), clr);
			else if (X.pos == 2 && P.x+6*y > 1 && P.y+(2-x)*3 > 0)
				puzzle_print(num[X.number][y][x], POS(P.x + y * 6, P.y + (2 - x) * 3), clr);
			else if (X.pos == 3 && P.x+(2-x)*6 > 1 && P.y+(4-y)*3 > 0)
				puzzle_print(num[X.number][y][x], POS(P.x + (2 - x) * 6, P.y + (4 - y) * 3), clr);
			else if(X.pos == 4 && P.x+(4-y)*6 > 1 && P.y+3*x > 0)
				puzzle_print(num[X.number][y][x], POS(P.x + (4 - y) * 6, P.y + x * 3), clr);
		}
	cct_setcolor();
}

bool check_mp(const NUM X, const POS P, const bool (*mp)[Maxm])
{
	bool rt = 1;
	for (int y = 0; y < num_row; ++y)
		for (int x = 0; x < num_col; ++x)
			if (num[X.number][y][x]) {
				if (X.pos == 1 && (P.y - wt_y) / 3 + y >= 0 && (P.x - wt_x) / 6 + x >= 0)
					rt = rt && !mp[(P.y - wt_y) / 3 + y][(P.x - wt_x) / 6 + x];
				else if (X.pos == 2 && (P.y - wt_y) / 3 + 2 - x >= 0 && (P.x - wt_x) / 6 + y >= 0)
					rt = rt && !mp[(P.y - wt_y) / 3 + 2 - x][(P.x - wt_x) / 6 + y];
				else if (X.pos == 3 && (P.y - wt_y) / 3 + 4 - y >= 0 && (P.x - wt_x) / 6 + 2 - x >= 0)
					rt = rt && !mp[(P.y - wt_y) / 3 + 4 - y][(P.x - wt_x) / 6 + 2 - x];
				else if (X.pos == 4 && (P.y - wt_y) / 3 + x >= 0 && (P.x - wt_x) / 6 + 4 - y >= 0)
					rt = rt && !mp[(P.y - wt_y) / 3 + x][(P.x - wt_x) / 6 + 4 - y];
			}
	return rt;
}

bool check_rotate(const NUM X, POS P, const POS PANEL, const bool (*mp)[Maxm])
{
	int tg = X.pos + 1 > 4 ? 1 : X.pos + 1;
	bool rt = 1;
	if (X.pos & 1)
		P.y += 3, P.x -= 6;
	else
		P.y -= 3, P.x += 6;
	if (P.y - wt_y < 0 || P.x - wt_x < 0)
		return 0;
	return check_mp(NUM(X.number, tg), P, mp);
}

bool check_place(const NUM X, const POS P, const POS PANEL, const bool (*mp)[Maxm])
{
	if ((P.y - wt_y) / 3 + num_col * ((X.pos & 1) == 0) + num_row * (X.pos & 1) > PANEL.y)
		return 0;
	if (P.x <= 1 || P.x + 17 > PANEL.x * 6 + 2)
		return 0;
	return check_mp(X, P, mp);
}

bool check_end(const POS PANEL, const bool (*mp)[Maxm])
{
	for (int i = 0; i < PANEL.x; ++i)
		if (mp[0][i])
			return 1;
	return 0;
}

void fill_mp(const NUM X, const POS P, bool (*mp)[Maxm])
{
	for(int y = 0; y < num_row; ++ y)
		for (int x = 0; x < num_col; ++x) {
			if (X.pos == 1)
				mp[(P.y - wt_y) / 3 + y][(P.x - wt_x) / 6 + x] = num[X.number][y][x];
			else if (X.pos == 2)
				mp[(P.y - wt_y) / 3 + 2 - x][(P.x - wt_x) / 6 + y] = num[X.number][y][x];
			else if (X.pos == 3)
				mp[(P.y - wt_y) / 3 + 4 - y][(P.x - wt_x) / 6 + 2 - x] = num[X.number][y][x];
			else
				mp[(P.y - wt_y) / 3 + x][(P.x - wt_x) / 6 + 4 - y] = num[X.number][y][x];
		}
}

int count_score(const POS PANEL, bool (*mp)[Maxm])
{
	int rt = 0;
	for (int y = 0; y < PANEL.y; ++y) {
		bool tg = 1;
		for (int x = 0; x < PANEL.x; ++x)
			tg = tg && mp[y][x];
		if (tg) {
			++rt;
			for (int x = 0; x < PANEL.x; ++x) {
				puzzle_print(1, POS(wt_x+6*x, wt_y+3*y), 0);
				mp[y][x] = 0;
				for (int k = y; k; --k) 
					if(mp[k][x] != mp[k-1][x]){
						puzzle_print(1, POS(wt_x+6*x, wt_y+3*k), mp[k-1][x]);
						mp[k][x] = mp[k - 1][x];
					}
				puzzle_print(1, POS(wt_x+6*x, wt_y), 0);
				mp[0][x] = 0;
			}
		}
	}
	return rt;
}

int moving(NUM X, POS P, const POS PANEL, bool (*mp)[Maxm], const int time)
{
	int N = 3 * PANEL.y, M = 3 * PANEL.x;
	char c;
	while (1) {
		if (_kbhit()) {
			c = _getch();
			c = _getch();
			if (c == 75 && check_place(X, POS(P.x-2, P.y), PANEL, mp)) {//left
				number_print(X, P, 0);
				P.x -= 2;
				number_print(X, P);
			}
			else if (c == 77 && check_place(X, POS(P.x+2, P.y), PANEL, mp)) {//right
				number_print(X, P, 0);
				P.x += 2;
				number_print(X, P);
			}
			else if (c == 72) {//up->change
				if (!check_rotate(X, P, PANEL, mp))
					continue;
				number_print(X, P, 0);
				if (X.pos & 1)
					P.y += 3, P.x -= 6;
				else
					P.y -= 3, P.x += 6;
				++X.pos;
				if (X.pos > 4)
					X.pos = 1;
				number_print(X, P);
			}
			else if (c == 80) {//down->drop
				while (check_place(X, POS(P.x, P.y+3), PANEL, mp)) {
					number_print(X, P, 0);
					P.y += 3;
					number_print(X, P);
				}
				fill_mp(X, P, mp);
				return count_score(PANEL, mp);
			}
		}
		else if (!check_place(X, POS(P.x, P.y + 3), PANEL, mp)) {
			fill_mp(X, P, mp);
			return count_score(PANEL, mp);
		}
		else {
			//Sleep(1000);
			number_print(X, P, 0);
			P.y += 3;
			number_print(X, P);
		}
		Sleep(time);
	}
}