/*1952339 信08 张馨月*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include "../include/lib_mto10_net_tools.h"
#include "../include/lib_md5_sha_tools.h"
#include "./90-01-b2-mto10.h"
#include "./90-01-b2_with_mto10.h"
#include "../include/cmd_console_tools.h"
#include "../include/common_mybase_tool.h"
using namespace std;

#define		MAX_ROW_NUM		8
#define		MAX_COL_NUM		10

/*自动游戏过程*/
int mto_game_progress(mto10_net_tools& client, bool tg)
{
	char svrpack[RECVBUF_LEN];	//存放从Server端收到的数据
	char row_rt;
	int col_rt;

	char* mp, * old_mp;
	int row, column;
	int score = 0, stp = 0, gme_id, maxv = 0;
	int pointx = 1, pointy = 1, x, y;
	int table[Maxn][Maxn], fnd[Maxn][Maxn];

	row = client.get_row();
	column = client.get_col();
	gme_id = client.get_gameid();

	bool clk = 0;

	get_number(client.get_map(), row, column, table);
	pos_enumerate(row, column, &pointx, &pointy, table, fnd, maxv);
	if(tg)
		puzzle_screen(row, column, table, gme_id, stp, score);

	while (1) {
		/* -------------------
			Client=>Server
		   ------------------- */
		   /* 根据服务端发来的地图，返回一个解坐标（目前为手工输入形式，需要改为自动求最佳解坐标）
			  提示：可以将client.get_map()的返回值复制到字符数组中，再还原为你自己的二维数组后求解
		   */
		   //client.print_map(); //本函数仅为示意，图形界面中不能调用，要自己写转换函数

		line_clr(0, 0);
		cout << "当前选择解坐标为第 " << pointy << " 行第 " << pointx << " 列";
		cct_getxy(x, y);

		row_rt = 'A' + pointy - 1;
		col_rt = pointx - 1;
		/*if (pointy < 1 || pointy > row || pointx < 1 || pointx > column) {
			return -1;
		}*/
		client.send_coordinate(row_rt, col_rt);

		if (tg) {
			pos_chosen(pointx, pointy, row, column, table, fnd);
			puzzle_clr(pointy, pointx, row, column, table, fnd, 1, &maxv);
			table_move(1, row, column, table, fnd, 0);
			cct_gotoxy(0, 9 + 4 * row);
		}

		/* -------------------
			Server=>Client
		   ------------------- */
		   /* 等待Server端的gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			cct_setcolor();
			return -1;
		}
		trans_svrp(svrpack, &stp, &score);

		if (game_check_end(svrpack) == 1) {
			trans_svrp(svrpack, &mp);
			get_number(mp, row, column, table);
			if (tg) {
				for (int i = 1; i <= row; ++i)
					for (int j = 1; j <= column; ++j)
						cout_puzzle(2 + 8 * (i - 1), 2 + 4 * (j - 1), table[i][j], table[i][j]);
			}
			if (tg)
				cout_inf(0, 2 + 4 * row, gme_id, stp, score, maxv);
			else
				cout_inf(0, y+1, gme_id, stp, score, maxv);
			return 0;
		}

		if (trans_svrp(svrpack, &mp, &old_mp) == 0) {
			cct_gotoxy(0, 0);
			cct_setcolor();
			cout << "无法解析新地图!\n";
			return -1;
		}

		get_number(mp, row, column, table);
		pos_enumerate(row, column, &pointx, &pointy, table, fnd, maxv);

		if (tg)
			tran_puzzle_rebuild(row, column, gme_id, stp, score, maxv, table, old_mp);
		else
			cout_inf(0, y+1, gme_id, stp, score, maxv);
	}
}

/*登录与服务器建立连接*/
int mto10_main(bool tg)
{
	const int sleep_ms = 5000;					//网络重连时延(ms)
	const char* my_no[2] = { "9332591", "1952339"};//"1952339";				//本人学号
	const char* my_pwd = "i9,(dL9sZ5Zv!rDP";	//本人密码

	bool first = true;

	int wanted_row, wanted_col, wanted_id, wanted_delay;

	wanted_row = 8;			//此处按需修改为键盘输入等形式
	wanted_col = 8;			//此处按需修改为键盘输入等形式
	wanted_id = 12345;//12345		//id为本次请求的游戏序号，如果置-1，表示服务器随机产生，[0..2^31-1]则表示想固定序号（序号固定，则每次给出的初始矩阵及后续填充均相同，方便调试）
	wanted_delay = 60 * 1000;	//delay为请求的每步应答的最长时延，单位ms

	mto10_net_tools client;

	/* 打开client类对象中的debug开关（调试时可打开，到图形界面时需关闭） */
	client.set_debug_switch(false);

	while (1) {
		if (!first) { //出任何错误，延时5秒重连（不包括第一次）
			cct_setcolor();
			cout << "与服务器的连接断开!" << endl;
			Sleep(sleep_ms);
		}
		else
			first = false;

		/* 连接服务器 */
		if (client.connect() < 0) {
			/* 连接失败信息，有没有debug_switch都打印 */
			cct_setcolor();
			cout << "连接服务器失败!" << endl;
			continue;//return -1;
		}

		/* 向Server端发送认证信息及参数 */
		if (client.send_parameter(my_no[tg], my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
			cct_setcolor();
			cout << "发送认证及参数信息失败!" << endl;
			continue;//return -1;
		}

		if (client.wait_for_game_start() < 0) {
			cct_setcolor();
			cout << "等待GameStart失败!" << endl;
			continue;//return -1;
		}

		/* 打印从服务器收到的参数，本次游戏以此参数为准（例：发送6行6列，返回8行10列，则本次游戏以8行10列为准）
		   下面打印的信息，图形化界面可以自行去除 */
		/*cout << "服务器返回信息 : " << endl;
		cout << "  行数 : " << client.get_row() << endl;
		cout << "  列数 : " << client.get_col() << endl;
		cout << "  ID号 : " << client.get_gameid() << endl;
		cout << "  时限 : " << client.get_delay() << endl;
		cout << "  地图 : " << client.get_map() << endl;*/
		/* 地图串中的值为1-9，A-F，分别表示1-15的值，
		   例如：
			 服务器返回行=3
			 服务器返回列=4
			 服务器返回地图=123A85CF2123
		   则表示当前地图为(本例仅仅是示例)
			 1 2 3  10
			 8 5 12 15
			 2 1 2  3
			游戏结束的条件为：合成到16或无任何可合成元素 */

			/* 进入游戏交互环节
			   1、收到Server的GameOver则返回0，游戏结束
			   2、其它错误均返回-1（报文信息不正确等错误），重连，再次重复	*/
		if (mto_game_progress(client, tg) < 0) {
			client.close();
			continue;
		}
		else {
			/* game_progress只有收到 GameOver 才返回 0 */
			break;
		}
	};

	client.close();
	cct_setcolor();
	cout << "\n游戏结束" << endl;

	return 0;
}
