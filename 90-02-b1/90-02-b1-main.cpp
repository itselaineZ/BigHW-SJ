/*1952339 –≈08 ’≈‹∞‘¬*/
#include<iostream>
#include<cstdio>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"../90-02-b1/90-02-b1-tool.h"
using namespace std;

void line_clr(const int x, const int y)
{
	int c, l, cc, ll;
	cct_getconsoleborder(c, l, cc, ll);
	cct_showch(x, y, ' ', 0, 0, c);
	cct_setcolor();
}

void dropping(const NUM X, POS P, const POS PANEL, const bool (*mp)[Maxm])
{
	while (check_place(X, POS(P.x, P.y+3), PANEL, mp) && !_kbhit()) {
		number_print(X, P, 0);
		P.y += 1;
		number_print(X, P);
	}
}

void game(NUM X, const POS PANEL, bool (*mp)[Maxm])
{
	cct_cls();

	panel_print(PANEL);

	int l, t = 1000;
	int Sco = 0, M = PANEL.x * 3, N = PANEL.y * 3, nxt, lines = 0;
	POS P = POS(PANEL.x+12, 1-3*4);
	cct_showstr(2 * M + 7, wt_y + 3, "Score:");
	cct_showstr(2 * M + 7, wt_y + 6, "The");
	cct_showstr(2 * M + 7, wt_y + 7, "Next:");
	cct_showstr(2 * M + 7, wt_y + 10, "All");
	cct_showstr(2 * M + 7, wt_y + 11, "Lines:");

	nxt = get_next_num();
	while (!check_end(PANEL, mp)) {
		X = NUM(nxt, 1);
		number_print(X, P);
		cct_gotoxy(2 * M + 7, wt_y + 4);
		cout << Sco;
		nxt = get_next_num();
		cct_gotoxy(2 * M + 7, wt_y + 8);
		cout << nxt;
		cct_gotoxy(2 * M + 7, wt_y + 12);
		cout << lines;
		l = moving(X, P, PANEL, mp, t);
		lines += l;
		Sco += fen[l < 5 ? l : 5];
		t = 1000 - Sco / 15 * 100 > 300 ? 1000 - Sco / 15 * 100 : 300;
	}
}

int menu() {
	cct_cls();
	cout << "------------------------------------------------------------\n";
	cout << "1.Print a Blank Panel\n";
	cout << "2.Create a Number on the Panel\n";
	cout << "3.Dropping Test\n";
	cout << "4.Movinng Test\n";
	cout << "5.Game Start\n";
	cout << "0.Exit\n";
	cout << "-------------------------------------------------------------\n";
	cout << "Please Enter a number(0~5): ";
	int rt;
	cin >> rt;
	while (cin.fail() || rt < 0 || rt > 6) {
		cin.clear();
		cin.ignore(0x3f3f3f3f, '\n');
		cout << "Please Enter a number(0~5): ";
		cin >> rt;
	}
	return rt;
}

int main() {
	cct_setcolor();
	int N, M;
	cout << "Please Entering Specifications of the Panel\n(Height: 18~26  Width: 12~21 to be divisible by 3):\n";
	cin >> N >> M;
	while (cin.fail() || N < 18 || N > 26 || M < 12 || M > 21) {
		cin.clear();
		cin.ignore(0x3f3f3f3f, '\n');
		cout << "Please Entering Specifications of the Panel\n(Height: 18~26  Width: 12~21 to be divisible by 3):\n";
		cin >> N >> M;
	}

	int x, y;
	unsigned int my_seed = 123456;
	bool mp[Maxn][Maxm] = {0};
	NUM X = NUM(get_next_num(1, my_seed), 1);

	while (1) {

		memset(mp, 0, sizeof mp );

		int ord = menu();

		switch (ord) {
			case 1: {
				panel_print(POS(M, N));
				break;
			}
			case 2: {
				panel_print(POS(M, N));
				number_print(X);
				break;
			}
			case 3: {
				panel_print(POS(M, N));
				number_print(X);
				dropping(X, POS(wt_x, wt_y), POS(M, N), mp);
				break;
			}
			case 4: {
				cct_setcursor(3);
				panel_print(POS(M, N));
				number_print(X);
				moving(X, POS(wt_x, wt_y), POS(M, N), mp, 1000);
				cct_setcursor(2);
				break;
			}
			case 5: {
				cct_setcursor(3);
				game(X, POS(M, N), mp);
				cct_setcursor(2);
				break;
			}
			default:
				return 0;
		}
		cct_gotoxy(0, 3 * N + 2);
		cout << "Enter End to continue\n";
		cct_getxy(x, y);
		char s[10];
		cin >> s;
		while (strcmp(s, "End") != 0) {
			line_clr(x, y);
			cct_gotoxy(x, y);
			cin >> s;
		}
	}
	return 0;
}