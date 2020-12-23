/*1952339 ��08 ��ܰ��*/
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

/*�Զ���Ϸ����*/
int mto_game_progress(mto10_net_tools& client, bool tg)
{
	char svrpack[RECVBUF_LEN];	//��Ŵ�Server���յ�������
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
		   /* ���ݷ���˷����ĵ�ͼ������һ�������꣨ĿǰΪ�ֹ�������ʽ����Ҫ��Ϊ�Զ�����ѽ����꣩
			  ��ʾ�����Խ�client.get_map()�ķ���ֵ���Ƶ��ַ������У��ٻ�ԭΪ���Լ��Ķ�ά��������
		   */
		   //client.print_map(); //��������Ϊʾ�⣬ͼ�ν����в��ܵ��ã�Ҫ�Լ�дת������

		line_clr(0, 0);
		cout << "��ǰѡ�������Ϊ�� " << pointy << " �е� " << pointx << " ��";
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
		   /* �ȴ�Server�˵�gameprogress */
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
			cout << "�޷������µ�ͼ!\n";
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

/*��¼���������������*/
int mto10_main(bool tg)
{
	const int sleep_ms = 5000;					//��������ʱ��(ms)
	const char* my_no[2] = { "9332591", "1952339"};//"1952339";				//����ѧ��
	const char* my_pwd = "i9,(dL9sZ5Zv!rDP";	//��������

	bool first = true;

	int wanted_row, wanted_col, wanted_id, wanted_delay;

	wanted_row = 8;			//�˴������޸�Ϊ�����������ʽ
	wanted_col = 8;			//�˴������޸�Ϊ�����������ʽ
	wanted_id = 12345;//12345		//idΪ�����������Ϸ��ţ������-1����ʾ���������������[0..2^31-1]���ʾ��̶���ţ���Ź̶�����ÿ�θ����ĳ�ʼ���󼰺���������ͬ��������ԣ�
	wanted_delay = 60 * 1000;	//delayΪ�����ÿ��Ӧ����ʱ�ӣ���λms

	mto10_net_tools client;

	/* ��client������е�debug���أ�����ʱ�ɴ򿪣���ͼ�ν���ʱ��رգ� */
	client.set_debug_switch(false);

	while (1) {
		if (!first) { //���κδ�����ʱ5����������������һ�Σ�
			cct_setcolor();
			cout << "������������ӶϿ�!" << endl;
			Sleep(sleep_ms);
		}
		else
			first = false;

		/* ���ӷ����� */
		if (client.connect() < 0) {
			/* ����ʧ����Ϣ����û��debug_switch����ӡ */
			cct_setcolor();
			cout << "���ӷ�����ʧ��!" << endl;
			continue;//return -1;
		}

		/* ��Server�˷�����֤��Ϣ������ */
		if (client.send_parameter(my_no[tg], my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
			cct_setcolor();
			cout << "������֤��������Ϣʧ��!" << endl;
			continue;//return -1;
		}

		if (client.wait_for_game_start() < 0) {
			cct_setcolor();
			cout << "�ȴ�GameStartʧ��!" << endl;
			continue;//return -1;
		}

		/* ��ӡ�ӷ������յ��Ĳ�����������Ϸ�Դ˲���Ϊ׼����������6��6�У�����8��10�У��򱾴���Ϸ��8��10��Ϊ׼��
		   �����ӡ����Ϣ��ͼ�λ������������ȥ�� */
		/*cout << "������������Ϣ : " << endl;
		cout << "  ���� : " << client.get_row() << endl;
		cout << "  ���� : " << client.get_col() << endl;
		cout << "  ID�� : " << client.get_gameid() << endl;
		cout << "  ʱ�� : " << client.get_delay() << endl;
		cout << "  ��ͼ : " << client.get_map() << endl;*/
		/* ��ͼ���е�ֵΪ1-9��A-F���ֱ��ʾ1-15��ֵ��
		   ���磺
			 ������������=3
			 ������������=4
			 ���������ص�ͼ=123A85CF2123
		   ���ʾ��ǰ��ͼΪ(����������ʾ��)
			 1 2 3  10
			 8 5 12 15
			 2 1 2  3
			��Ϸ����������Ϊ���ϳɵ�16�����κοɺϳ�Ԫ�� */

			/* ������Ϸ��������
			   1���յ�Server��GameOver�򷵻�0����Ϸ����
			   2���������������-1��������Ϣ����ȷ�ȴ��󣩣��������ٴ��ظ�	*/
		if (mto_game_progress(client, tg) < 0) {
			client.close();
			continue;
		}
		else {
			/* game_progressֻ���յ� GameOver �ŷ��� 0 */
			break;
		}
	};

	client.close();
	cct_setcolor();
	cout << "\n��Ϸ����" << endl;

	return 0;
}
