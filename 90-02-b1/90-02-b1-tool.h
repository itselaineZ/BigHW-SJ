/*1952339 信08 张馨月*/
#pragma once

struct NUM {
	int number;
	int pos;//旋转姿态1 2 3 4
	NUM() { number = pos = 0; }
	NUM(int a, int b) { number = a, pos = b; }
};

struct POS {
	int x, y;
	POS() { x = y = 0; }
	POS(int a, int b) { x = a, y = b; }
};

const int wt_x = 2;
const int wt_y = 1;
const int Maxn = 30;
const int Maxm = 30;
const int num_col = 3;
const int num_row = 5;
const int wt_time = 100;
const int tip_width = 10;
const int pnl_bg_clr = 7;
const int pnl_fg_clr = 0;
const int pzl_bg_clr = 1;
const int pzl_fg_clr = 7;
const int fen[6] = {0, 1, 3, 6, 10, 15};
const int num[10][5][3] = { {{1,1,1},{1,0,1},{1,0,1},{1,0,1},{1,1,1}}, {{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0}}, {{1,1,1},{0,0,1},{1,1,1},{1,0,0},{1,1,1}}, {{1,1,1},{0,0,1},{1,1,1},{0,0,1},{1,1,1}}, {{1,0,1},{1,0,1},{1,1,1},{0,0,1},{0,0,1}}, {{1,1,1},{1,0,0},{1,1,1},{0,0,1},{1,1,1}}, {{1,1,1},{1,0,0},{1,1,1},{1,0,1},{1,1,1}}, {{1,1,1},{0,0,1},{0,0,1},{0,0,1},{0,0,1}}, {{1,1,1},{1,0,1},{1,1,1},{1,0,1},{1,1,1}}, {{1,1,1},{1,0,1},{1,1,1},{0,0,1},{1,1,1}} };

int get_next_num(const bool new_seed = false, const unsigned int seed = 0);

void panel_print(const POS PANEL);

void puzzle_print(const int key, const POS P, const bool clr = 1);

void number_print(const NUM X, const POS P = POS(2, 1), const bool clr = 1);

bool check_rotate(const NUM X, POS P, const POS PANEL, const bool(*mp)[Maxm]);

bool check_place(const NUM X, const POS P, const POS PANEL, const bool(*mp)[Maxm]);

bool check_end(const POS PANEL, const bool(*mp)[Maxm]);

void fill_mp(const NUM X, const POS P, bool(*mp)[Maxm]);

int moving(NUM X, POS P, const POS PANEL, bool(*mp)[Maxm], const int time);