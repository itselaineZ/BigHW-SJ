/*1952339 ��08 ��ܰ��*/
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

/* ---------------------------------------------------------------------------------------
	 �Ǳ�Ŀ¼�µ�ͷ�ļ�����˵������cmd_console_tools.hΪ������
	 1�����cpp��Ҫ������h��ͬһĿ¼�£�ֱ��#include "cmd_console_tools.h"����
	 2�������У�cpp�Ͳ���ͬһĿ¼�£�����Ҫ�����·����ʽ������
		Ŀ¼�ṹ���£�
		  BigHW
			|---90-01-b1
			|       90-01-b1-main.cpp
			|---include
			|       cmd_console_tools.h
		˵����
		  a) 90-01-b1��include���ֵܹ�ϵ����Ŀ¼����BigHW
		  b) �ڲ���ϵͳ�У�
			 ".."��ʾ��Ŀ¼�����磺"../include"��ʾ��Ŀ¼�µ�include��Ŀ¼
			 "." ��ʾ�Լ���  ���磺"./90-01-b1-main.cpp"��"90-01-b1-main.cpp"�ȼۣ�����ʾ��ǰĿ¼�µ�90-01-b1-main.cpp�ļ�
		  c) 90-01-b1�е�cpp�����include�е�h�������90-01-b1��˵��h��90-01-b1�ĸ���BigHW��include��Ŀ¼
			 ��ˣ��ڱ�cpp�У�h�����·��Ӧ���� "../include/cmd_console_tools.h"
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

/*��εĳ�ʼ��*/
void Initialize()
{
	p[0] = p[1] = p[2] = 0;
	stp = 0;
	cct_setcolor();
}

/*��ʼ��������*/
void Screen_setup()
{
	cct_cls();
	cout << "---------------------------------\n";
	cout << "1.������\n";
	cout << "2.������(������¼)\n";
	cout << "3.�ڲ�������ʾ(����)\n";
	cout << "4.�ڲ�������ʾ(���� + ����)\n";
	cout << "5.ͼ�ν� - Ԥ�� - ������Բ��\n";
	cout << "6.ͼ�ν� - Ԥ�� - ����ʼ���ϻ�n������\n";
	cout << "7.ͼ�ν� - Ԥ�� - ��һ���ƶ�\n";
	cout << "8.ͼ�ν� - �Զ��ƶ��汾\n";
	cout << "9.ͼ�ν� - ��Ϸ��\n";
	cout << "0.�˳�\n";
	cout << "---------------------------------\n";
	cout << "[��ѡ��:] ";
}

/*��ʼ���ݶ���*/
void Read(int* N, char* bgn, char* ed)
{
	cout << "�����뺺ŵ���Ĳ���(1-10)��\n";
	cin >> *N;
	cin.ignore(INF, '\n');
	while (cin.fail() || *N < 1 || *N > 10) {
		cin.clear();
		cin.ignore(INF, '\n');
		cout << "�����뺺ŵ���Ĳ���(1-10)��\n";
		cin >> *N;
	}
	cout << "��������ʼ��(A-C)��\n";
	cin >> *bgn;
	cin.ignore(INF, '\n');
	while (cin.fail() || !((*bgn >= 'a' && *bgn <= 'c') || (*bgn >= 'A' && *bgn <= 'C'))) {
		cin.clear();
		cin.ignore(INF, '\n');
		cout << "��������ʼ��(A-C)��\n";
		cin >> *bgn;
	}
	cout << "������Ŀ����(A-C)��\n";
	cin >> *ed;
	cin.ignore(INF, '\n');
	while (cin.fail() || !((*ed >= 'a' && *ed <= 'c') || (*ed >= 'A' && *ed <= 'C')) || *ed == *bgn) {
		cin.clear();
		cin.ignore(INF, '\n');
		cout << "������Ŀ����(A-C)��\n";
		cin >> *ed;
	}
	if (*bgn > 'C')
		*bgn -= 'a' - 'A';
	if (*ed > 'C')
		*ed -= 'a' - 'A';
}

/*��������ʱ��������룬���˸�������ƽ��Ƿ�*/
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

/*�����ٶȣ�ͣ�٣�Ҫ��*/
void Read_slp(char* slp)
{
	cout << "�������ƶ��ٶ�(0-5��0-���س�������ʾ 1-��ʱ� 5-��ʱ���) ";
	while ((*slp = getchar()) < '0' || *slp > '5') {
		cin.ignore(INF, '\n');
		cout << "�������ƶ��ٶ�(0-5��0-���س�������ʾ 1-��ʱ� 5-��ʱ���) ";
	}
}

/*ǿ�ƶ���س�*/
void Read_enter()
{
	char x = _getch();
	while (x != '\r')
		x = _getch();
}

/*����ƶ�����*/
void cout_move(int st_pos, int ed_pos, int stp)
{
	cout << "��" << setw(4) << stp << " ��(" << setw(2) << stk[st_pos][p[st_pos] - 1] << "#: ";
	cout << char(st_pos + 'A') << "-->" << char(ed_pos + 'A') << ")";
}

/*����ƶ�����������ݣ�->�����������*/
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

/*����ƶ�����*/
void cout_case(int st_pos, int deltay)
{
	cct_gotoxy(10, 12 + deltay);
	for (int i = 1; i <= 25; ++i)
		putchar('=');
	cout << "\n           A         B         C\n\n\n\n";
	cout << "��ʼ: ";
	cout_table();
	for (int x = 11 + st_pos * 10, y = 11 + deltay, i = 0; i < p[st_pos]; ++i) {
		cct_gotoxy(x, y - i);
		cout << stk[st_pos][i];
	}
}

/*���Բ����*/
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

/*�����ʼ����λ��*/
void cout_plate_initial()
{
	for (int i = 0; i < 3; ++i)
		if (p[i])
			for (int j = 0; j < p[i]; Sleep(50), ++j)
				cct_showstr(stx + gap_x * i - stk[i][j], sty - j, spc[stk[i][j]], stk[i][j], COLOR_BLACK);
	cct_setcolor();
}

/*ջ���ƶ�*/
void stk_move(int st_pos, int ed_pos)
{
	stk[ed_pos][p[ed_pos]++] = stk[st_pos][--p[st_pos]];
}

/*���ְ��ƶ�����*/
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

/*�������ƶ�����*/
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

/*��ʼ���������ȫ����*/
void Big_picture_Pre(char bgn, char ed, int N, int now_pos)
{
	cct_cls();
	cout << "�� " << bgn << " �ƶ��� " << ed << "���� " << N << " ��\n";
	cout_cylinder();
	cout_plate_initial();
	cct_setcolor();
	cout_case(now_pos, 15);
	cct_setcursor(CURSOR_INVISIBLE);
}

/*��������Ͻ������ӵ��ƶ�����*/
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

/*Hano�ж�2��3����Ĵ���*/
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

/*Hano�ж�4����Ĵ���*/
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

/*Hano�ж�7��8����Ĵ���*/
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

/*��ŵ����Ҫ����*/
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

/*�������ư涯���ƶ�*/
void Hano_move(int N, int aim_pos)
{
	int sx, sy, stp = 0;
	cct_gotoxy(0, 34);
	cout << "�������ƶ�������(������ʽ��AC = A���˵������ƶ���C��Q = �˳�) ��";
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
			cout << "\n��Ϸ��ֹ!!!!";
			return;
		}
		if (tot == 2 && p[ed - 'A'] > 0 && stk[bgn - 'A'][p[bgn - 'A'] - 1] > stk[ed - 'A'][p[ed - 'A'] - 1]) {
			cout << '\n';
			cct_getxy(x, y);
			cct_setcolor();
			cout << "����ѹС�̣��Ƿ��ƶ�!";
			Sleep(1000);
			line_clr(25, y);
		}
		else if (tot == 2) {
			if (p[bgn - 'A'] && bgn != ed) {
				Change_Big_picture(bgn - 'A', ed - 'A', ++stp, 5);
				if (p[aim_pos] == N) {
					cct_gotoxy(0, sy + 1);
					cct_setcolor();
					cout << "��Ϸ����!!!!!";
					return;
				}
			}
			else if (p[bgn - 'A'] == 0 && bgn != ed) {
				cct_setcolor();
				cout << "\nԴ��Ϊ��";
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

/*�����������ݲ˵�����������*/
int main()
{
	/* ����������д�ģ����԰���ɾ�����޸� */
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
			Read(&N, &bgn, &ed);//���õ����뺯��
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
				cout << "�� " << bgn << " �ƶ��� " << ed << "���� 3 �㣬��ʱ����Ϊ " << slp << '\n';
				cout_case(now_pos, 0);
				cct_setcursor(CURSOR_INVISIBLE);
			}
			else if (ord == '6' || ord == '7') {
				slp = '3';
				cct_setconsoleborder(100, 30);
				cct_cls();
				if (ord == '7')
					cout << "�� " << bgn << " �ƶ��� " << ed << "���� 3 �㣬��ʱ����Ϊ " << slp << '\n';
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
		cout << "\n���س�������";
		ord = _getch();
		while (ord != '\r')
			ord = _getch();
	}
	return 0;
}
