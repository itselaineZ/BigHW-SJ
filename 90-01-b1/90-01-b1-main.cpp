/*1952339 信08 张馨月*/
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

/* ---------------------------------------------------------------------------------------
	 非本目录下的头文件包含说明（以cmd_console_tools.h为例）：
	 1、如果cpp和要包含的h在同一目录下，直接#include "cmd_console_tools.h"即可
	 2、本例中，cpp和不在同一目录下，则需要用相对路径方式来包含
		目录结构如下：
		  BigHW
			|---90-01-b1
			|       90-01-b1-main.cpp
			|---include
			|       cmd_console_tools.h
		说明：
		  a) 90-01-b1和include是兄弟关系，父目录都是BigHW
		  b) 在操作系统中，
			 ".."表示父目录，例如："../include"表示父目录下的include子目录
			 "." 表示自己，  例如："./90-01-b1-main.cpp"和"90-01-b1-main.cpp"等价，都表示当前目录下的90-01-b1-main.cpp文件
		  c) 90-01-b1中的cpp想包含include中的h，则相对90-01-b1来说，h在90-01-b1的父亲BigHW的include子目录
			 因此：在本cpp中，h的相对路径应该是 "../include/cmd_console_tools.h"
   --------------------------------------------------------------------------------------- */
#include "../include/cmd_console_tools.h"
#include "../include/common_mybase_tool.h"

const int INF = 0x3f3f3f3f;
const int stx = 12;
const int sty = 14;
const int gap_x = 32;
const int Time[6] = { 50, 200, 100, 50, 20, 0 };
const char spc[11][22] = { "", "   ", "     ", "       ", "         ", "           ", "             ", "               ", "                 ", "                   ", "                     " };

int stp;

int p[3];
int stk[3][10];

/*多次的初始化*/
void Initialize()
{
	p[0] = p[1] = p[2] = 0;
	stp = 0;
	cct_setcolor();
}

/*起始界面设置*/
void Screen_setup()
{
	cct_cls();
	cout << "---------------------------------\n";
	cout << "1.基本解\n";
	cout << "2.基本解(步数记录)\n";
	cout << "3.内部数组显示(横向)\n";
	cout << "4.内部数组显示(纵向 + 横向)\n";
	cout << "5.图形解 - 预备 - 画三个圆柱\n";
	cout << "6.图形解 - 预备 - 在起始柱上画n个盘子\n";
	cout << "7.图形解 - 预备 - 第一次移动\n";
	cout << "8.图形解 - 自动移动版本\n";
	cout << "9.图形解 - 游戏版\n";
	cout << "0.退出\n";
	cout << "---------------------------------\n";
	cout << "[请选择:] ";
}

/*起始数据读入*/
void Read(int* N, char* bgn, char* ed)
{
	cout << "请输入汉诺塔的层数(1-10)：\n";
	cin >> *N;
	cin.ignore(INF, '\n');
	while (cin.fail() || *N < 1 || *N > 10) {
		cin.clear();
		cin.ignore(INF, '\n');
		cout << "请输入汉诺塔的层数(1-10)：\n";
		cin >> *N;
	}
	cout << "请输入起始柱(A-C)：\n";
	cin >> *bgn;
	cin.ignore(INF, '\n');
	while (cin.fail() || !((*bgn >= 'a' && *bgn <= 'c') || (*bgn >= 'A' && *bgn <= 'C'))) {
		cin.clear();
		cin.ignore(INF, '\n');
		cout << "请输入起始柱(A-C)：\n";
		cin >> *bgn;
	}
	cout << "请输入目标柱(A-C)：\n";
	cin >> *ed;
	cin.ignore(INF, '\n');
	while (cin.fail() || !((*ed >= 'a' && *ed <= 'c') || (*ed >= 'A' && *ed <= 'C')) || *ed == *bgn) {
		cin.clear();
		cin.ignore(INF, '\n');
		cout << "请输入目标柱(A-C)：\n";
		cin >> *ed;
	}
	if (*bgn > 'C')
		*bgn -= 'a' - 'A';
	if (*ed > 'C')
		*ed -= 'a' - 'A';
}

/*自主操作时的命令读入，禁退格禁左右移禁非法*/
void Read_move(char* bgn, char* ed, int* tot)
{
	char ts, tt;
	while ((ts = _getch()) && ts != '\r') {
		tt = ts;
		if (tt >= 'a' && tt <= 'z')
			tt = tt + 'A' - 'a';
		if (!(tt >= 'A' && tt <= 'Z')) {
			if (int(tt) == -32)
				tt = _getch();
			continue;
		}
		cout << ts;
		++* tot;
		if (*tot == 1)
			*bgn = tt;
		else if (*tot == 2)
			*ed = tt;
	}
}

/*读入速度（停顿）要求*/
void Read_slp(char* slp)
{
	cout << "请输入移动速度(0-5：0-按回车单步演示 1-延时最长 5-延时最短) ";
	while ((*slp = getchar()) < '0' || *slp > '5') {
		cin.ignore(INF, '\n');
		cout << "请输入移动速度(0-5：0-按回车单步演示 1-延时最长 5-延时最短) ";
	}
}

/*强制读入回车*/
void Read_enter()
{
	char x = _getch();
	while (x != '\r')
		x = _getch();
}

/*输出移动步骤*/
void cout_move(int st_pos, int ed_pos, int stp)
{
	cout << "第" << setw(4) << stp << " 步(" << setw(2) << stk[st_pos][p[st_pos] - 1] << "#: ";
	cout << char(st_pos + 'A') << "-->" << char(ed_pos + 'A') << ")";
}

/*输出移动表格（柱上内容）->横向输出内容*/
void cout_table()
{
	for (int k = 0; k < 3; ++k) {
		if (k == 0)
			cout << " A:";
		else if (k == 1)
			cout << " B:";
		else
			cout << " C:";
		for (int i = 0; i < p[k]; ++i)
			cout << setw(2) << stk[k][i];
		for (int i = 20 - 2 * p[k]; i; --i)
			putchar(32);
	}
	putchar(10);
}

/*输出移动方案*/
void cout_case(int st_pos, int deltay)
{
	cct_gotoxy(10, 12 + deltay);
	for (int i = 1; i <= 25; ++i)
		putchar('=');
	cout << "\n           A         B         C\n\n\n\n";
	cout << "初始: ";
	cout_table();
	for (int x = 11 + st_pos * 10, y = 11 + deltay, i = 0; i < p[st_pos]; ++i) {
		cct_gotoxy(x, y - i);
		cout << stk[st_pos][i];
	}
}

/*输出圆柱体*/
void cout_cylinder()
{
	cct_setcursor(CURSOR_INVISIBLE);
	int length = 23;
	int height = 12;
	int x = 1, y = 15;
	for (int i = 0; i < length; ++i) {
		cct_showch(x + i, y, ' ', COLOR_HYELLOW, COLOR_BLACK);
		cct_showch(x + i + length + 9, y, ' ', COLOR_HYELLOW, COLOR_BLACK);
		cct_showch(x + i + length * 2 + 18, y, ' ', COLOR_HYELLOW, COLOR_BLACK);
	}
	for (int i = 1; i <= height; Sleep(50), ++i) {
		cct_showch(x + 11, y - i, ' ', COLOR_HYELLOW, COLOR_BLACK);
		cct_showch(x + 11 + length + 9, y - i, ' ', COLOR_HYELLOW, COLOR_BLACK);
		cct_showch(x + 11 + length * 2 + 18, y - i, ' ', COLOR_HYELLOW, COLOR_BLACK);
	}
	cct_gotoxy(0, 28);
	cct_setcolor();
}

/*输出起始盘子位置*/
void cout_plate_initial()
{
	for (int i = 0; i < 3; ++i)
		if (p[i])
			for (int j = 0; j < p[i]; Sleep(50), ++j)
				cct_showstr(stx + gap_x * i - stk[i][j], sty - j, spc[stk[i][j]], stk[i][j], COLOR_BLACK);
	cct_setcolor();
}

/*栈内移动*/
void stk_move(int st_pos, int ed_pos)
{
	stk[ed_pos][p[ed_pos]++] = stk[st_pos][--p[st_pos]];
}

/*数字版移动盘子*/
void plate_change_number(int st_pos, int ed_pos, int deltay)
{
	int x = 11 + st_pos * 10;
	int y = 11 - p[st_pos] + 1 + deltay;
	cct_gotoxy(x, y);
	cct_showch(x, y, ' ', COLOR_BLACK, COLOR_BLACK);
	x = 11 + ed_pos * 10;
	y = 11 - p[ed_pos] + deltay;
	cct_gotoxy(x, y);
	cct_showch(x, y, '0' + stk[st_pos][p[st_pos] - 1], COLOR_BLACK, COLOR_WHITE);
}

/*动画版移动盘子*/
void cout_move_plate(int st_pos, int ed_pos, int tim)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int x = stx + gap_x * st_pos;
	int y = sty - (p[st_pos] - 1);
	int len = stk[st_pos][p[st_pos] - 1];
	cct_gotoxy(x, y);
	for (int i = 0; i < y; ++i) {
		cct_showstr(x - len, y - i, spc[len], len);
		Sleep(tim);
		cct_showstr(x - len, y - i, spc[(len + 1) / 2]);
		if (y - i > 2)
			cct_showstr(x, y - i, " ", COLOR_HYELLOW);
		else
			cct_showstr(x, y - i, " ");
		cct_showstr(x + 1, y - i, spc[(len + 1) / 2]);
		Sleep(tim);
	}
	cct_setcursor(CURSOR_INVISIBLE);
	int rgt = gap_x * (ed_pos - st_pos);
	int tg = rgt < 0 ? -1 : 1;
	rgt = rgt < 0 ? -rgt : rgt;
	for (int i = 1; i <= rgt; ++i) {
		cct_showstr(x + i * tg - len, 1, spc[len], len);
		Sleep(tim);
		cct_showstr(x + i * tg - len, 1, spc[len]);
		Sleep(tim);
	}
	cct_setcursor(CURSOR_INVISIBLE);
	x += rgt * tg;
	int dn = sty - p[ed_pos];
	for (int i = 1; i < dn; ++i) {
		cct_showstr(x - len, i, spc[len], len);
		Sleep(tim);
		cct_showstr(x - len, i, spc[(len + 1) / 2]);
		if (i > 2)
			cct_showstr(x, i, " ", COLOR_HYELLOW);
		else
			cct_showstr(x, i, " ");
		cct_showstr(x + 1, i, spc[(len + 1) / 2]);
		Sleep(tim);
	}
	cct_showstr(x - len, dn, spc[len], len);
}

/*起始动画面板完全绘制*/
void Big_picture_Pre(char bgn, char ed, int N, int now_pos)
{
	cct_cls();
	cout << "从 " << bgn << " 移动到 " << ed << "，共 " << N << " 层\n";
	cout_cylinder();
	cout_plate_initial();
	cct_setcolor();
	cout_case(now_pos, 15);
	cct_setcursor(CURSOR_INVISIBLE);
}

/*动画面板上进行盘子的移动操作*/
void Change_Big_picture(int now_pos, int aim_pos, int stp, int slp)
{
	cct_setcolor();
	line_clr(80, 32);
	plate_change_number(now_pos, aim_pos, 15);
	cct_gotoxy(0, 32);
	cout_move(now_pos, aim_pos, stp);
	stk_move(now_pos, aim_pos);
	cout_table();
	stk_move(aim_pos, now_pos);
	cout_move_plate(now_pos, aim_pos, Time[slp]);
	stk_move(now_pos, aim_pos);
}

/*Hano中对2、3命令的处理*/
void order_2_3(int now_pos, int aim_pos, int stp, int ord)
{
	if (ord == 2) {
		cout_move(now_pos, aim_pos, stp);
		putchar(10);
		stk_move(now_pos, aim_pos);
	}
	else {
		cout_move(now_pos, aim_pos, stp);
		stk_move(now_pos, aim_pos);
		cout_table();
	}
}

/*Hano中对4命令的处理*/
void order_4(int now_pos, int aim_pos, int slp)
{
	if (!slp)
		Read_enter();
	else
		Sleep(Time[slp]);
	line_clr(80, 17);
	plate_change_number(now_pos, aim_pos, 0);
	cct_gotoxy(0, 17);
	cout_move(now_pos, aim_pos, stp);
	stk_move(now_pos, aim_pos);
	cout_table();
}

/*Hano中对7、8命令的处理*/
void order_8_7(int now_pos, int aim_pos, int slp, int stp, int ord)
{
	if (ord == 8) {
		if (!slp)
			Read_enter();
		else
			Sleep(Time[slp]);
		Change_Big_picture(now_pos, aim_pos, stp, slp);
	}
	else {
		cout_move_plate(now_pos, aim_pos, Time[slp]);
		stk_move(now_pos, aim_pos);
		cct_setcolor();
	}
}

/*汉诺塔主要函数*/
void Hano(int n, int now_pos, int aim_pos, int ord, int slp)
{
	if (n == 0)
		return;
	Hano(n - 1, now_pos, 3 - now_pos - aim_pos, ord, slp);
	++stp;
	if (ord == 1)
		cout << n << "# " << char(now_pos + 'A') << "---->" << char(aim_pos + 'A') << '\n';
	else if (ord == 2 || ord == 3)
		order_2_3(now_pos, aim_pos, stp, ord);
	else if (ord == 4)
		order_4(now_pos, aim_pos, slp);
	else if (ord == 8 || (ord == 7 && stp == 1))
		order_8_7(now_pos, aim_pos, slp, stp, ord);
	Hano(n - 1, 3 - now_pos - aim_pos, aim_pos, ord, slp);
}

/*自主控制版动画移动*/
void Hano_move(int N, int aim_pos)
{
	int sx, sy, stp = 0;
	cct_gotoxy(0, 34);
	cout << "请输入移动的柱号(命令形式：AC = A顶端的盘子移动到C，Q = 退出) ：";
	cct_getxy(sx, sy);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	char bgn = 0, ed = 0;
	int x, y, tot = 0;
	while (1) {
		bgn = ed = 0;
		tot = 0;
		x = sx, y = sy;
		Read_move(&bgn, &ed, &tot);
		if (tot == 1 && bgn == 'Q') {
			cct_setcolor();
			cout << "\n游戏中止!!!!";
			return;
		}
		if (tot == 2 && p[ed - 'A'] > 0 && stk[bgn - 'A'][p[bgn - 'A'] - 1] > stk[ed - 'A'][p[ed - 'A'] - 1]) {
			cout << '\n';
			cct_getxy(x, y);
			cct_setcolor();
			cout << "大盘压小盘，非法移动!";
			Sleep(1000);
			line_clr(25, y);
		}
		else if (tot == 2) {
			if (p[bgn - 'A'] && bgn != ed) {
				Change_Big_picture(bgn - 'A', ed - 'A', ++stp, 5);
				if (p[aim_pos] == N) {
					cct_gotoxy(0, sy + 1);
					cct_setcolor();
					cout << "游戏结束!!!!!";
					return;
				}
			}
			else if (p[bgn - 'A'] == 0 && bgn != ed) {
				cct_setcolor();
				cout << "\n源柱为空";
				Sleep(1000);
				cct_getxy(x, y);
				line_clr(25, y);
			}
		}
		for (int i = 0; i <= tot; ++i)
			cct_showch(sx + i, sy, ' ');
		cct_setcolor();
		cct_gotoxy(sx, sy);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
}

/*主函数，操纵菜单及函数调用*/
int main()
{
	/* 内容是随意写的，可以按需删除或修改 */
	//cct_cls();
	while (1) {
		Initialize();
		Screen_setup();
		char ord, slp = 0;
		ord = _getch();
		while (ord < '0' || ord > '9')
			ord = _getch();
		cout << ord;
		if (ord == '0')
			return 0;
		if (ord != '5') {
			cout << "\n\n\n";
			int N, tim = 3;
			char bgn, ed;
			Read(&N, &bgn, &ed);//共用的输入函数
			int now_pos = bgn - 'A', aim_pos = ed - 'A';
			for (int i = N; i; --i)
				stk[now_pos][p[now_pos] ++] = i;
			if (ord == '3') {
				cct_setconsoleborder(100, 30);
				cct_cls();
			}
			else if (ord == '4') {
				Read_slp(&slp);
				cct_setconsoleborder(100, 30);
				cct_cls();
				cout << "从 " << bgn << " 移动到 " << ed << "，共 3 层，延时设置为 " << slp << '\n';
				cout_case(now_pos, 0);
				cct_setcursor(CURSOR_INVISIBLE);
			}
			else if (ord == '6' || ord == '7') {
				slp = '3';
				cct_setconsoleborder(100, 30);
				cct_cls();
				if (ord == '7')
					cout << "从 " << bgn << " 移动到 " << ed << "，共 3 层，延时设置为 " << slp << '\n';
				cout_cylinder();
				cout_plate_initial();
				cct_gotoxy(0, 27);
			}
			else if (ord == '8') {
				Read_slp(&slp);
				cct_setconsoleborder(100, 36);
				Big_picture_Pre(bgn, ed, N, now_pos);
			}
			else if (ord == '9') {
				cct_setconsoleborder(100, 38);
				Big_picture_Pre(bgn, ed, N, now_pos);
				Hano_move(N, aim_pos);
			}
			if (ord != '6' && ord != '9')
				Hano(N, now_pos, aim_pos, ord - '0', 1 * (slp - '0'));
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			if (ord == '4')
				cout << "\n\n\n\n\n\n\n\n\n";
		}
		else {
			cct_setconsoleborder(100, 30);
			cct_cls();
			cout_cylinder();
		}
		if (ord == '7')
			cct_gotoxy(0, 27);
		else if (ord == '8')
			cct_gotoxy(0, 33);
		else if (ord == '9')
			cct_gotoxy(0, 36);
		cct_setcolor();
		cout << "\n按回车键继续";
		ord = _getch();
		while (ord != '\r')
			ord = _getch();
	}
	return 0;
}
