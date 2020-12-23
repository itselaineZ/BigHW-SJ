#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "../include/class_aat.h"
#include "../include/class_cft.h"
#include "../include/class_gmw.h"
#include "./90-02-final-mto10.h"

using namespace std;

const int number[7][20] = { {}, {}, {}, {1, 2, 3}, {1, 1, 1, 2, 2, 2, 3, 3, 3, 4}, {1, 1, 1, 1, 1, 2, 2, 2 ,2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5, 5}, {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6} };


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* procname)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " --cfgfile { --linestyle | --separator | --rowno | --rowno }" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--cfgfile        : ָ�������ļ���(��ȱʡ)" << endl;
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--linestyle 1~4  : ָ���߿��ߵ�����" << endl;
	cout << setw(wopt) << ' ' << "--separator      : ָ���Ƿ���Ҫ�ָ���" << endl;
	cout << setw(wopt) << ' ' << "--rowno yes/no   : ָ���Ƿ���Ҫ�к�" << endl;
	cout << setw(wopt) << ' ' << "--colno          : ָ���Ƿ���Ҫ�к�" << endl;
	cout << endl;

	cout << "e.g.  " << procname << " --cfgfile my.cfg               : ָ����my.cfg�ж����ã��ĸ���ѡ���������ļ�Ϊ׼" << endl;
	cout << "      " << procname << " --cfgfile t.conf --linestyle 4 : ָ����t.cfg�ж����ã�������Ϊ�ᵥ��˫�������������ļ�Ϊ׼" << endl;
	cout << "      " << procname << " --cfgfile test.conf --colno    : ָ����test.cfg�ж����ã���ʾ�кţ������������ļ�Ϊ׼" << endl;
	cout << endl;
}

/* enum��˳��Ҫ��args������˳�򱣳�һ�� */
enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_CFGFILE, OPT_ARGS_LINE_STYLE, OPT_ARGS_SEPARATOR, OPT_ARGS_ROWNO, OPT_ARGS_COLNO };

void screen_setup(CCT cct)
{
	cct.cls();
	cct.setcolor();
	cout << "-----------------------------------\n";
	cout << "1.�������ҳ��ɺϳ����ʶ���ǵݹ飩\n";
	cout << "2.�������ҳ��ɺϳ����ʶ���ݹ飩\n";
	cout << "3.���������һ�κϳɣ��ֲ�����ʾ��\n";
	cout << "4.�����������棨�ֲ�����ʾ��\n";
	cout << "5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�\n";
	cout << "6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�\n";
	cout << "7.αͼ�ν������ü�ͷ��ѡ��ǰɫ��\n";
	cout << "8.αͼ�ν������һ�κϳɣ��ֲ��裩\n";
	cout << "9.αͼ�ν���������\n";
	cout << "0.�˳�\n";
	cout << "-----------------------------------\n";
	cout << "[��ѡ��0-9] ";
}

/*����һ����������ĸ������5-8��*/
void read_num(CCT cct, int inv, int* num, int row = Maxn, int column = Maxn, int* pos = 0)
{
	int x, y;
	cct.getxy(x, y);
	int n;
	char c;
	if (pos)
		*pos = -1;
	while (1) {
		*num = 0;
		n = 0;
		c = getchar();
		if (pos) {
			if (c >= 'a' && c < 'a' + row)
				*pos = c - 'a';
			else if (c >= 'A' && c < 'A' + row)
				*pos = c - 'A';
			c = getchar();
			++n;
		}
		while (c >= '0' && c <= '9') {
			(*num) = (*num) * 10 + c - 48;
			c = getchar();
			++n;
		}
		if (!pos && *num >= data_interval[inv][0] && *num <= data_interval[inv][1])
			break;
		if (pos && (*pos != -1 && *pos < row && *num < column))
			break;
		while (c != '\n' && (c = getchar()))
			++n;
		while (n >= 0)
			cct.showch(x + n, y, ' ', CCT_COLOR::black, CCT_COLOR::black), --n;
		cct.gotoxy(0, y + 1);
		cct.setcolor();
		cout << "���벻�Ϸ�������������";
		cct.gotoxy(x, y);
	}
	cct.showstr(0, y + 1, "                              ");
	cct.gotoxy(0, y + 1);
}

/*��ʼ��ֵ*/
void initialize(int(*table)[Maxn], int(*fnd)[Maxn])
{
	memst(table);
	memst(fnd);
}

/*�����Ϸ����*/
bool check_end(int row, int column, const int table[Maxn][Maxn])
{
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j)
			for (int k = 0; k < 4; ++k) {
				int xx = j + dd[k][0];
				int yy = i + dd[k][1];
				if (check_in_mp(xx, yy, row, column) && table[yy][xx] == table[i][j])
					return 0;
			}
	return 1;
}

/*����End��Ϸ����*/
void game_end(CCT cct)
{
	cct.setcolor();
	cct.setcursor(CCT_CURSOR::normal);
	cout << "\n��С�������������End����...";
	char ts[5] = { 0 };
	int x, y;
	cct.getxy(x, y);
	while (1) {
		cct.gotoxy(x, y);
		char* p = ts;
		bool flg = 0;
		while ((*(p++) = getchar()) && p - ts <= 3) {
			if (*(p - 1) == '\n') {
				flg = 1;
				break;
			}
		}
		if (*(p - 1) == '\n')
			flg = 1;
		while (!flg && (*p = getchar()))
			if (*p == '\n')
				flg = 1;
		if (ts[0] == 'E' && ts[1] == 'n' && ts[2] == 'd')
			break;
		cct.showstr(x, y, "                                      ", CCT_COLOR::black, CCT_COLOR::black);
		cct.setcolor();
	}
}

/*�����������*/
void build_data(int r, int c, int(*table)[Maxn])
{
	srand((unsigned)time(0));
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j)
			table[i][j] = rand() % 3 + 1;
}

/*���������*/
void table_fillin(CONSOLE_GRAPHICS_INFO mto, int id, int row, int column, int maxv, int(*table)[Maxn], const BLOCK_DISPLAY_INFO *cb)
{
	if (maxv >= 7) {
		int num[20];
		num[0] = maxv;//7 6 5 5 
		num[1] = maxv - 1;
		num[2] = num[3] = maxv - 2;
		int segmt = 16 / (maxv - 3);
		for (int i = maxv - 3; i; --i)
			for (int j = 0; j < segmt; ++j)
				num[4 + j * segmt + j] = i;
		int all = segmt * (maxv - 3) + 4;
		for (int i = 1; i <= row; ++i)
			for (int j = 1; j <= column; ++j)
				if (!table[i][j]) {
					table[i][j] = num[rand() % all];
					if (id) 
						mto.gmw_draw_block(i-1, j-1, table[i][j], cb);
				}
		return;
	}
	int mod;
	if (maxv <= 3)
		mod = 3;
	else if (maxv == 4)
		mod = 10;
	else
		mod = 20;
	if (maxv <= 3)
		maxv = 3;
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j)
			if (!table[i][j]) {
				table[i][j] = number[maxv][rand() % mod];
				if (id)
					mto.gmw_draw_block(i-1, j-1, table[i][j], cb);
			}
}

/*�������ͼ�ͻ����*/
void game_setup_symple_frame(CCT cct, int x, int y, int row, int column)
{
	cct.gotoxy(x, y);
	cout << "  |";
	for (int i = 0; i < column; ++i)
		cout << "  " << i;
	cout << "\n--+";
	for (int i = 0; i < column; ++i)
		cout << "---";
	putchar(10);
	for (int i = 0; i < row; ++i)
		cout << char('A' + i) << " |\n";
}

/*������ұ�����飬�������������·�*/
void cout_fnd(CCT cct, int x, int y, int row, int column, const int fnd[Maxn][Maxn])
{
	cct.gotoxy(x, y);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j) {
			cct.gotoxy(x + 3 * j, y + i);
			if (fnd[i][j])
				putchar('*');
			else
				putchar('0');
		}
	cct.gotoxy(0, y + row + 1);
}

/*�����ɫ������飬�������������·�*/
void cout_table_color(CCT cct, int x, int y, int row, int column, const int table[Maxn][Maxn], const int fnd[Maxn][Maxn])
{
	cct.gotoxy(x, y);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j) {
			cct.gotoxy(x + 3 * j, y + i);
			if (fnd[i][j])
				cct.setcolor(CCT_COLOR::black, CCT_COLOR::hyellow);
			cout << table[i][j];
			cct.setcolor();
		}
	cct.gotoxy(0, y + row + 1);
}

/*��������ְ���*/
void cout_board(CCT cct, bool id, int x, int y, int row, int column, const int(*table)[Maxn], const int fnd[Maxn][Maxn])
{
	cct.gotoxy(x, y);
	game_setup_symple_frame(cct, x, y, row, column);
	if (id == 0)
		cout_fnd(cct, x + 2, y + 1, row, column, fnd);
	else
		cout_table_color(cct, x + 2, y + 1, row, column, table, fnd);
}

/*Dfs������Χ��ͬ����*/
void game_find_same_DFS(int posr, int posc, int row, int column, const int table[Maxn][Maxn], int(*fnd)[Maxn])
{
	++fnd[0][0];
	for (int i = 0; i < 4; ++i) {
		int xx = posc + dd[i][0];
		int yy = posr + dd[i][1];
		if (check_in_mp(xx, yy, row, column) && !fnd[yy][xx] && table[yy][xx] == table[posr][posc]) {
			fnd[yy][xx] = 1;
			game_find_same_DFS(yy, xx, row, column, table, fnd);
		}
	}
}

/*���ֺϲ����㣬���װ�*/
int table_change(int posr, int posc, int row, int column, int(*table)[Maxn], int(*fnd)[Maxn])
{
	int sco = table[posr][posc], tot = 1;
	++table[posr][posc];
	fnd[0][1] = fnd[0][1] > table[posr][posc] ? fnd[0][1] : table[posr][posc];
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j)
			if (fnd[i][j] && (i != posr || j != posc))
				table[i][j] = 0, ++tot;
	sco *= tot * 3;
	return sco;
}

/*����1��2��3��4*/
void order_1_2_3_4(CCT cct, CONSOLE_GRAPHICS_INFO mto, int id, int x, int y, int row, int column, int aim, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO *cb)
{
	int posr, posc;
	while (1) {
		cct.gotoxy(x, y);
		while (1) {
			cout << "������ĸ+������ʽ[����c2]����������꣺";
			read_num(cct, 2, &posc, row, column, &posr);
			cct.getxy(x, y);
			cct.showstr(0, y, "                              ");
			cct.gotoxy(0, y);
			cout << "����Ϊ" << char(posr + 'A') << "��" << posc << "��\n";
			++posc, ++posr;
			if (id != 2)
				game_find_same_BFS(posr, posc, row, column, table, fnd);
			else
				game_find_same_DFS(posr, posc, row, column, table, fnd);
			if (fnd[0][0] == 1)
				cout << "����ľ�������λ�ô���������ֵͬ������������\n";
			else
				break;
			memst(fnd);
		}
		cout << "\n���ҽ�����飺\n";
		cct.getxy(x, y);
		cout_board(cct, 0, x, y, row, column, table, fnd);
		cct.getxy(x, y);
		cout << "\n��ǰ����(��ͬɫ��ʶ)��\n";
		cct.getxy(x, y);
		cout_board(cct, 1, x, y, row, column, table, fnd);
		if (id == 1 || id == 2)
			break;
		cout << "\n��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���" << char(posr + 'A' - 1) << posc - 1 << "��(Y/N/Q)��";
		cct.getxy(x, y);
		char c;
		while ((c = _getch()) != 'Y' && c != 'y' && c != 'N' && c != 'n' && c != 'q' && c != 'Q')
			cct.gotoxy(x, y);
		cout << c;
		putchar(10);
		if (c == 'Q' || c == 'q' || c == 'N' || c == 'n')
			break;
		int score = 0;
		score = table_change(posr, posc, row, column, table, fnd);
		cout << "\n��ֵͬ�鲢�������(��ͬɫ��ʶ)��\n";
		cct.getxy(x, y);
		cout_board(cct, 1, x, y, row, column, table, fnd);
		cout << "\n���ε÷֣�" << score << " �ܵ÷֣�" << score << " �ϳ�Ŀ�꣺" << aim << '\n';
		cout << "\n���س����������������0����...";
		cct.getxy(x, y);
		while ((c = getchar()) != '\n')
			cct.gotoxy(x, y);
		table_move(mto, 0, row, column, table, fnd, cb);
		cout << "��0�������(��ͬɫ��ʶ)��\n";
		cct.getxy(x, y);
		cout_board(cct, 1, x, y, row, column, table, fnd);
		cout << "\n���س���������ֵ���...";
		cct.getxy(x, y);
		while ((c = getchar()) != '\n')
			cct.gotoxy(x, y);
		cout << "��ֵ���������(��ͬɫ��ʶ)��\n";
		table_fillin(mto, 0, row, column, fnd[0][1], table, cb);
		cct.getxy(x, y);
		cout_board(cct, 1, x, y, row, column, table, fnd);
		if (id == 3)
			break;
		if (id == 4) {
			cout << "���κϳɽ��������س���������һ�εĺϳ�...\n";
			cct.getxy(x, y);
			if (fnd[0][1] >= aim) {
				cct.setcolor(CCT_COLOR::yellow, CCT_COLOR::red);
				cout << "�Ѿ��ϳɵ�" << fnd[0][1];
				cct.setcolor();
			}
			cout << "\n���س������������Ŀ�����...\n\n";
			cct.getxy(x, y);
		}
	}
	game_end(cct);
}

/*�˵���1��2*/
void menu_1_2(CCT cct, CONSOLE_GRAPHICS_INFO mto, int id, int* row, int* column, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO *cb)
{
	cout << "\n��ǰ���飺\n";
	game_setup_symple_frame(cct, 0, 4, *row, *column);
	build_data(*row, *column, table);
	cout_table_color(cct, 2, 5, *row, *column, table, fnd);
	order_1_2_3_4(cct, mto, id, 0, 12, *row, *column, 0, table, fnd, cb);
}

/*�˵���3��4*/
void menu_3_4(CCT cct, CONSOLE_GRAPHICS_INFO mto, int id, int* row, int* aim, int* column, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO* cb)
{
	cout << "\n��ǰ���飺\n";
	game_setup_symple_frame(cct, 0, 5, *row, *column);
	build_data(*row, *column, table);
	cout_table_color(cct, 2, 6, *row, *column, table, fnd);
	order_1_2_3_4(cct, mto, id, 0, 13, *row, *column, *aim, table, fnd, cb);
}

/*����ɫ��*/
void choose_move(CONSOLE_GRAPHICS_INFO mto, int x, int y, int px, int py, const int table[Maxn][Maxn], const BLOCK_DISPLAY_INFO* cb, const BLOCK_DISPLAY_INFO* cb1)
{
	mto.gmw_draw_block(y-1, x-1, table[y][x], cb);
	mto.gmw_draw_block(py-1, px-1, table[py][px], cb1);
}

/*��ָ��c�ı䵱ǰѡ��λ��*/
bool change_pos(char c, int* pointx, int* pointy, const int row, const int column)
{
	if (c == 75) {//left
		--* pointx;
		if (!*pointx)
			*pointx = column;
	}
	else if (c == 77) {//right
		++* pointx;
		if (*pointx > column)
			*pointx = 1;
	}
	else if (c == 72) {//up
		--* pointy;
		if (!*pointy)
			*pointy = row;
	}
	else if (c == 80) {//down
		++* pointy;
		if (*pointy > row)
			*pointy = 1;
	}
	else
		return 0;
	return 1;
}

/*�ƶ�ѡ��*/
bool puzzle_choose(CONSOLE_GRAPHICS_INFO mto, int* pointx, int* pointy, int* row, int* column, const int table[Maxn][Maxn], const BLOCK_DISPLAY_INFO* cb, const BLOCK_DISPLAY_INFO* cb1)
{
	char c;
	int x = *pointx, y = *pointy;
	while (1) {
		while ((c = _getch()) != -32 && c != '\r')
			;
		if (c == '\r')
			return 0;
		c = _getch();
		if (!change_pos(c, pointx, pointy, *row, *column))
			continue;
		break;
	}
	choose_move(mto, x, y, *pointx, *pointy, table, cb, cb1);
	return 1;
}

void menu_7_8_9(CCT cct, CONSOLE_GRAPHICS_INFO mto, int id, int aim, int* row, int* column, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO* cb, const int (*opt)[2])
{
	const BLOCK_DISPLAY_INFO cb1[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL},
		{10, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL},
		{1, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL},
		{2, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL},
		{3, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL},
		{4, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL},
		{5, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL},
		{6, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL},
		{7, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL},
		{8, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL},
		{9, (CCT_COLOR)opt[2][0], (CCT_COLOR)opt[2][1], NULL}
	};
	int x, y, score = 0, up = aim;
	mto.gmw_draw_frame();
	cct.getxy(x, y);
	++y;
	mto.gmw_top_status_line("��ͷ���ƶ����س���ѡ��");
	cct.setcursor(CCT_CURSOR::invisible);
	int pointx, pointy;
	pointx = 1, pointy = 1;
	mto.gmw_draw_block(pointy-1, pointx-1, table[pointy][pointx], cb);
	char c;
	while (1) {
		bool rt = 1;
		while (rt)
			rt = puzzle_choose(mto, &pointx, &pointy, row, column, table, cb, cb1);
		//line_clr(x, y);
		if (id == 7)
			break;
		game_find_same_BFS(pointy, pointx, *row, *column, table, fnd);
		if (fnd[0][0] == 1) {
			//line_clr(x, y);
			mto.gmw_lower_status_line(NULL, "��Χ����ֵͬ");
			cct.setcolor();
			//cout << "����ͷ���ƶ����س���ѡ��";
			continue;
		}
		change_neighbor(mto, 0, *row, *column, table, fnd, cb, opt);
		mto.gmw_draw_block(pointy-1, pointx-1, table[pointy][pointx], cb1);
		//line_clr(x, y);
		mto.gmw_lower_status_line("��ͷ���ƶ���ȡ����ǰѡ�񣬻س����ϳ�");
		while ((c = _getch()) != '\r' && c != -32)
			;
		if (c == '\r') {
			puzzle_clr(mto, pointy, pointx, *row, *column, table, fnd, cb);
			score += fnd[0][0] * (table[pointy][pointx] - 1) * 3;
			//line_clr(0, 0);
			char content[30];
			sprintf(content, "���ε÷�:%d �ܷ�:%d �ϳ�Ŀ��:%d", fnd[0][0] * (table[pointy][pointx] - 1) * 3, score, aim);
			mto.gmw_top_status_line(content);
			for (int k = 0; k < 2; ++k) {
				mto.gmw_draw_block(pointy-1, pointx-1, table[pointy][pointx], cb1);
				mto.gmw_draw_block(pointy-1, pointx-1, table[pointy][pointx], cb);
			}
			if (id == 8) {
				//line_clr(x, y);
				mto.gmw_lower_status_line("�ϳ���ɣ��س�������0");
				while ((c = _getch()) != '\r')
					;
			}
			table_move(mto, 1, *row, *column, table, fnd, cb);
			if (id == 8) {
				//line_clr(x, y);
				mto.gmw_lower_status_line("����0��ɣ��س��������ֵ");
				while ((c = _getch()) != '\r')
					;
			}
			table_fillin(mto, 1, *row, *column, fnd[0][1], table, cb);
			if (id == 8) {
				//line_clr(x, y);
				mto.gmw_lower_status_line("���κϳɽ�������C������һ�εĺϳ�");
				while ((c = _getch()) != 'c' && c != 'C')
					;
				break;
			}
			if (fnd[0][1] > up) {
				up = fnd[0][1];
				//line_clr(x, y);
				cct.setcolor(CCT_COLOR::black, CCT_COLOR::hyellow);
				sprintf(content, "�Ѿ��ϳɵ�%d�����س����������Ŀ�����", fnd[0][1]);
				mto.gmw_lower_status_line(content);
				cct.setcolor();
				while ((c = _getch()) != '\r')
					;
			}
			if (check_end(*row, *column, table))
				break;
			pointx = pointy = 1;
			mto.gmw_draw_block(pointy-1, pointx-1, table[pointy][pointx], cb);
		}
		else {
			change_neighbor(mto, 1, *row, *column, table, fnd, cb, opt);
			c = _getch();
			change_pos(c, &pointx, &pointy, *row, *column);
			mto.gmw_draw_block(pointy-1, pointx-1, table[pointy][pointx], cb1);
		}
	}
	//line_clr(x, y);
	cct.gotoxy(x, y - 1);
	game_end(cct);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char** argv)
{
	string yesno[] = { "yes","no", "" };	//��β������""

	AAT args[] = {
		AAT("--help", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--cfgfile", ST_EXTARGS_TYPE::str, 1, string("")),				//ָ����Ϸ�����ļ���������������������ļ��ж�ȡ
		AAT("--linestyle", ST_EXTARGS_TYPE::int_with_default, 1, 1, 1, 4),	//ָ�����ͣ���ѡ��1-4������� gmw���������������ļ�����Ӧ���������߲�ͬ���Ա���Ϊ׼��
		AAT("--separator", ST_EXTARGS_TYPE::boolean, 0, false),			//������Ƿ���Ҫ�ָ��ߣ��������������ļ�����Ӧ���������߲�ͬ���Ա���Ϊ׼��
		AAT("--rowno", ST_EXTARGS_TYPE::str_with_set_default, 1, 0, yesno),//������Ƿ���Ҫ��ʾ�кţ�ȱʡΪyes���������������ļ�����Ӧ���������߲�ͬ�ұ�����֣��Ա���Ϊ׼��
		AAT("--colno", ST_EXTARGS_TYPE::boolean, 0, false),				//������Ƿ���Ҫ��ʾ�кţ������--rowno��ͬ��ȱʡΪflase������ʾ���������������ļ�����Ӧ���������߲�ͬ�ұ�����֣��Ա���Ϊ׼��
		AAT()  //���һ�������ڽ���
	};

	int cur_argc;

	//���һ������1����ʾ��ѡ������⣬������������
	if ((cur_argc = args_analyse(argc, argv, args, 0)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	args_analyse_print(args);

	/* ��help�����⴦�� */
	if (args[OPT_ARGS_HELP].existed()) {
		//ֻҪ�� --help���������������ԣ���ʾ��������
		usage(argv[0]);
		return -1; //ִ�����ֱ���˳�
	}

	if (!args[OPT_ARGS_CFGFILE].existed()) {
		usage(argv[0]);
		cout << "����ָ��[" << args[OPT_ARGS_CFGFILE].get_name() << "]" << endl;
		return -1;
	}

	/* ������������������������ļ���������Ϸ�Ⱥ������� */

	CONSOLE_GRAPHICS_INFO mto;
	CFT fcfg;

	/*�������ļ�*/
	int row_num = 5, col_num = 5;
	int aim_number = 5;

	int block_color[10][2] = {
		{0, 13}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, 
		{0, 5}, {0, 9}, {0, 10}, {0, 11}, {0, 12}
	};
	int opt[3][2];
	int block_width = 6, block_high = 3;
	 {
		fcfg.open(args[1].get_string().c_str(), OPEN_OPT_RDONLY);
		int start_x = 0, start_y = 0;
		int extern_up_lines = 0, extern_lower_lines = 0, extern_left_cols = 0, extern_right_cols = 0;

		int area_bgcolor = 0, area_fgcolor = 7;
		char fontname[30];
		strcpy_s(fontname, "Terminal");
		int fs = 8;
		int delay_of_draw_frame = 0, delay_of_block_move = 10;

		fcfg.item_get_value("��������", "��ʼ�к�", start_y);
		fcfg.item_get_value("��������", "��ʼ�к�", start_x);

		fcfg.item_get_value("��������", "�Ϸ�����", extern_up_lines);
		fcfg.item_get_value("��������", "�·�����", extern_lower_lines);
		fcfg.item_get_value("��������", "������", extern_left_cols);
		fcfg.item_get_value("��������", "�Ҳ����", extern_right_cols);

		fcfg.item_get_value("��������", "����", row_num);
		fcfg.item_get_value("��������", "����", col_num);

		fcfg.item_get_value("��������", "����ɫ", area_bgcolor);
		fcfg.item_get_value("��������", "ǰ��ɫ", area_fgcolor);

		fcfg.item_get_value("��������", "����", fontname);
		if (strcmp(fontname, "��������") == 0)
			strcpy_s(fontname, "Terminal");
		else if (strcmp(fontname, "������") == 0)
			fs = 12;
		else {
			strcpy_s(fontname, "Terminal");
			fs = 8;
		}
		fcfg.item_get_value("��������", "�ֺ�", fs);

		fcfg.item_get_value("��������", "���߿���ʱ", delay_of_draw_frame);
		fcfg.item_get_value("��������", "ɫ���ƶ���ʱ", delay_of_block_move);

		mto.gmw_set_rowcol(row_num, col_num);
		mto.gmw_set_color((CCT_COLOR)area_bgcolor, (CCT_COLOR)area_fgcolor);
		mto.gmw_set_delay(DELAY_OF_BLOCK_MOVED, delay_of_block_move);
		mto.gmw_set_delay(DELAY_OF_DRAW_FRAME, delay_of_draw_frame);
		mto.gmw_set_font(fontname, fs * 2, fs);
		mto.gmw_set_ext_rowcol(extern_up_lines, extern_lower_lines, extern_left_cols, extern_right_cols);

		char top_left[CFI_LEN];			// "�X"
		char lower_left[CFI_LEN];		// "�^"
		char top_right[CFI_LEN];			// "�["
		char lower_right[CFI_LEN];		// "�a"
		char h_normal[CFI_LEN];			// "�T"	//Horizontal
		char v_normal[CFI_LEN];			// "�U"	//Vertical
		char h_top_separator[CFI_LEN];	// "�h"
		char h_lower_separator[CFI_LEN];	// "�k"
		char v_left_separator[CFI_LEN];	// "�c"
		char v_right_separator[CFI_LEN];	// "�f"
		char mid_separator[CFI_LEN];
		char separator = 'Y', draw_frame_with_no = 'Y';
		int bgcolor = 15, fgcolor = 0;

		fcfg.item_get_value("�߿�����", "�߿���-���Ͻ�", top_left);
		fcfg.item_get_value("�߿�����", "�߿���-���½�", lower_left);
		fcfg.item_get_value("�߿�����", "�߿���-���Ͻ�", top_right);
		fcfg.item_get_value("�߿�����", "�߿���-���½�", lower_right);
		fcfg.item_get_value("�߿�����", "�߿���-����", h_normal);
		fcfg.item_get_value("�߿�����", "�߿���-����", v_normal);
		fcfg.item_get_value("�߿�����", "�߿���-�Ϸָ���", h_top_separator);
		fcfg.item_get_value("�߿�����", "�߿���-�·ָ���", h_lower_separator);
		fcfg.item_get_value("�߿�����", "�߿���-��ָ���", v_left_separator);
		fcfg.item_get_value("�߿�����", "�߿���-�ҷָ���", v_right_separator);
		fcfg.item_get_value("�߿�����", "�߿���-�зָ���", mid_separator);

		fcfg.item_get_value("�߿�����", "��Ҫ�ָ���", separator);
		fcfg.item_get_value("�߿�����", "�к��б���ʾ", draw_frame_with_no);

		fcfg.item_get_value("�߿�����", "����ɫ", bgcolor);
		fcfg.item_get_value("�߿�����", "ǰ��ɫ", fgcolor);

		mto.gmw_set_frame_linetype(top_left, lower_left, top_right, lower_right, h_normal, v_normal,
			h_top_separator, h_lower_separator, v_left_separator, v_right_separator, mid_separator);
		mto.gmw_set_rowno_switch(draw_frame_with_no == 'Y' || draw_frame_with_no == 'y');
		mto.gmw_set_colno_switch(draw_frame_with_no == 'Y' || draw_frame_with_no == 'y');
		mto.gmw_set_frame_color((CCT_COLOR)bgcolor, (CCT_COLOR)fgcolor);

		char b_top_left[CBI_LEN];			// "�X"
		char b_lower_left[CBI_LEN];		// "�^"
		char b_top_right[CBI_LEN];			// "�["
		char b_lower_right[CBI_LEN];		// "�a"
		char b_h_normal[CBI_LEN];			// "�T"	//Horizontal
		char b_v_normal[CBI_LEN];			// "�U"	//Vertical

		fcfg.item_get_value("ɫ������", "���", block_width);
		fcfg.item_get_value("ɫ������", "�߶�", block_high);

		fcfg.item_get_value("ɫ������", "ɫ��1-ǰ��ɫ", block_color[1][0]);
		fcfg.item_get_value("ɫ������", "ɫ��1-����ɫ", block_color[1][1]);
		fcfg.item_get_value("ɫ������", "ɫ��2-ǰ��ɫ", block_color[2][0]);
		fcfg.item_get_value("ɫ������", "ɫ��2-����ɫ", block_color[2][1]);
		fcfg.item_get_value("ɫ������", "ɫ��3-ǰ��ɫ", block_color[3][0]);
		fcfg.item_get_value("ɫ������", "ɫ��3-����ɫ", block_color[3][1]);
		fcfg.item_get_value("ɫ������", "ɫ��4-ǰ��ɫ", block_color[4][0]);
		fcfg.item_get_value("ɫ������", "ɫ��4-����ɫ", block_color[4][1]);
		fcfg.item_get_value("ɫ������", "ɫ��5-ǰ��ɫ", block_color[5][0]);
		fcfg.item_get_value("ɫ������", "ɫ��5-����ɫ", block_color[5][1]);
		fcfg.item_get_value("ɫ������", "ɫ��6-ǰ��ɫ", block_color[6][0]);
		fcfg.item_get_value("ɫ������", "ɫ��6-����ɫ", block_color[6][1]);
		fcfg.item_get_value("ɫ������", "ɫ��7-ǰ��ɫ", block_color[7][0]);
		fcfg.item_get_value("ɫ������", "ɫ��7-����ɫ", block_color[7][1]);
		fcfg.item_get_value("ɫ������", "ɫ��8-ǰ��ɫ", block_color[8][0]);
		fcfg.item_get_value("ɫ������", "ɫ��8-����ɫ", block_color[8][1]);
		fcfg.item_get_value("ɫ������", "ɫ��9-ǰ��ɫ", block_color[9][0]);
		fcfg.item_get_value("ɫ������", "ɫ��9-����ɫ", block_color[9][1]);
		fcfg.item_get_value("ɫ������", "ɫ��10-ǰ��ɫ", block_color[0][0]);
		fcfg.item_get_value("ɫ������", "ɫ��10-����ɫ", block_color[0][1]);

		fcfg.item_get_value("ɫ������", "�߿���-���Ͻ�", b_top_left);
		fcfg.item_get_value("ɫ������", "�߿���-���½�", b_lower_left);
		fcfg.item_get_value("ɫ������", "�߿���-���Ͻ�", b_top_right);
		fcfg.item_get_value("ɫ������", "�߿���-���½�", b_lower_right);
		fcfg.item_get_value("ɫ������", "�߿���-����", b_h_normal);
		fcfg.item_get_value("ɫ������", "�߿���-����", b_v_normal);

		fcfg.item_get_value("ɫ������", "������ɫ��-����ɫ", opt[0][0]);
		fcfg.item_get_value("ɫ������", "������ɫ��-ǰ��ɫ", opt[0][1]);
		fcfg.item_get_value("ɫ������", "ѡ��ɫ�鱳��ɫ", opt[1][0]);
		fcfg.item_get_value("ɫ������", "ѡ��ɫ��ǰ��ɫ", opt[1][1]);
		fcfg.item_get_value("ɫ������", "����ɫ�鱳��ɫ", opt[2][0]);
		fcfg.item_get_value("ɫ������", "����ɫ��ǰ��ɫ", opt[2][1]);

		mto.gmw_set_frame_style(block_width, block_high, separator == 'Y' || separator == 'y');
		mto.gmw_set_block_linetype(b_top_left, b_lower_left, b_top_right, b_lower_right,
			b_h_normal, b_v_normal);

		char top_status = 'Y', lower_status = 'Y';
		int normal_bgcolor = -1, normal_fgcolor = -1, catchy_bgcolor = -1, catchy_fgcolor = 14;

		fcfg.item_get_value("״̬������", "��״̬��", top_status);
		fcfg.item_get_value("״̬������", "��״̬��", lower_status);
		fcfg.item_get_value("״̬������", "�������ֱ���ɫ", normal_bgcolor);
		fcfg.item_get_value("״̬������", "��������ǰ��ɫ", normal_fgcolor);
		fcfg.item_get_value("״̬������", "�������ֱ���ɫ", catchy_bgcolor);
		fcfg.item_get_value("״̬������", "��������ǰ��ɫ", catchy_fgcolor);

		mto.gmw_set_status_line_switch(TOP_STATUS_LINE, top_status == 'Y' || top_status == 'y');
		mto.gmw_set_status_line_switch(LOWER_STATUS_LINE, lower_status == 'Y' || lower_status == 'y');
		mto.gmw_set_status_line_color(TOP_STATUS_LINE, (CCT_COLOR)normal_bgcolor, (CCT_COLOR)normal_fgcolor, (CCT_COLOR)catchy_bgcolor, (CCT_COLOR)catchy_fgcolor);
		mto.gmw_set_status_line_color(LOWER_STATUS_LINE, (CCT_COLOR)normal_bgcolor, (CCT_COLOR)normal_fgcolor, (CCT_COLOR)catchy_bgcolor, (CCT_COLOR)catchy_fgcolor);
	}

	const BLOCK_DISPLAY_INFO cb[] = {
		{BDI_VALUE_BLANK, CCT_COLOR::invalid, CCT_COLOR::invalid, NULL},
		{10, (CCT_COLOR)block_color[0][0], (CCT_COLOR)block_color[0][1], NULL},
		{1, (CCT_COLOR)block_color[1][0], (CCT_COLOR)block_color[1][1], NULL},
		{2, (CCT_COLOR)block_color[2][0], (CCT_COLOR)block_color[2][1], NULL},
		{3, (CCT_COLOR)block_color[3][0], (CCT_COLOR)block_color[3][1], NULL},
		{4, (CCT_COLOR)block_color[4][0], (CCT_COLOR)block_color[4][1], NULL},
		{5, (CCT_COLOR)block_color[5][0], (CCT_COLOR)block_color[5][1], NULL},
		{6, (CCT_COLOR)block_color[6][0], (CCT_COLOR)block_color[6][1], NULL},
		{7, (CCT_COLOR)block_color[7][0], (CCT_COLOR)block_color[7][1], NULL},
		{8, (CCT_COLOR)block_color[8][0], (CCT_COLOR)block_color[8][1], NULL},
		{9, (CCT_COLOR)block_color[9][0], (CCT_COLOR)block_color[9][1], NULL}
	};

	/*��Ϸ*/
	CCT cct;
	int table[Maxn][Maxn], fnd[Maxn][Maxn];
	while (1) {
		initialize(table, fnd);
		screen_setup(cct);
		char ord;
		ord = _getch();
		int row, column, aim;
		row = row_num, column = col_num, aim = aim_number;
		cct.cls();
		if (ord == '0')
			return 0;
		if (ord == '1')
			menu_1_2(cct, mto, 1, &row, &column, table, fnd, cb);
		if (ord == '2')
			menu_1_2(cct, mto, 2, &row, &column, table, fnd, cb);
		if (ord == '3')
			menu_3_4(cct, mto, 3, &row, &column, &aim, table, fnd, cb);
		if (ord == '4')
			menu_3_4(cct, mto, 4, &row, &column, &aim, table, fnd, cb);
		if (ord == '5') {
			mto.gmw_set_frame_style(block_width, block_high, 0);
			mto.gmw_draw_frame();
			game_end(cct);
		}
		if (ord == '6') {
			mto.gmw_set_frame_style(block_width, block_high, 1);
			mto.gmw_draw_frame();
			game_end(cct);
		}
		if (ord == '7')
			menu_7_8_9(cct, mto, 7, aim, &row, &column, table, fnd, cb, opt);
		if (ord == '8')
			menu_7_8_9(cct, mto, 8, aim, &row, &column, table, fnd, cb, opt);
		if (ord == '9')
			menu_7_8_9(cct, mto, 9, aim, &row, &column, table, fnd, cb, opt);

	}
	return 0;
}

