/*1952339 ��08 ��ܰ��*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<conio.h>
#include<ctime>
using namespace std;

#include "./90-01-b2-mto10.h"
#include "../include/common_mybase_tool.h"

const int number[7][20] = { {}, {}, {}, {1, 2, 3}, {1, 1, 1, 2, 2, 2, 3, 3, 3, 4}, {1, 1, 1, 1, 1, 2, 2, 2 ,2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5, 5}, {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6}};

/*����һ����������ĸ������5-8��*/
void read_num(int inv, int *num, int row = Maxn, int column = Maxn, int *pos = 0)
{
	int x, y;
	cct_getxy(x, y);
	int n;
	char c;
	if(pos)
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
		if(!pos && *num >= data_interval[inv][0] && *num <= data_interval[inv][1])
			break;
		if (pos && (*pos != -1 && *pos < row && *num < column))
			break;
		while (c != '\n' && (c = getchar()))
			++n;
		while (n >= 0)
			cct_showch(x + n, y, ' ', COLOR_BLACK, COLOR_BLACK), --n;
		cct_gotoxy(0, y + 1);
		cct_setcolor();
		cout << "���벻�Ϸ�������������";
		cct_gotoxy(x, y);
	}
	cct_showstr(0, y+1,"                              ");
	cct_gotoxy(0, y+1);
}

/*��ʼ��ֵ*/
void initialize(int (*table)[Maxn], int (*fnd)[Maxn])
{
	memst(table);
	memst(fnd);
}

/*�����Ϸ����*/
bool check_end(int row, int column, const int table[Maxn][Maxn])
{
	for(int i = 1; i <= row; ++ i)
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
void game_end()
{
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cout << "\n��С�������������End����...";
	char ts[5] = { 0 };
	int x, y;
	cct_getxy(x, y);
	while (1) {
		cct_gotoxy(x, y);
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
		cct_showstr(x, y, "                                      ", COLOR_BLACK, COLOR_BLACK);
		cct_setcolor();
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
void table_fillin(int id, int row, int column, int maxv, int (*table)[Maxn])
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
		int all = segmt * (maxv-3) + 4;
		for (int i = 1; i <= row; ++i)
			for (int j = 1; j <= column; ++j)
				if (!table[i][j]) {
					table[i][j] = num[rand() % all];
					if (id) {
						cout_puzzle(2 + 8 * (j - 1), 2 + 4 * (i - 1), table[i][j], table[i][j]);
						Sleep(slp);
					}
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
				table[i][j] = number[maxv][rand()%mod];
				if (id) {
					cout_puzzle(2 + 8 * (j - 1), 2 + 4 * (i - 1), table[i][j], table[i][j]);
					Sleep(slp);
				}
			}
}

/*ˢ����Ļ���˵�*/
void screen_setup()
{
	cct_setconsoleborder(cols, rows, cols, rows*10);
	cct_setcolor();
	cct_cls();
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
	cout << "A.αͼ�ν��������Զ����\n";
	cout << "B.αͼ�ν��������Զ��⾺����\n";
	cout << "-----------------------------------\n";
	cout << "[��ѡ��0-9] ";
}

/*�������ͼ�ͻ����*/
void game_setup_symple_frame(int x, int y, int row, int column)
{
	cct_gotoxy(x, y);
	cout << "  |";
	for (int i = 0; i < column; ++i)
		cout << "  " << i;
	cout << "\n--+";
	for (int i = 0; i < column; ++i)
		cout << "---";
	putchar(10);
	for (int i = 0; i < row; ++i)
		cout << char('A'+i) << " |\n";
}

/*������ұ�����飬�������������·�*/
void cout_fnd(int x, int y, int row, int column, const int fnd[Maxn][Maxn])
{
	cct_gotoxy(x, y);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= column; ++j) {
			cct_gotoxy(x+3*j, y+i);
			if (fnd[i][j])
				putchar('*');
			else
				putchar('0');
		}
	cct_gotoxy(0, y+row+1);
}

/*�����ɫ������飬�������������·�*/
void cout_table_color(int x, int y, int row, int column, const int table[Maxn][Maxn], const int fnd[Maxn][Maxn])
{
	cct_gotoxy(x, y);
	for (int i = 1; i <= row; ++i) 
		for (int j = 1; j <= column; ++j) {
			cct_gotoxy(x+3*j, y+i);
			if (fnd[i][j])
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
			cout << table[i][j];
			cct_setcolor();
		}
	cct_gotoxy(0, y+row+1);
}

/*��������ְ���*/
void cout_board(bool id, int x, int y, int row, int column, const int(*table)[Maxn], const int fnd[Maxn][Maxn])
{
	cct_gotoxy(x, y);
	game_setup_symple_frame(x, y, row, column);
	if(id == 0)
		cout_fnd(x + 2, y + 1, row, column, fnd);
	else 
		cout_table_color(x + 2, y + 1, row, column, table, fnd);
}

/*��ʼ����row,column*/
void read_initial(int *row, int *column)
{
	cout << "����������(5-8)�� ";
	read_num(0, row);
	cout << "����������(5-8)�� ";
	read_num(1, column);
}

/*Dfs������Χ��ͬ����*/
void game_find_same_DFS(int posr, int posc, int row, int column, const int table[Maxn][Maxn], int (*fnd)[Maxn])
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
int table_change(int posr, int posc, int row, int column, int (*table)[Maxn], int (*fnd)[Maxn])
{
	int sco = table[posr][posc], tot = 1;
	++table[posr][posc];
	fnd[0][1] = fnd[0][1] > table[posr][posc] ? fnd[0][1] : table[posr][posc];
	for(int i = 1; i <= row; ++ i)
		for (int j = 1; j <= column; ++j)
			if (fnd[i][j] && (i != posr || j != posc)) 
				table[i][j] = 0, ++tot;
	sco *= tot * 3;
	return sco;
}

/*����1��2��3��4*/
void order_1_2_3_4(int id, int x, int y, int row, int column, int aim, int(*table)[Maxn], int (*fnd)[Maxn])
{
	int posr, posc;
	while(1){
		cct_gotoxy(x, y);
		while (1) {
			cout << "������ĸ+������ʽ[����c2]����������꣺";
			read_num(2, &posc, row, column, &posr);
			cct_getxy(x, y);
			cct_showstr(0, y, "                              ");
			cct_gotoxy(0, y);
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
		cct_getxy(x, y);
		cout_board(0, x, y, row, column, table, fnd);
		cct_getxy(x, y);
		cout << "\n��ǰ����(��ͬɫ��ʶ)��\n";
		cct_getxy(x, y);
		cout_board(1, x, y, row, column, table, fnd);
		if (id == 1 || id == 2)
			break;
		cout << "\n��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���" << char(posr+'A'-1) << posc-1 << "��(Y/N/Q)��";
		cct_getxy(x, y);
		char c;
		while ((c = _getch()) != 'Y' && c != 'y' && c != 'N' && c != 'n' && c != 'q' && c != 'Q')
			cct_gotoxy(x, y);
		cout << c;
		putchar(10);
		if (c == 'Q' || c == 'q' || c == 'N' || c == 'n')
			break;
		int score = 0;
		score = table_change(posr, posc, row, column, table, fnd);
		cout << "\n��ֵͬ�鲢�������(��ͬɫ��ʶ)��\n";
		cct_getxy(x, y);
		cout_board(1, x, y, row, column, table, fnd);
		cout << "\n���ε÷֣�" << score << " �ܵ÷֣�" << score << " �ϳ�Ŀ�꣺" << aim <<'\n';
		cout << "\n���س����������������0����...";
		cct_getxy(x, y);
		while ((c = getchar()) != '\n')
			cct_gotoxy(x, y);
		table_move(0, row, column, table, fnd);
		cout << "��0�������(��ͬɫ��ʶ)��\n";
		cct_getxy(x, y);
		cout_board(1, x, y, row, column, table, fnd);
		cout << "\n���س���������ֵ���...";
		cct_getxy(x, y);
		while ((c = getchar()) != '\n')
			cct_gotoxy(x, y);
		cout << "��ֵ���������(��ͬɫ��ʶ)��\n";
		table_fillin(0, row, column, fnd[0][1], table);
		cct_getxy(x, y);
		cout_board(1, x, y, row, column, table, fnd);
		if(id == 3)
			break;
		if (id == 4) {
			cout << "���κϳɽ��������س���������һ�εĺϳ�...\n";
			cct_getxy(x, y);
			if (fnd[0][1] >= aim) {
				cct_setcolor(COLOR_YELLOW, COLOR_RED);
				cout << "�Ѿ��ϳɵ�" << fnd[0][1];
				cct_setcolor();
			}
			cout << "\n���س������������Ŀ�����...\n\n";
			cct_getxy(x, y);
		}
	}
	game_end();
}

/*�˵���1��2*/
void menu_1_2(int id, int *row, int *column, int (*table)[Maxn], int (*fnd)[Maxn])
{
	read_initial(row, column);
	cout << "\n��ǰ���飺\n";
	game_setup_symple_frame(0, 4, *row, *column);
	build_data(*row, *column, table);
	cout_table_color(2, 5, *row, *column, table, fnd);
	order_1_2_3_4(id, 0, 12, *row, *column, 0, table, fnd);
}

/*�˵���3��4*/
void menu_3_4(int id, int *row, int *aim, int *column, int(*table)[Maxn], int(*fnd)[Maxn])
{
	read_initial(row, column);
	cout << "������ϳ�Ŀ��(5-20)��";
	read_num(2, aim);
	cout << "\n��ǰ���飺\n";
	game_setup_symple_frame(0, 5, *row, *column);
	build_data(*row, *column, table);
	cout_table_color(2, 6, *row, *column, table, fnd);
	order_1_2_3_4(id, 0, 13, *row, *column, *aim, table, fnd);
}

/*���αͼ�λ�����*/
void puzzle_screen(int id, int row, int column, int(*table)[Maxn])
{
	int width = (id == 5 ? 3 : 4);
	int ww = 2 * width * column + 5, hh = 4 + 3 * row + (id != 5) * (row - 1);
	cct_setconsoleborder(ww, hh+3, ww, (hh+3)*10);
	cct_cls();
	build_data(row, column, table);
	cout_table_puzzle(id, 0, 1, row, column, table);
	int x, y;
	cct_getxy(x, y);
	cct_gotoxy(0, 0);
	cct_setcolor();
	cout << "��Ļ��ǰ����Ϊ��" << hh+3 << "��" << ww << "��";
	cct_gotoxy(0, y);
}

/*����ɫ��*/
void choose_move(int x, int y, int px, int py, const int table[Maxn][Maxn])
{
	cout_puzzle(2+8*(x-1), 2+4*(y-1), table[y][x], table[y][x], COLOR_BLACK);
	cout_puzzle(2+8*(px-1), 2+4*(py-1), table[py][px], 14, COLOR_HBLUE);
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
bool puzzle_choose(int *pointx, int *pointy, int *row, int *column, const int table[Maxn][Maxn])
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
	choose_move(x, y, *pointx, *pointy, table);
	return 1;
}

/*�˵���7��8��9*/
void menu_7_8_9(int id, int *row, int *column, int(*table)[Maxn], int(*fnd)[Maxn])
{
	int x, y, aim, score = 0, up;
	read_initial(row, column);
	if (id != 7) {
		cout << "������ϳ�Ŀ��(5-20)��";
		read_num(2, &aim);
		up = aim;
	}
	puzzle_screen(7, *row, *column, table);
	cct_getxy(x, y);
	++y;
	line_clr(x, y);
	cout << "��ͷ���ƶ����س���ѡ��";
	if (id == 7)
		cout << "������";
	cct_setcursor(CURSOR_INVISIBLE);
	int pointx, pointy;
	pointx = 1, pointy = 1;
	cout_puzzle(2 + 8 * (pointx - 1), 2 + 4 * (pointy - 1), table[pointy][pointx], 14, COLOR_HBLUE);
	char c;
	while (1) {
		bool rt = 1;
		while (rt)
			rt = puzzle_choose(&pointx, &pointy, row, column, table);
		line_clr(x, y);
		if (id == 7)
			break;
		game_find_same_BFS(pointy, pointx, *row, *column, table, fnd);
		if (fnd[0][0] == 1) {
			line_clr(x, y);
			cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
			cout << "��Χ����ֵͬ";
			cct_setcolor();
			cout << "����ͷ���ƶ����س���ѡ��";
			continue;
		}
		change_neighbor(0, *row, *column, table, fnd);
		cout_puzzle(2 + 8 * (pointx - 1), 2 + 4 * (pointy - 1), table[pointy][pointx], 14, COLOR_HRED);
		line_clr(x, y);
		cout << "��ͷ���ƶ���ȡ����ǰѡ�񣬻س����ϳ�";
		while ((c = _getch()) != '\r' && c != -32)
			;
		if (c == '\r') {
			puzzle_clr(pointy, pointx, *row, *column, table, fnd);
			score += fnd[0][0] * (table[pointy][pointx] - 1) * 3;
			line_clr(0, 0);
			cout << "���ε÷�:" << fnd[0][0]*(table[pointy][pointx]-1)*3 << " �ܷ�:" << score << " �ϳ�Ŀ��:" << aim;
			for (int k = 0; k < 2; ++k) {
				cout_puzzle(2 + 8 * (pointx - 1), 2 + 4 * (pointy - 1), table[pointy][pointx], 14, COLOR_HBLUE);
				Sleep(slp * 10);
				cout_puzzle(2 + 8 * (pointx - 1), 2 + 4 * (pointy - 1), table[pointy][pointx], table[pointy][pointx]);
				Sleep(slp * 10);
			}
			if (id == 8) {
				line_clr(x, y);
				cout << "�ϳ���ɣ��س�������0";
				while ((c = _getch()) != '\r')
					;
			}
			table_move(1, *row, *column, table, fnd);
			if (id == 8) {
				line_clr(x, y);
				cout << "����0��ɣ��س��������ֵ";
				while ((c = _getch()) != '\r')
					;
			}
			table_fillin(1, *row, *column, fnd[0][1], table);
			if (id == 8) {
				line_clr(x, y);
				cout << "���κϳɽ�������C������һ�εĺϳ�";
				while ((c = _getch()) != 'c' && c != 'C')
					;
				break;
			}
			if (fnd[0][1] > up) {
				up = fnd[0][1];
				line_clr(x, y);
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cout << "�Ѿ��ϳɵ�" << fnd[0][1];
				cct_setcolor();
				cout << "�����س������������Ŀ�����";
				while ((c = _getch()) != '\r')
					;
			}
			if(check_end(*row, *column, table))
				break;
			pointx = pointy = 1;
			cout_puzzle(2 + 8 * (pointx - 1), 2 + 4 * (pointy - 1), table[pointy][pointx], 14, COLOR_HBLUE);
		}
		else {
			change_neighbor(1, *row, *column, table, fnd);
			c = _getch();
			change_pos(c, &pointx, &pointy, *row, *column);
			cout_puzzle(2 + 8 * (pointx - 1), 2 + 4 * (pointy - 1), table[pointy][pointx], 14, COLOR_HBLUE);
		}
	}
	line_clr(x, y);
	cct_gotoxy(x, y-1);
	game_end();
}

int main()
{
	int table[Maxn][Maxn], fnd[Maxn][Maxn];
	while (1) {
		initialize(table, fnd);
		screen_setup();
		char ord;
		int row, column, aim;
		ord  = _getch();
		cout << ord;
		Sleep(500);
		cct_cls();
		if (ord == '0')
			return 0;
		if (ord == '1') 
			menu_1_2(1, &row, &column, table, fnd);
		if (ord == '2') 
			menu_1_2(2, &row, &column, table, fnd);
		if (ord == '3')
			menu_3_4(3, &row, &column, &aim, table, fnd);
		if (ord == '4') 
			menu_3_4(4, &row, &column, &aim, table, fnd);
		if (ord == '5') {
			read_initial(&row, &column);
			puzzle_screen(5, row, column, table);
			game_end();
		}
		if (ord == '6') {
			read_initial(&row, &column);
			puzzle_screen(6, row, column, table);
			game_end();
		}
		if (ord == '7') 
			menu_7_8_9(7, &row, &column, table, fnd);
		if (ord == '8') 
			menu_7_8_9(8, &row, &column, table, fnd);
		if (ord == '9')
			menu_7_8_9(9, &row, &column, table, fnd);
		if (ord == 'A') {
			mto10_main(1);
			game_end();
		}
		if (ord == 'B') {
			for (int i = 0; i < 64; ++i) {
				initialize(table, fnd);
				cct_cls();
				mto10_main(0);
			}
			game_end();
		}
	}
	return 0;
}