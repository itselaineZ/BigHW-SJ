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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* procname)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " --cfgfile { --linestyle | --separator | --rowno | --rowno }" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "必选项：" << endl;
	cout << setw(wopt) << ' ' << "--cfgfile        : 指定配置文件名(无缺省)" << endl;
	cout << setw(wkey) << ' ' << "可选项：" << endl;
	cout << setw(wopt) << ' ' << "--linestyle 1~4  : 指定边框线的线型" << endl;
	cout << setw(wopt) << ' ' << "--separator      : 指定是否需要分隔线" << endl;
	cout << setw(wopt) << ' ' << "--rowno yes/no   : 指定是否需要行号" << endl;
	cout << setw(wopt) << ' ' << "--colno          : 指定是否需要列号" << endl;
	cout << endl;

	cout << "e.g.  " << procname << " --cfgfile my.cfg               : 指定从my.cfg中读配置，四个可选项以配置文件为准" << endl;
	cout << "      " << procname << " --cfgfile t.conf --linestyle 4 : 指定从t.cfg中读配置，且线型为横单竖双，其余以配置文件为准" << endl;
	cout << "      " << procname << " --cfgfile test.conf --colno    : 指定从test.cfg中读配置，显示列号，其余以配置文件为准" << endl;
	cout << endl;
}

/* enum的顺序要和args的排列顺序保持一致 */
enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_CFGFILE, OPT_ARGS_LINE_STYLE, OPT_ARGS_SEPARATOR, OPT_ARGS_ROWNO, OPT_ARGS_COLNO };

void screen_setup(CCT cct)
{
	cct.cls();
	cct.setcolor();
	cout << "-----------------------------------\n";
	cout << "1.命令行找出可合成项并标识（非递归）\n";
	cout << "2.命令行找出可合成项并标识（递归）\n";
	cout << "3.命令行完成一次合成（分步骤显示）\n";
	cout << "4.命令行完整版（分步骤显示）\n";
	cout << "5.伪图形界面显示初始数组（无分隔线）\n";
	cout << "6.伪图形界面显示初始数组（有分隔线）\n";
	cout << "7.伪图形界面下用箭头键选择当前色块\n";
	cout << "8.伪图形界面完成一次合成（分步骤）\n";
	cout << "9.伪图形界面完整版\n";
	cout << "0.退出\n";
	cout << "-----------------------------------\n";
	cout << "[请选择0-9] ";
}

/*读入一个整数、字母加数（5-8）*/
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
		cout << "输入不合法，请重新输入";
		cct.gotoxy(x, y);
	}
	cct.showstr(0, y + 1, "                              ");
	cct.gotoxy(0, y + 1);
}

/*初始化值*/
void initialize(int(*table)[Maxn], int(*fnd)[Maxn])
{
	memst(table);
	memst(fnd);
}

/*检查游戏结束*/
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

/*输入End游戏继续*/
void game_end(CCT cct)
{
	cct.setcolor();
	cct.setcursor(CCT_CURSOR::normal);
	cout << "\n本小题结束，请输入End继续...";
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

/*生成随机数组*/
void build_data(int r, int c, int(*table)[Maxn])
{
	srand((unsigned)time(0));
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j)
			table[i][j] = rand() % 3 + 1;
}

/*补充随机数*/
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

/*输出简单无图型化框架*/
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

/*输出查找标记数组，结束后光标在左下方*/
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

/*输出变色标记数组，结束后光标在左下方*/
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

/*输出简化数字版面*/
void cout_board(CCT cct, bool id, int x, int y, int row, int column, const int(*table)[Maxn], const int fnd[Maxn][Maxn])
{
	cct.gotoxy(x, y);
	game_setup_symple_frame(cct, x, y, row, column);
	if (id == 0)
		cout_fnd(cct, x + 2, y + 1, row, column, fnd);
	else
		cout_table_color(cct, x + 2, y + 1, row, column, table, fnd);
}

/*Dfs查找周围相同数字*/
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

/*数字合并清零，简易版*/
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

/*命令1、2、3、4*/
void order_1_2_3_4(CCT cct, CONSOLE_GRAPHICS_INFO mto, int id, int x, int y, int row, int column, int aim, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO *cb)
{
	int posr, posc;
	while (1) {
		cct.gotoxy(x, y);
		while (1) {
			cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
			read_num(cct, 2, &posc, row, column, &posr);
			cct.getxy(x, y);
			cct.showstr(0, y, "                              ");
			cct.gotoxy(0, y);
			cout << "输入为" << char(posr + 'A') << "行" << posc << "列\n";
			++posc, ++posr;
			if (id != 2)
				game_find_same_BFS(posr, posc, row, column, table, fnd);
			else
				game_find_same_DFS(posr, posc, row, column, table, fnd);
			if (fnd[0][0] == 1)
				cout << "输入的矩阵坐标位置处无连续相同值，请重新输入\n";
			else
				break;
			memst(fnd);
		}
		cout << "\n查找结果数组：\n";
		cct.getxy(x, y);
		cout_board(cct, 0, x, y, row, column, table, fnd);
		cct.getxy(x, y);
		cout << "\n当前数组(不同色标识)：\n";
		cct.getxy(x, y);
		cout_board(cct, 1, x, y, row, column, table, fnd);
		if (id == 1 || id == 2)
			break;
		cout << "\n请确认是否把相邻的相同值合并到" << char(posr + 'A' - 1) << posc - 1 << "中(Y/N/Q)：";
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
		cout << "\n相同值归并后的数组(不同色标识)：\n";
		cct.getxy(x, y);
		cout_board(cct, 1, x, y, row, column, table, fnd);
		cout << "\n本次得分：" << score << " 总得分：" << score << " 合成目标：" << aim << '\n';
		cout << "\n按回车键进行数组下落除0操作...";
		cct.getxy(x, y);
		while ((c = getchar()) != '\n')
			cct.gotoxy(x, y);
		table_move(mto, 0, row, column, table, fnd, cb);
		cout << "除0后的数组(不同色标识)：\n";
		cct.getxy(x, y);
		cout_board(cct, 1, x, y, row, column, table, fnd);
		cout << "\n按回车键进行新值填充...";
		cct.getxy(x, y);
		while ((c = getchar()) != '\n')
			cct.gotoxy(x, y);
		cout << "新值填充后的数组(不同色标识)：\n";
		table_fillin(mto, 0, row, column, fnd[0][1], table, cb);
		cct.getxy(x, y);
		cout_board(cct, 1, x, y, row, column, table, fnd);
		if (id == 3)
			break;
		if (id == 4) {
			cout << "本次合成结束，按回车键继续新一次的合成...\n";
			cct.getxy(x, y);
			if (fnd[0][1] >= aim) {
				cct.setcolor(CCT_COLOR::yellow, CCT_COLOR::red);
				cout << "已经合成到" << fnd[0][1];
				cct.setcolor();
			}
			cout << "\n按回车键继续向更高目标进发...\n\n";
			cct.getxy(x, y);
		}
	}
	game_end(cct);
}

/*菜单项1、2*/
void menu_1_2(CCT cct, CONSOLE_GRAPHICS_INFO mto, int id, int* row, int* column, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO *cb)
{
	cout << "\n当前数组：\n";
	game_setup_symple_frame(cct, 0, 4, *row, *column);
	build_data(*row, *column, table);
	cout_table_color(cct, 2, 5, *row, *column, table, fnd);
	order_1_2_3_4(cct, mto, id, 0, 12, *row, *column, 0, table, fnd, cb);
}

/*菜单项3、4*/
void menu_3_4(CCT cct, CONSOLE_GRAPHICS_INFO mto, int id, int* row, int* aim, int* column, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO* cb)
{
	cout << "\n当前数组：\n";
	game_setup_symple_frame(cct, 0, 5, *row, *column);
	build_data(*row, *column, table);
	cout_table_color(cct, 2, 6, *row, *column, table, fnd);
	order_1_2_3_4(cct, mto, id, 0, 13, *row, *column, *aim, table, fnd, cb);
}

/*更换色块*/
void choose_move(CONSOLE_GRAPHICS_INFO mto, int x, int y, int px, int py, const int table[Maxn][Maxn], const BLOCK_DISPLAY_INFO* cb, const BLOCK_DISPLAY_INFO* cb1)
{
	mto.gmw_draw_block(y-1, x-1, table[y][x], cb);
	mto.gmw_draw_block(py-1, px-1, table[py][px], cb1);
}

/*由指令c改变当前选中位置*/
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

/*移动选择*/
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
	mto.gmw_top_status_line("箭头键移动，回车键选择");
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
			mto.gmw_lower_status_line(NULL, "周围无相同值");
			cct.setcolor();
			//cout << "，箭头键移动，回车键选择";
			continue;
		}
		change_neighbor(mto, 0, *row, *column, table, fnd, cb, opt);
		mto.gmw_draw_block(pointy-1, pointx-1, table[pointy][pointx], cb1);
		//line_clr(x, y);
		mto.gmw_lower_status_line("箭头键移动并取消当前选择，回车键合成");
		while ((c = _getch()) != '\r' && c != -32)
			;
		if (c == '\r') {
			puzzle_clr(mto, pointy, pointx, *row, *column, table, fnd, cb);
			score += fnd[0][0] * (table[pointy][pointx] - 1) * 3;
			//line_clr(0, 0);
			char content[30];
			sprintf(content, "本次得分:%d 总分:%d 合成目标:%d", fnd[0][0] * (table[pointy][pointx] - 1) * 3, score, aim);
			mto.gmw_top_status_line(content);
			for (int k = 0; k < 2; ++k) {
				mto.gmw_draw_block(pointy-1, pointx-1, table[pointy][pointx], cb1);
				mto.gmw_draw_block(pointy-1, pointx-1, table[pointy][pointx], cb);
			}
			if (id == 8) {
				//line_clr(x, y);
				mto.gmw_lower_status_line("合成完成，回车键下落0");
				while ((c = _getch()) != '\r')
					;
			}
			table_move(mto, 1, *row, *column, table, fnd, cb);
			if (id == 8) {
				//line_clr(x, y);
				mto.gmw_lower_status_line("下落0完成，回车键填充新值");
				while ((c = _getch()) != '\r')
					;
			}
			table_fillin(mto, 1, *row, *column, fnd[0][1], table, cb);
			if (id == 8) {
				//line_clr(x, y);
				mto.gmw_lower_status_line("本次合成结束，按C继续新一次的合成");
				while ((c = _getch()) != 'c' && c != 'C')
					;
				break;
			}
			if (fnd[0][1] > up) {
				up = fnd[0][1];
				//line_clr(x, y);
				cct.setcolor(CCT_COLOR::black, CCT_COLOR::hyellow);
				sprintf(content, "已经合成到%d，按回车继续向更高目标进发", fnd[0][1]);
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	string yesno[] = { "yes","no", "" };	//结尾必须是""

	AAT args[] = {
		AAT("--help", ST_EXTARGS_TYPE::boolean, 0, false),
		AAT("--cfgfile", ST_EXTARGS_TYPE::str, 1, string("")),				//指定游戏配置文件，所有设置项均从配置文件中读取
		AAT("--linestyle", ST_EXTARGS_TYPE::int_with_default, 1, 1, 1, 4),	//指定线型，可选项1-4，具体见 gmw（本项优于配置文件名对应项，即如果两者不同，以本项为准）
		AAT("--separator", ST_EXTARGS_TYPE::boolean, 0, false),			//主框架是否需要分隔线（本项优于配置文件名对应项，即如果两者不同，以本项为准）
		AAT("--rowno", ST_EXTARGS_TYPE::str_with_set_default, 1, 0, yesno),//主框架是否需要显示行号（缺省为yes，本项优于配置文件名对应项，即如果两者不同且本项出现，以本项为准）
		AAT("--colno", ST_EXTARGS_TYPE::boolean, 0, false),				//主框架是否需要显示列号（故意和--rowno不同，缺省为flase，不显示，本项优于配置文件名对应项，即如果两者不同且本项出现，以本项为准）
		AAT()  //最后一个，用于结束
	};

	int cur_argc;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		return -1;
	}

	args_analyse_print(args);

	/* 对help做特殊处理 */
	if (args[OPT_ARGS_HELP].existed()) {
		//只要有 --help，其它参数都忽略，显示帮助即可
		usage(argv[0]);
		return -1; //执行完成直接退出
	}

	if (!args[OPT_ARGS_CFGFILE].existed()) {
		usage(argv[0]);
		cout << "必须指定[" << args[OPT_ARGS_CFGFILE].get_name() << "]" << endl;
		return -1;
	}

	/* 进入后续分析参数、读配置文件，进行游戏等后续工作 */

	CONSOLE_GRAPHICS_INFO mto;
	CFT fcfg;

	/*读配置文件*/
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

		fcfg.item_get_value("区域设置", "起始行号", start_y);
		fcfg.item_get_value("区域设置", "起始列号", start_x);

		fcfg.item_get_value("区域设置", "上方空行", extern_up_lines);
		fcfg.item_get_value("区域设置", "下方空行", extern_lower_lines);
		fcfg.item_get_value("区域设置", "左侧空行", extern_left_cols);
		fcfg.item_get_value("区域设置", "右侧空行", extern_right_cols);

		fcfg.item_get_value("区域设置", "行数", row_num);
		fcfg.item_get_value("区域设置", "列数", col_num);

		fcfg.item_get_value("区域设置", "背景色", area_bgcolor);
		fcfg.item_get_value("区域设置", "前景色", area_fgcolor);

		fcfg.item_get_value("区域设置", "字体", fontname);
		if (strcmp(fontname, "点阵字体") == 0)
			strcpy_s(fontname, "Terminal");
		else if (strcmp(fontname, "新宋体") == 0)
			fs = 12;
		else {
			strcpy_s(fontname, "Terminal");
			fs = 8;
		}
		fcfg.item_get_value("区域设置", "字号", fs);

		fcfg.item_get_value("区域设置", "画边框延时", delay_of_draw_frame);
		fcfg.item_get_value("区域设置", "色块移动延时", delay_of_block_move);

		mto.gmw_set_rowcol(row_num, col_num);
		mto.gmw_set_color((CCT_COLOR)area_bgcolor, (CCT_COLOR)area_fgcolor);
		mto.gmw_set_delay(DELAY_OF_BLOCK_MOVED, delay_of_block_move);
		mto.gmw_set_delay(DELAY_OF_DRAW_FRAME, delay_of_draw_frame);
		mto.gmw_set_font(fontname, fs * 2, fs);
		mto.gmw_set_ext_rowcol(extern_up_lines, extern_lower_lines, extern_left_cols, extern_right_cols);

		char top_left[CFI_LEN];			// "╔"
		char lower_left[CFI_LEN];		// "╚"
		char top_right[CFI_LEN];			// "╗"
		char lower_right[CFI_LEN];		// "╝"
		char h_normal[CFI_LEN];			// "═"	//Horizontal
		char v_normal[CFI_LEN];			// "║"	//Vertical
		char h_top_separator[CFI_LEN];	// "╤"
		char h_lower_separator[CFI_LEN];	// "╧"
		char v_left_separator[CFI_LEN];	// "╟"
		char v_right_separator[CFI_LEN];	// "╢"
		char mid_separator[CFI_LEN];
		char separator = 'Y', draw_frame_with_no = 'Y';
		int bgcolor = 15, fgcolor = 0;

		fcfg.item_get_value("边框设置", "边框线-左上角", top_left);
		fcfg.item_get_value("边框设置", "边框线-左下角", lower_left);
		fcfg.item_get_value("边框设置", "边框线-右上角", top_right);
		fcfg.item_get_value("边框设置", "边框线-右下角", lower_right);
		fcfg.item_get_value("边框设置", "边框线-横线", h_normal);
		fcfg.item_get_value("边框设置", "边框线-竖线", v_normal);
		fcfg.item_get_value("边框设置", "边框线-上分隔线", h_top_separator);
		fcfg.item_get_value("边框设置", "边框线-下分隔线", h_lower_separator);
		fcfg.item_get_value("边框设置", "边框线-左分隔线", v_left_separator);
		fcfg.item_get_value("边框设置", "边框线-右分隔线", v_right_separator);
		fcfg.item_get_value("边框设置", "边框线-中分隔线", mid_separator);

		fcfg.item_get_value("边框设置", "需要分隔线", separator);
		fcfg.item_get_value("边框设置", "行号列标显示", draw_frame_with_no);

		fcfg.item_get_value("边框设置", "背景色", bgcolor);
		fcfg.item_get_value("边框设置", "前景色", fgcolor);

		mto.gmw_set_frame_linetype(top_left, lower_left, top_right, lower_right, h_normal, v_normal,
			h_top_separator, h_lower_separator, v_left_separator, v_right_separator, mid_separator);
		mto.gmw_set_rowno_switch(draw_frame_with_no == 'Y' || draw_frame_with_no == 'y');
		mto.gmw_set_colno_switch(draw_frame_with_no == 'Y' || draw_frame_with_no == 'y');
		mto.gmw_set_frame_color((CCT_COLOR)bgcolor, (CCT_COLOR)fgcolor);

		char b_top_left[CBI_LEN];			// "╔"
		char b_lower_left[CBI_LEN];		// "╚"
		char b_top_right[CBI_LEN];			// "╗"
		char b_lower_right[CBI_LEN];		// "╝"
		char b_h_normal[CBI_LEN];			// "═"	//Horizontal
		char b_v_normal[CBI_LEN];			// "║"	//Vertical

		fcfg.item_get_value("色块设置", "宽度", block_width);
		fcfg.item_get_value("色块设置", "高度", block_high);

		fcfg.item_get_value("色块设置", "色块1-前景色", block_color[1][0]);
		fcfg.item_get_value("色块设置", "色块1-背景色", block_color[1][1]);
		fcfg.item_get_value("色块设置", "色块2-前景色", block_color[2][0]);
		fcfg.item_get_value("色块设置", "色块2-背景色", block_color[2][1]);
		fcfg.item_get_value("色块设置", "色块3-前景色", block_color[3][0]);
		fcfg.item_get_value("色块设置", "色块3-背景色", block_color[3][1]);
		fcfg.item_get_value("色块设置", "色块4-前景色", block_color[4][0]);
		fcfg.item_get_value("色块设置", "色块4-背景色", block_color[4][1]);
		fcfg.item_get_value("色块设置", "色块5-前景色", block_color[5][0]);
		fcfg.item_get_value("色块设置", "色块5-背景色", block_color[5][1]);
		fcfg.item_get_value("色块设置", "色块6-前景色", block_color[6][0]);
		fcfg.item_get_value("色块设置", "色块6-背景色", block_color[6][1]);
		fcfg.item_get_value("色块设置", "色块7-前景色", block_color[7][0]);
		fcfg.item_get_value("色块设置", "色块7-背景色", block_color[7][1]);
		fcfg.item_get_value("色块设置", "色块8-前景色", block_color[8][0]);
		fcfg.item_get_value("色块设置", "色块8-背景色", block_color[8][1]);
		fcfg.item_get_value("色块设置", "色块9-前景色", block_color[9][0]);
		fcfg.item_get_value("色块设置", "色块9-背景色", block_color[9][1]);
		fcfg.item_get_value("色块设置", "色块10-前景色", block_color[0][0]);
		fcfg.item_get_value("色块设置", "色块10-背景色", block_color[0][1]);

		fcfg.item_get_value("色块设置", "边框线-左上角", b_top_left);
		fcfg.item_get_value("色块设置", "边框线-左下角", b_lower_left);
		fcfg.item_get_value("色块设置", "边框线-右上角", b_top_right);
		fcfg.item_get_value("色块设置", "边框线-右下角", b_lower_right);
		fcfg.item_get_value("色块设置", "边框线-横线", b_h_normal);
		fcfg.item_get_value("色块设置", "边框线-竖线", b_v_normal);

		fcfg.item_get_value("色块设置", "被消除色块-背景色", opt[0][0]);
		fcfg.item_get_value("色块设置", "被消除色块-前景色", opt[0][1]);
		fcfg.item_get_value("色块设置", "选中色块背景色", opt[1][0]);
		fcfg.item_get_value("色块设置", "选中色块前景色", opt[1][1]);
		fcfg.item_get_value("色块设置", "反显色块背景色", opt[2][0]);
		fcfg.item_get_value("色块设置", "反显色块前景色", opt[2][1]);

		mto.gmw_set_frame_style(block_width, block_high, separator == 'Y' || separator == 'y');
		mto.gmw_set_block_linetype(b_top_left, b_lower_left, b_top_right, b_lower_right,
			b_h_normal, b_v_normal);

		char top_status = 'Y', lower_status = 'Y';
		int normal_bgcolor = -1, normal_fgcolor = -1, catchy_bgcolor = -1, catchy_fgcolor = 14;

		fcfg.item_get_value("状态栏设置", "上状态栏", top_status);
		fcfg.item_get_value("状态栏设置", "下状态栏", lower_status);
		fcfg.item_get_value("状态栏设置", "正常文字背景色", normal_bgcolor);
		fcfg.item_get_value("状态栏设置", "正常文字前景色", normal_fgcolor);
		fcfg.item_get_value("状态栏设置", "错误文字背景色", catchy_bgcolor);
		fcfg.item_get_value("状态栏设置", "错误文字前景色", catchy_fgcolor);

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

	/*游戏*/
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

